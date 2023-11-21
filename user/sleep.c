#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(strlen(argv[1]) == 0 || argc == 1) {
        printf("input error");
    }

    int num = atoi(argv[1]);

    if(num == -1) {
        printf("input error");
    } else {
        sleep(num);
    }

    exit(0);
}