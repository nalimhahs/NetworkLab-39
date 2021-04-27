#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Arg
{
    int n1;
    int n2;
} dat;

void *mult(void *ptr)
{
    dat *arg_ptr = (dat *)ptr;
    int prod = arg_ptr->n1 * arg_ptr->n2;
    pthread_exit((void *)prod);
}

void main()
{
    int mat1[20][20], mat2[20][20], mat3[20][20];
    int r1, r2, c1, c2;
    pthread_t *t;
    dat obj;
    int *prod;
    int sum;

    printf("Enter the number of rows and columns: ");
    scanf("%d%d", &r1, &c1);

    printf("Enter the matrix:\n");
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++)
        {
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Enter the number of rows and columns ");
    scanf("%d%d", &r2, &c2);

    printf("Enter the matrix\n");
    for (int i = 0; i < r2; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            scanf("%d", &mat2[i][j]);
        }
    }

    t = (pthread_t *)malloc(sizeof(pthread_t) * r1 * c2 * c1);
    prod = (int *)malloc(sizeof(int) * r1 * c2 * c1);

    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            sum = 0;
            int val = 0;
            for (int k = 0; k < c1; k++)
            {
                obj.n1 = mat1[i][k];
                obj.n2 = mat2[k][j];
                pthread_create(&(t[i * r1 + j * c2 + k]), NULL, &mult, (void *)&obj);
                pthread_join(t[i * r1 + j * c2 + k], (void **)&(prod[i * r1 + j * c2 + k]));
                sum = sum + prod[i * r1 + j * c2 + k];
            }
            mat3[i][j] = sum;
        }
    }
    
    printf("After multiplication\n");
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            printf("%d ", mat3[i][j]);
        }
        printf("\n");
    }
}