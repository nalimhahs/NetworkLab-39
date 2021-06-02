#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

char str[10];
char *itoa(int num)
{
    sprintf(str, "%d", num);
    return str;
}

int main()
{
    int fd1[2], fd2[2];
    char str[] = "Hello world. Voluptate minim esse amet proident minim duis. \n Voluptate minim esse amet proident minim duis.";

    pid_t p;
    pipe(fd1);
    pipe(fd2);

    p = fork();

    // Parent process
    if (p > 0)
    {
        char data[10];

        write(fd1[1], str, strlen(str) + 1);
        wait(NULL);

        read(fd2[0], data, 10);
        printf("No of chars: %s\n", data);
        read(fd2[0], data, 10);
        printf("No of words: %s\n", data);
        read(fd2[0], data, 10);
        printf("No of lines: %s\n", data);
    }
    // child process
    else
    {
        char sentence[200];
        read(fd1[0], sentence, 200);

        int c = 0, w = 0, l = 0;
        for (int i = 0; i < strlen(sentence); i++)
        {
            if (sentence[i] == '\n')
            {
                l++;
            }
            else if (sentence[i] == ' ')
            {
                w++;
            }
            else
            {
                c++;
            }
        }

        write(fd2[1], itoa(c), 10);
        write(fd2[1], itoa(w), 10);
        write(fd2[1], itoa(l), 10);
        exit(0);
    }
}
