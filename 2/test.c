#include <stdio.h>
#include <unistd.h>

void main()
{
    int a[5], sum = 0, product = 1;
    printf("Enter 5 numbers: ");
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &a[i]);
    }

    if (fork() == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            sum += a[i];
        }
        printf("\nSum: %d", sum);
        printf("SUm process: %d", getpid());
    }

    if (fork() == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            product *= a[i];
        }
        printf("\nProduct: %d\n", product);
        printf("Prod process: %d", getpid());
    }
}