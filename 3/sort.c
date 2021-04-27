#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Arg
{
    int start;
    int end;
    int *array;
}arr;

void *sort(void *ptr)
{
    arr *arg_ptr = (arr *)ptr;
    int temp;
    for (int i = arg_ptr->start; i <= arg_ptr->end - 1; i++)
    {
        for (int j = arg_ptr->start; j <= (arg_ptr->end + arg_ptr->start - i - 1); j++)
        {
            if (arg_ptr->array[j] > arg_ptr->array[j + 1])
            {

                temp = arg_ptr->array[j];
                arg_ptr->array[j] = arg_ptr->array[j + 1];
                arg_ptr->array[j + 1] = temp;
            }
        }
    }
}

void main()
{
    int *ar;
    int n;
    pthread_t t1, t2;
    arr obj1, obj2;

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    ar = (int *)malloc(sizeof(int) * n);

    printf("Enter the values: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ar[i]);
    }

    obj1.start = 0;
    obj1.end = n / 2 - 1;
    obj1.array = ar;
    obj2.start = n / 2;
    obj2.end = n - 1;
    obj2.array = ar;

    pthread_create(&t1, NULL, &sort, (void *)&obj1);
    pthread_create(&t2, NULL, &sort, (void *)&obj2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", ar[i]);
    }
}