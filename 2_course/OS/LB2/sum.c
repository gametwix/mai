#include "stdio.h"

int main(){
    long long sum = 0;
    int num;
    while(scanf("%d",&num) != EOF)
    {
        sum += num;
    }
    FILE *file;
    file = fopen("output", "w");
    fprintf(file,"%lld\n",sum);
    fclose(file);
    return 0;
}