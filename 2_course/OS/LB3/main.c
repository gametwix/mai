#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

#define UP 1
#define DOWN 0

pthread_mutex_t lock;
size_t max_thread = 1;
size_t use_thread = 1;

struct ArgsBitonic{
    int *Nums;
    size_t Size;
    size_t RealSize;
    size_t Start;
    int Dir;
};

void InitArgs(struct ArgsBitonic *args,int *Nums,size_t Size,size_t RealSize,size_t Start,int Dir)
{
    args->Nums = Nums;
    args->Size = Size;
    args->RealSize = RealSize;
    args->Start = Start;
    args->Dir = Dir;
}


int SizeStep(int Num){
    int i = 1;
    while(i < Num)
        i*=2;
    return i;
}

void comparator(int *Nums,size_t i,size_t j,int dir){
    if(dir == (Nums[i] > Nums[j])){
        int temp = Nums[i];
        Nums[i] = Nums[j];
        Nums[j] = temp;
    }
}

void BitonicMerge(struct ArgsBitonic *args){
    if(args->Size > 1){
        int k = args->Size / 2;
        int n = args->RealSize;
        for(int i=args->Start;(i<k+args->Start && i < n);++i)
        {
            if(i+k < n)
                comparator(args->Nums,i,i+k,args->Dir);
        }
        struct ArgsBitonic args1;
        struct ArgsBitonic args2;
        InitArgs(&args1,args->Nums,k,args->RealSize,args->Start,args->Dir);
        InitArgs(&args2,args->Nums,k,args->RealSize,args->Start+k,args->Dir);
        BitonicMerge(&args1);
        BitonicMerge(&args2);
    }
}
 
void BitonicSort(struct ArgsBitonic *args){
    if(args->Size > 1 && (args->Start+1 < args->RealSize)){
        int k = args->Size/2;
        struct ArgsBitonic args1;
        struct ArgsBitonic args2;
        InitArgs(&args1,args->Nums,k,args->RealSize,args->Start,DOWN);
        InitArgs(&args2,args->Nums,k,args->RealSize,args->Start+k,UP);
        BitonicSort(&args1);
        BitonicSort(&args2);
        BitonicMerge(args);
    }
}

void BitonicMergePar(struct ArgsBitonic *args){
    if(args->Size > 1){
        int k = args->Size / 2;
        int n = args->RealSize;
        int isParal = 0;
        for(int i=args->Start;(i<k+args->Start && i < n);++i)
        {
            if(i+k < n)
                comparator(args->Nums,i,i+k,args->Dir);
        }
        struct ArgsBitonic args1;
        struct ArgsBitonic args2;
        pthread_t tid;
        InitArgs(&args1,args->Nums,k,args->RealSize,args->Start,args->Dir);
        InitArgs(&args2,args->Nums,k,args->RealSize,args->Start+k,args->Dir);
        pthread_mutex_lock(&lock);
        if(use_thread < max_thread)
        { 
            ++use_thread;
            pthread_mutex_unlock(&lock);
            isParal = 1;
            pthread_create(&tid, NULL,(void*) &BitonicMergePar, &args1);
        }
        else{
            pthread_mutex_unlock(&lock);
            BitonicMergePar(&args1);
        }
        BitonicMergePar(&args2);
    }
}
 
void BitonicSortPar(struct ArgsBitonic *args){
    if(args->Size > 1 && (args->Start+1 < args->RealSize)){
        int k = args->Size/2;
        int isParal = 0;
        struct ArgsBitonic args1;
        struct ArgsBitonic args2;
        pthread_t tid;
        InitArgs(&args1,args->Nums,k,args->RealSize,args->Start,DOWN);
        InitArgs(&args2,args->Nums,k,args->RealSize,args->Start+k,UP);
        pthread_mutex_lock(&lock);
        if(use_thread < max_thread)
        {
            ++use_thread;
            pthread_mutex_unlock(&lock);
            isParal = 1;
            pthread_create(&tid, NULL,(void*) &BitonicSortPar, &args1);
        }
        else
        {
            pthread_mutex_unlock(&lock);
            BitonicSortPar(&args1);
        }
        BitonicSortPar(&args2);
        if(isParal)
            pthread_join(tid, NULL);
        BitonicMergePar(args);
    }
}

int main(int argc, char *argv[]){
    if(argc == 2){
        if(atoi(argv[1]) > 1)
            max_thread = atoi(argv[1]);
    }
    pthread_mutex_init(&lock, NULL);
    int n;
    scanf("%d",&n);
    int *Nums = malloc(sizeof(int)*n);
    int SizeToSort = SizeStep(n);
    for(int i = 0;i<n;++i)
        scanf("%d",Nums+i);
    struct ArgsBitonic args;
    InitArgs(&args,Nums,SizeToSort,n,0,UP);
    BitonicSortPar(&args);

    for(int i=0;i<n;++i){
        printf("%d ",Nums[i]);
    }
    printf("\n");
    pthread_mutex_destroy(&lock);
    free(Nums);
    return 0;
}