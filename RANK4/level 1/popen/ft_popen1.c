#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	if(!file || !argv || (type != 'r' && type != 'w'))
		return -1;

	int fd[2];
	pid_t pid;

	if(pipe(fd) == - 1)
		return -1;
	if((pid = fork()) == -1)
		return(close(fd[0]), close(fd[1]), -1);
	if(pid == 0)
	{
		if(type == 'r')
			dup2(fd[1],1);
		else
			dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit(1);
	}
	if(type == 'r')
		return(close(fd[1]), fd[0]);
	else
		return(close(fd[0]), fd[1]);
}

int main(void)
{
	char buffer[1024];
	size_t n;
	int fd;

	fd = ft_popen("echo", (char *const[]){"echo", "hello ft_open", NULL}, 'r');

	if(fd != -1)
	{
		while((n = read(fd, buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[n] = '\0';
			printf("%s", buffer);
		}
		close(fd);

	}
	return 0;
}
