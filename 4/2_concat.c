#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd1[2], fd2[2];
    char str1[100], str2[100];

    pid_t p;
    pipe(fd1);
    pipe(fd2);

    printf("Enter string: ");
    // scanf("%[^\n]s", str1);
    fgets(str1, 50, stdin);

    printf("Enter string to concat to: ");
    fgets(str2, 50, stdin);
    // scanf("%[^\n]s", str2);

    p = fork();

    // Parent process
    if (p > 0)
    {
        char concat_str[200];

        write(fd1[1], str2, strlen(str2) + 1);
        wait(NULL);

        read(fd2[0], concat_str, 200);
        printf("Concatenated string: %s\n", concat_str);
    }
    // child process
    else
    {
        // Read
        char concat_str[200];
        read(fd1[0], concat_str, 200);

        // Concatenate
        int k = strlen(concat_str);
        int i;
        for (i = 0; i < strlen(str1); i++)
            concat_str[k++] = str1[i];

        concat_str[k] = '\0';

        write(fd2[1], concat_str, strlen(concat_str) + 1);
        exit(0);
    }
}
