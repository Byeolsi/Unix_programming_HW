#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <signal.h>

void handler(int signo) {
    printf("The parent process receives SIGUSR1\n");
}

int main() {
    int fd, pagesize, length;
    pid_t pid;
    caddr_t addr;
    struct stat statbuf;

    pagesize = sysconf(_SC_PAGESIZE);
    length = 1 * pagesize;

    if ((fd = open("HW3data", O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1) {
        perror("open");
        exit(1);
    }

    if (ftruncate(fd, (off_t)length) == -1) {
        perror("ftruncate");
        exit(1);
    }

    if (stat("HW3data", &statbuf) == -1) {
        perror("stat");
        exit(1);
    }

    addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE,
                 MAP_SHARED, fd, (off_t)0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    close(fd);

    switch (pid = fork()) {
        case -1 :  /* fork failed */
            perror("fork");
            exit(1);
            break;
        case 0 :   /* child process */
            strcpy(addr, "Message from child process to parent process\n");
            printf("The child process raises SIGUSR1\n");
            kill(getppid(), SIGUSR1);
            break;
        default :  /* parent process */
            sigset(SIGUSR1, handler);
            sigpause(SIGUSR1);
            printf("%s", addr);
            break;
    }

    return 0;
}
