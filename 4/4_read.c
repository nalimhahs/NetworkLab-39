#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SEG_SIZE 1024

typedef struct StudentDetails
{
    char name[10];
    int rank;
    int count;
} Student;

void displayDetails(Student *s_details, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nStudent no: %d\n", i + 1);
        printf("Name: %s\n", s_details[i].name);
        printf("Rank: %d\n", s_details[i].rank);
    }
}


void swap(Student *std1, Student *std2)
{
    Student temp;
    strcpy(temp.name, std1->name);
    temp.rank = std1->rank;

    strcpy(std1->name, std2->name);
    std1->rank = std2->rank;

    strcpy(std2->name, temp.name);
    std2->rank = temp.rank;
}

void bubbleSort(Student *s_details, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (s_details[j].rank > s_details[j + 1].rank)
            {
                swap(&s_details[j], &s_details[j + 1]);
            }
        }
    }
}

void main()
{
    char str[100];
    Student studs[10];
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SEG_SIZE, 0666 | IPC_CREAT);
    Student *data = (Student *)shmat(shmid, NULL, 0);

    memcpy(studs, data, 10 * sizeof(Student));
    displayDetails(studs, studs[0].count);

    printf("After sorting\n\n");
    bubbleSort(studs, studs[0].count);
    displayDetails(studs, studs[0].count);

    shmdt(data); //detaching str from segment

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL); //destroying the created segment
    printf("Successful\n");
}
