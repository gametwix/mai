#include "unistd.h"
#include "stdio.h"

int main(){
    
    int fd[2];
    pipe(fd);
    int id = fork();
    if(id == 0)
    {
        int input = dup(fd[0]);
        close(fd[1]);
        close(fd[0]);
        dup2(input,0);
        execl("./sum","sum",(char*) NULL);
    }
    else
    {
        close(fd[0]);
        dup2(fd[1],1);
        int num;
        while(scanf("%d",&num) != EOF)
        {
            printf("%d\n",num);
            fflush(stdout);
        }
        close(fd[1]);
    }
    return 0;
}

