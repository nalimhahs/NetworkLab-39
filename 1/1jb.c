#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    printf("We are in 1jb.c\n");
    printf("PID of 1jb.c = %d\n", getpid());
    return 0;
}