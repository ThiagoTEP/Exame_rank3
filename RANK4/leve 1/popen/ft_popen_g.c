#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int ft_popen(char const *file, const char *argv[], int type)
{
    int     fd[2];
    pid_t   pid;

    if (!file || !argv || (type != 'r' && type != 'w'))
        return (-1);
    if (pipe(fd) < 0)
        return (-1);
    pid = fork();
    if (pid < 0)
    {
        close (fd[0]);
        close (fd[1]);
        return (-1);
    }
    if (pid == 0)
    {
        if (type == 'r')
        {
            if (dup2(fd[1], 1) < 0)
                exit (-1);
        }
        else
        {
            if (dup2(fd[0], 0) < 0)
                exit (-1);
        }
        close (fd[1]);
        close (fd[0]);
        execvp(file, argv);
        exit(-1);
    }
    if (type == 'r')
    {
        close (fd[1]);
        return (fd[0]);
    }
    else
    {
        close (fd[0]);
        return (fd[1]);
    }
}
