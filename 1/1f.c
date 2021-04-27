#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    if (fork() && (!fork()))
    {
        if (fork() || fork())
        {
            fork();
        }
    }
    printf("2\n");
}