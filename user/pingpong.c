#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int *p1=malloc(2*sizeof(int));
    int *p2=malloc(2*sizeof(int));

    pipe(p1);
    pipe(p2);
    char trans = 'b';
    char trans2 = 'a';

    int *read1 = p1, *write1 = ++p1;
    int *read2 = p2, *write2 = ++p2;

    int pid = fork();
    if(pid < 0) {
        printf("fork failed");
    } else if(pid > 0) {
        int txt1 = write(*write1, &trans, sizeof(trans));
        if(txt1 != sizeof(trans)) exit(1);
        char buf1;
        int res1 = read(*read2, &buf1, sizeof(buf1));
        if(buf1 == trans2 && res1 == sizeof(trans)) printf("<pid:%d>: received pong\n", getpid());
    } else if(pid == 0) {
        int txt2 = write(*write2, &trans2, sizeof(trans2));
        if(txt2 != sizeof(trans2)) exit(1);
        char buf2;
        int res2 = read(*read1, &buf2, sizeof(buf2));
        if(buf2 == trans && res2 == sizeof(trans2)) printf("<pid:%d>: received ping\n", getpid());
    }

    exit(0);
}