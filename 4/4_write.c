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

//displaying all the collected details
void displayDetails(Student *s_details, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nStudent no: %d\n", i + 1);
        printf("Name: %s\n", s_details[i].name);
        printf("Rank: %d\n", s_details[i].rank);
    }
}

void main()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SEG_SIZE, 0666 | IPC_CREAT);
    Student studs[10];
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\nDetails of Student %d\n", i);
        printf("Enter name: ");
        scanf("%s", studs[i].name);
        printf("Enter rank: ");
        scanf("%d", &studs[i].rank);
        studs[i].count = n;
    }

    printf("\n\nCollected Details\n");
    displayDetails(studs, n);

    Student *data = (Student *)shmat(shmid, NULL, 0);

    memcpy(data, studs, 10 * sizeof(Student));

    shmdt(data);
    printf("Successful\n");
}
