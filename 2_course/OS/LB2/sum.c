#include "stdio.h"
#include "string.h"

int main(){
    long long sum = 0;
    int num;
    char ch;
    FILE *file;
    char *filename = NULL;
    size_t sizename = 0;
    getline(&filename,&sizename,stdin);
    filename[strlen(filename)-1] = '\0';
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

