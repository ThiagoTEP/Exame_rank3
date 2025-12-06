#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int    picoshell(char **cmds[])
{
	int num = 0;
	while(cmds[num])
		num++;

	pid_t	pid[num];
	int fd[2];
	int prev_fd = -1;

	for (int i = 0; i < num; i++)
	{
		if ((i < num -1) && (pipe(fd) == -1))
			return 1;
		if ((pid[i] = fork()) < 0)
			return 1;
		if (pid[i] == 0)
		{
			if (prev_fd != -1)
				dup2(prev_fd, 0), close(prev_fd);
			if(i < num -1)
				dup2(fd[1], 1), close(fd[0]), close(fd[1]);
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (i < num -1)
			close(fd[1]), prev_fd = fd[0];
	}
	for (int i = 0; i < num; i++)
		wait(NULL);
	return (0);
}

// GIVEN MAIN V
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