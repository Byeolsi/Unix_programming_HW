#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 64

int main(int argc, char *argv[]){
        int fd, i, length;
        char buf[BUFSIZE], tmpStr1[BUFSIZE], tmpStr2[BUFSIZE];
        off_t offset;
        ssize_t nbuf;

        if((fd = open("residents", O_RDWR, 0644)) == -1){
                perror("Open residents");
                exit(1);
        }

        printf("< Before >\n");
        for (i = 0; i < 12; i++){
                if ((nbuf = read(fd, buf, sizeof(buf))) <= 0){
                        perror("Read Error");
                        exit(1);
                }
                printf("room = %d, %s\n", i + 1, buf);
        }

        if (argc == 3){
                offset = atoi(argv[1]) - 1;
                lseek(fd, offset * sizeof(buf), SEEK_SET);
                read(fd, buf, sizeof(buf));
                strcpy(tmpStr1, buf);

                offset = atoi(argv[2]) - 1;
                lseek(fd, offset * sizeof(buf), SEEK_SET);
                read(fd, buf, sizeof(buf));
                strcpy(tmpStr2, buf);

                offset = atoi(argv[1]) - 1;
                lseek(fd, offset * sizeof(buf), SEEK_SET);
                strcpy(buf, tmpStr2);
                write(fd, buf, sizeof(buf));

                offset = atoi(argv[2]) - 1;
                lseek(fd, offset * sizeof(buf), SEEK_SET);
                strcpy(buf, tmpStr1);
                write(fd, buf, sizeof(buf));

                printf("< After >\n");
                lseek(fd, 0, SEEK_SET);
                for (i = 0; i < 12; i++){
                        if ((nbuf = read(fd, buf, sizeof(buf))) <= 0){
                                perror("Read error");
                                exit(1);
                        }
                        printf("room = %d, %s\n", i + 1, buf);
                }
        }
        else {
                perror("Not Enough argv!");
                exit(1);
        }

        return 0;
}