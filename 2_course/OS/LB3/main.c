#include "stdio.h"
#include "stdlib.h"

#define UP 1
#define DOWN 0

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

void BitonicMerge(int *Nums,size_t Size,size_t RealSize,size_t Start,int Dir){
    if(Size > 1){
        int k = Size / 2;
        int n = RealSize;
        for(int i=Start;(i<k+Start && i < n);++i)
        {
            if(i+k < n)
                comparator(Nums,i,i+k,Dir);
        }
        BitonicMerge(Nums,k,RealSize,0,Dir);
        BitonicMerge(Nums,k,RealSize,k,Dir);
    }
}
 
void BitonicSort(int *Nums,size_t Size,size_t RealSize,size_t Start,int Dir){
    if(Size > 1 && (Start+1 < RealSize)){
        int k = Size/2;
        BitonicSort(Nums,k,RealSize,Start,DOWN);
        BitonicSort(Nums,k,RealSize,Start+k,UP);
        BitonicMerge(Nums,Size,RealSize,Start,Dir);
    }
}




int main(){
    int n;
    scanf("%d",&n);
    int *Nums = malloc(sizeof(int)*n);
    int SizeToSort = SizeStep(n);
    for(int i = 0;i<n;++i)
        scanf("%d",Nums+i);

    BitonicSort(Nums,SizeToSort,n,0,UP);

    for(int i=0;i<n;++i){
        printf("%d ",Nums[i]);
    }
    printf("\n");

    free(Nums);
    return 0;
}