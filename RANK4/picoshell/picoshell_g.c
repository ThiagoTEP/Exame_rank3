#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
    int     fd[2];
    pid_t   pid;
    int     i = 0;
    int     in = -1;
    int     ret = 0;
    int     status;
    
    while (cmds[i])
    {
        if (cmds[i + 1])
        {
            if (pipe(fd) == -1)
            {
                if (in != -1)
                    close (in);
                return (1);
            }
        }
        else
        {
            fd[0] = -1;
            fd[1] = -1;
        }
        pid = fork();
        if (pid < 0)
        {
            if (in != -1)
                close (in);
            if (fd[1] != -1)
                close (fd[1]);
            if (fd[0] != -1)
                close (fd[1]);
            return (1);
        }
        if (pid == 0)
        {
            if (in != -1)
            {
                if (dup2(in, 0) == -1)
                    exit (1);
                close (in);
            }
            if (fd[1] != -1)
            {
                if (dup2(fd[1], 1) == -1)
                    exit (1);
                close (fd[1]);
                close (fd[0]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        else
        {
            if (in != -1)
                close (in);
            if (fd[1] != -1)
                close (fd[1]);
            in = fd[0];
            i++;
        }
    }
    while (wait(&status) > 0)
    {
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
            ret = 1;
    }
    return (ret);
}
