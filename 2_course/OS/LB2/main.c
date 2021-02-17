#include "unistd.h"
#include "string.h"
#include "stdio.h"

int main(){
    int fd[2];
    pipe(fd);
    int id = fork();
    if(id == 0){
        close(fd[1]);
        dup2(fd[0],0);
        execl("./child","child",(char*) NULL);
    } else {
        close(fd[0]);
        char filename[100];
        scanf("%s",filename);
        filename[strlen(filename)] = '\n';
        write(fd[1],filename,strlen(filename));
        char ch;
        while(scanf("%c",&ch) != EOF){
            write(fd[1],&ch,sizeof(ch));  
        }
        close(fd[1]);
    }
    return 0;
}

