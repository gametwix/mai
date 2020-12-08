#include "stdio.h"
#include "unistd.h"

int main()
{
    int fd[2];
	pipe(fd);
	int id = fork();
	if (id == -1)
	{
		perror("fork error");
		return -1;
	}
	else if (id == 0)
	{
        printf("child\n");
        char name[256];
        read(fd[0],name,256*sizeof(char));
        printf("1\n");
        printf("%s\n",name);
        int res = 0;
        int x;
        while(read(fd[0], &x, sizeof(int)) != 1)
            res += x;
		write(fd[1], &res, sizeof(int));
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
        char name[256];
        scanf("%s",name);
        write(fd[0],name,256*sizeof(char));
        int x;
		while(scanf("%d",&x) == 1)
        {
            write(fd[0],&x,sizeof(int));
        }
        int res;
        read(fd[1], &res, sizeof(int));
        close(fd[0]);
		close(fd[1]);
        printf("Результат %d\n",res);
	}

    return 0;
}