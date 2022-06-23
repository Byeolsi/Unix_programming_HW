#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char**argv){
        FILE *rfp, *wfp;

        char buf[27];
        int i, n;

        n = atoi(argv[1]);

        if ((wfp = fopen("testdata", "w")) == NULL){
                perror("fopen: testdata");
                exit(1);
        }

        fputs("abcdefghijklmnopqrstuvwxyz", wfp);

        fclose(wfp);

        if ((rfp = fopen("testdata", "r")) == NULL){
                perror("fopen: testdata");
                exit(1);
        }

        fgets(buf, 27, rfp);
        printf("current offset : ");
        for (i = 0; i < strlen(buf); i += n){
                printf("%d ", i);
        }
        printf("\n");

        printf("current data : ");
        for (i = 0; i < strlen(buf); i += n){
                printf("%c ", buf[i]);
        }
        printf("\n");

        fclose(rfp);

        return 0;
}