#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
        if(argc < 2) exit(1);

        if (strcmp(argv[1], "-v") ==0) {
                int pipefd[2];
                pipe(pipefd);
                int childpid1 = fork();
                if (childpid1 == 0) {
                        close(1);
                        dup2(pipefd[1], 1);
                        close(pipefd[0]);
                        close(pipefd[1]);
                        execvp(argv[2], &argv[2]);
                        exit(1);
                }
                int childpid2 = fork();
                if (childpid2 == 0) {
                        close(0);
                        dup2(pipefd[0], 0);
                        close(pipefd[1]);
                        close(pipefd[0]);
                        int fd = open("record.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        close(1);
                        dup2(fd, 1);
                        close(fd);
                        char *args[] = {"filter", NULL};
                        execvp("./filter", args);
                        exit(1);
                }
                close(pipefd[0]);
                close(pipefd[1]);
        } else {
                int fd = open("record.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                close(1);
                dup2(fd, 1);
                close(fd);
                execvp(argv[1], &argv[1]);
                exit(1);
        }
        return 0;
}
