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
    int m, n, p, q;
    pthread_t *t;
    dat obj;
    int *prod;
    int sum;

    printf("Enter the number of rows and columns: ");
    scanf("%d%d", &m, &n);

    printf("Enter the matrix:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Enter the number of rows and columns ");
    scanf("%d%d", &p, &q);

    printf("Enter the matrix\n");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
        {
            scanf("%d", &mat2[i][j]);
        }
    }

    t = (pthread_t *)malloc(sizeof(pthread_t) * m * q * n);
    prod = (int *)malloc(sizeof(int) * m * q * n);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            sum = 0;
            int val = 0;
            for (int k = 0; k < n; k++)
            {
                int thread_id = ((i * m) + (j * q)) + k;
                obj.n1 = mat1[i][k];
                obj.n2 = mat2[k][j];
                pthread_create(&(t[thread_id]), NULL, &mult, (void *)&obj);
                pthread_join(t[thread_id], (void **)&(prod[thread_id]));
                sum = sum + prod[thread_id];
            }
            mat3[i][j] = sum;
        }
    }

    printf("\nAfter multiplication\n\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            printf("%d\t", mat3[i][j]);
        }
        printf("\n");
    }
}