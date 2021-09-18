#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

// Sort array
void sort(int arr[], int n, int start)
{
    int i, j, key;
    for (i = start + 1; i < n + start; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= start && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Print Array
void printArray(int arr[], int n, int start)
{
    int i;
    for (i = start; i < n + start; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void main()
{
    int a[20], n;
    printf("Enter a Limit: ");
    scanf("%d", &n);

    printf("Enter Array values: \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int a0[20], a1[20], a2[20];
    int p = 1, q = 1, r = 1;
    for (int i = 0; i < n; i++)
    {
        if (a[i] % 3 == 0)
        {
            a0[p++] = a[i];
        }
        if (a[i] % 3 == 1)
        {
            a1[q++] = a[i];
        }
        if (a[i] % 3 == 2)
        {
            a2[r++] = a[i];
        }
    }

    a0[0] = p - 1;
    a1[0] = q - 1;
    a2[0] = r - 1;

    // Pipes
    int toA0[2], toA1[2], toA2[2], fromA0[2], fromA1[2], fromA2[2];
    pipe(toA0);
    pipe(toA1);
    pipe(toA2);
    pipe(fromA0);
    pipe(fromA1);
    pipe(fromA2);

    write(toA0[1], a0, sizeof(a0));
    close(toA0[1]);

    write(toA1[1], a1, sizeof(a1));
    close(toA1[1]);

    write(toA2[1], a2, sizeof(a2));
    close(toA2[1]);

    //First Child
    if (fork() == 0)
    {
        int arr[20];
        read(toA0[0], arr, sizeof(arr));
        close(toA0[0]);
        sort(arr, arr[0], 1);
        printf("\nLargest of mod 0: %d", arr[arr[0]]);
        write(fromA0[1], arr, sizeof(arr));
        close(fromA0[1]);
        exit(0);
    }
    else
    {
        // Second Child
        if (fork() == 0)
        {
            int arr[20];
            read(toA1[0], arr, sizeof(arr));
            close(toA1[0]);
            sort(arr, arr[0], 1);
            printf("\nLargest of mod 1: %d", arr[arr[0]]);
            write(fromA1[1], arr, sizeof(arr));
            close(fromA1[1]);
        }
        else
        {
            // Third Child
            if (fork() == 0)
            {
                int arr[20];
                read(toA2[0], arr, sizeof(arr));
                close(toA2[0]);
                sort(arr, arr[0], 1);
                printf("\nLargest of mod 2: %d", arr[arr[0]]);
                write(fromA2[1], arr, sizeof(arr));
                close(fromA2[1]);
            }
            // Final Parent
            else
            {
                wait(NULL);
                wait(NULL);
                wait(NULL);
                read(fromA0[0], a0, sizeof(a0));
                close(fromA0[0]);
                read(fromA1[0], a1, sizeof(a1));
                close(fromA1[0]);
                read(fromA2[0], a2, sizeof(a2));
                close(fromA2[0]);
                printf("\nRead complete!");
                int arr[20], k = 0;
                for (int i = 1; i < a0[0] + 1; i++)
                {
                    arr[k++] = a0[i];
                }
                for (int i = 1; i < a1[0] + 1; i++)
                {
                    arr[k++] = a1[i];
                }
                for (int i = 1; i < a2[0] + 1; i++)
                {
                    arr[k++] = a2[i];
                }
                sort(arr, k, 0);
                printf("\nSorted: ");
                printArray(arr, k, 0);
            }
        }
    }
}