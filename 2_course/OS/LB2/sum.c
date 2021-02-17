#include "stdio.h"

int main(){
    long long sum = 0;
    int num;
    char ch;
    FILE *file;
    char filename[100];
    scanf("%s",filename);
    file = fopen(filename, "w");
    while(scanf("%d%c",&num,&ch) != EOF){
        sum += num;
        if(ch == '\n'){
            fprintf(file,"%lld\n",sum);
            sum = 0;
        }
    }
    fclose(file);
    return 0;
}

