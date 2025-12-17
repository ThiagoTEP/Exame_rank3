#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int num = 0;
	while(cmds[num])
		num++;

	if(num == 0)
		return 0;

	int fd[2];
	pid_t pid[num];
	int prev_fd = -1;

	int i = 0;
	while(i < num)
	{
		if((i < num -1) && (pipe(fd) == -1))
			return 1;
		if((pid[i] = fork()) < 0)
			return 1;
		if(pid[i] == 0)
		{
			if(prev_fd != -1)
				dup2(prev_fd, 0), close(prev_fd);
			if(i < num  -1)
				dup2(fd[1], 1), close(fd[0]), close(fd[1]);
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		if(prev_fd != -1)
			close(prev_fd);
		if(i < num  -1)
			close(fd[1]), prev_fd = fd[0];
		i++;
	}
	i = 0;
	while(i < num)
	{
		wait(NULL);
		i++;
	}
	return 0;
}

int main(int argc, char **argv)
{
	int cmds_size = 1;
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "|"))
			cmds_size++;
	}
	char ***cmds = calloc(cmds_size + 1, sizeof(char **));
	if (!cmds)
	{
		dprintf(2, "Malloc error: %m\n");
		return 1;
	}
	cmds[0] = argv + 1;
	int cmds_i = 1;
	for (int i = 1; i < argc; i++)
		if (!strcmp(argv[i], "|"))
		{
			cmds[cmds_i] = argv + i + 1;
			argv[i] = NULL;
			cmds_i++;
		}
	int ret = picoshell(cmds);
	if (ret)
		perror("picoshell");
	free(cmds);
	return ret;
}
