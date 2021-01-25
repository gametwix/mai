#include "unistd.h"
#include "stdio.h"

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
		printf("[%d] It's child\n", getpid());
		fflush(stdout);
		int x, y;
		read(fd[0], &x, sizeof(int));
		read(fd[0], &x, sizeof(int));
		
		int res = x + y;
		write(fd[1], &res, sizeof(int));
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		printf("[%d] It's parent. Child id: %d\n", getpid(), id);
		fflush(stdout);
		int x = 10;
		int y = 5;
		write(fd[1], &x, sizeof(int));
		write(fd[1], &y, sizeof(int));
		
		int res;
		read(fd[0], &res, sizeof(int));
		printf("[%d] Result from child: %d\n", getpid(), res);
		fflush(stdout);
		close(fd[0]);
		close(fd[1]);
	}
	return 0;
}