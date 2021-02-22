#include <stdio.h>

int sum(int **array){
    if(sizeof(array) > sizeof(int))
    {
        printf("%p %ld\n",array,sizeof(array));

        return sum(&(*array + 1))+**array;
    }  
    else
        return **array;
}

int main(){
    int array[5] = {5,4,3,2,1};
    printf("%d\n",sum(&array));
    return 0;
}