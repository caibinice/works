#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
       #include <sys/types.h>
       #include <sys/wait.h>



int exec_sb(char *cmd, char *res_buff, size_t size)
{
    int rv, pipe_fd[2], data_size;
    pid_t pid;

    rv = pipe(pipe_fd);
    if (rv < 0) {
        printf("pipe error rv=%d", rv);
        return rv;
    }

    pid = fork();
    if (pid < 0) {
        printf("fork error pid=%d", pid);
        return pid;
    }

    if (pid == 0) {
        char *arg;

        close(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);

        arg = strchr(cmd, ' ');
        if (arg != NULL) {
            *arg = '\0';
            arg++;
        }

        rv = execlp(cmd, cmd, arg, NULL);
        if (rv < 0) {
            printf("Error:execlp rv=%d\n", rv);
        }
        _exit(0);
    }

    close(pipe_fd[1]) ;
    memset(res_buff, 0, size);
    data_size = read(pipe_fd[0], res_buff, size - 1);
    if (data_size < 0) {
        printf("read error data_size=%d", data_size);
        return -20;
    }
    int status = 0 ;
    waitpid(pid, &status, WUNTRACED);
    printf("Child process status=%d, WEXITSTATUS=%d\n", status, WEXITSTATUS(status)) ;

    return WEXITSTATUS(status);
}

/*
int main(void) {
	char test[] = "ls ./" ;
    int rs = exec(test, buff, BUFF_SIZE);
    printf("main rv=%d\n", rs);
    printf(buff);
    return rs;
}*/
