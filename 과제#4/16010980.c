#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int ntimes = 0;

void p_action(int);
void c_action(int);

main(int argc, char **argv) {
        int i;
        pid_t pid, ppid;

        switch (pid = fork()) {

        case -1:
                perror("fork failed");
                exit(1);
        case 0:
                ppid = getppid();
                signal(SIGUSR1, c_action);
                for (i = 0; i < 5; i++){
                        sleep(1);
                        kill(ppid, SIGUSR1);
                        pause();
                }
        default:
                signal(SIGUSR1, p_action);
                for (i = 0; i < 5; i++){
                        pause();
                        sleep(1);
                        kill(pid, SIGUSR1);
                }
        }
}

void p_action(int sig)
{
        printf("Parent caught signal %d\n", ++ntimes);
}

void c_action(int sig)
{
        printf("Child caught signal %d\n", ++ntimes);
}