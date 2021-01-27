#include "stdio.h"
#include "stdlib.h"

#define UP 1
#define DOWN 0

int Ceil(int a, int b){ return (a+a%2)/b;}

void comparator(int *Nums,size_t i,size_t j,int dir){
    if(dir == (Nums[i] > Nums[j])){
        int temp = Nums[i];
        Nums[i] = Nums[j];
        Nums[j] = temp;
    }
}

void BironicMerge(int *Nums,size_t Size,size_t Start,int Dir){

}

void BitonicSort(int *Nums,size_t Size,size_t Start,int Dir){
    if(Size > 1){
        int k = Ceil(Size,2);
        BitonicSort(Nums,k,0,UP);
        BitonicSort(Nums,Size-k,k,UP);

    }
}


int main(){
    int n;
    scanf("%d",&n);
    /*int *Nums = malloc(sizeof(int)*n);

    for(int i = 0;i<n;++i)
        scanf("%d",Nums+i);
    free(Nums);*/
    printf("%d",Ceil(n,2));
    
    return 0;
}