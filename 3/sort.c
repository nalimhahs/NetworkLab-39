#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Arg
{
    int beg;
    int end;
    int *ar;
}arr;

void *sort(void *ptr)
{
    arr *arg_ptr = (arr *)ptr;
    int temp;
    for (int i = arg_ptr->beg; i <= arg_ptr->end - 1; i++)
    {
        for (int j = arg_ptr->beg; j <= (arg_ptr->end + arg_ptr->beg - i - 1); j++)
        {
            if (arg_ptr->ar[j] > arg_ptr->ar[j + 1])
            {

                temp = arg_ptr->ar[j];
                arg_ptr->ar[j] = arg_ptr->ar[j + 1];
                arg_ptr->ar[j + 1] = temp;
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

    obj1.beg = 0;
    obj1.end = n / 2 - 1;
    obj1.ar = ar;
    obj2.beg = n / 2;
    obj2.end = n - 1;
    obj2.ar = ar;

    pthread_create(&t1, NULL, &sort, (void *)&obj1);
    pthread_create(&t2, NULL, &sort, (void *)&obj2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", ar[i]);
    }
}