#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#define MAXARG 100

int main(int argc, char *argv[])
{
    char s;

    int fd[2];
    pipe(fd);

    int pid = fork();
    char *n[MAXARG];
    int i = 1, j = 0;

    if(pid == 0) {
        close(fd[1]);
        n[0]=malloc(sizeof(char)*MAXARG);
        while(read(fd[0], &s, 1) != 0) {
            //printf("%c", s);
            if(s != ' ') n[i][j++] = s;
            else {
                n[i][j] = '\0';
                i++;
                n[i] = malloc(sizeof(char)*MAXARG);
                j=0;
            }
        }
        for(int l = 1; l <= i; l++) printf("%s", n[l]);
        exec(argv[1], n);
        close(fd[0]);

    } else {
        close(fd[0]);
        for(int k = 2; k < argc; k++) {
            write(fd[1], argv[i], sizeof(argv[i]));
            write(fd[1], " ", sizeof(" "));
        }

        while(read(0, &s, 1) != 0){
            if(s != ' ') write(fd[1], &s, sizeof(s));
            else write(fd[1], " ", sizeof(" "));
        }
        close(fd[1]);
        wait(0);
    }
    
    exit(0);
}