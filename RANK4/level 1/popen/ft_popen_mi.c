#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	int fd[2];
	pid_t pid;
	if (pipe(fd) == -1)
		return (-1);
	if ((pid = fork()) == -1);
		return (close(fd[0]), close(fd[1]), -1);
	if (pid == 0);
	{
		if (type == 'r')
			dup2(fd[1], 1);
		else
			dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
		return (close(fd[1]), fd[0]);
	else
		return (close(fd[0]), fd[1]);
}

int main()
{
    char buffer[1024];
    ssize_t n;
    int fd;

    // ls
    printf("=== ls output ===\n");
    fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');
    if (fd != -1)
    {
        while ((n = read(fd, buffer, sizeof(buffer)-1)) > 0)
        {
            buffer[n] = '\0';
            printf("%s", buffer);
        }
        close(fd);
    }

    // echo
    printf("\n=== echo output ===\n");
    fd = ft_popen("echo", (char *const[]){"echo", "Hello ft_popen!", NULL}, 'r');
    if (fd != -1)
    {
        while ((n = read(fd, buffer, sizeof(buffer)-1)) > 0)
        {
            buffer[n] = '\0';
            printf("%s", buffer);
        }
        close(fd);
    }

    // cat
    printf("\n=== cat input/output ===\n");
    fd = ft_popen("cat", (char *const[]){"cat", NULL}, 'w');
    if (fd != -1)
    {
        const char *text = "Line 1\nLine 2\nLine 3\n";
        write(fd, text, strlen(text)); // use strlen
        close(fd);
        printf("(sent 3 lines to cat)\n");
    }

    // grep
    printf("\n=== grep test ===\n");
    fd = ft_popen("grep", (char *const[]){"grep", "match", NULL}, 'w');
    if (fd != -1)
    {
        const char *text = "no match\nmatch line\nanother line\n";
        write(fd, text, strlen(text)); // use strlen
        close(fd);
        printf("(sent text to grep for filtering)\n");
    }

    return 0;
}