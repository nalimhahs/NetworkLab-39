#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

sem_t read_protect;
sem_t write_protect;
sem_t item_protect;

int item = 0;
int write_waiting = 0;
int read_waiting = 0;

key_t key;
int shmid;

void *writer(void *tid)
{
    int *id = (int *)tid;

    sem_wait(&write_protect);
    write_waiting++;
    sem_wait(&item_protect);

    key = ftok("shmfile", 65);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int *num = (int *)shmat(shmid, (void *)0, 0);

    item++;
    *num = item;

    printf("Data written in memory: %d\n", *num);

    shmdt(num);

    sem_post(&item_protect);

    write_waiting--;

    sem_post(&write_protect);
}

void *reader(void *tid)
{

    int *id = (int *)tid;

    sem_wait(&read_protect);
    while (write_waiting)
        ;
    read_waiting++;

    sem_wait(&item_protect);
    key = ftok("shmfile", 65);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int *num = (int *)shmat(shmid, (void *)0, 0);
    printf("Data read from memory: %d\n", *num);
    sem_post(&item_protect);
    read_waiting--;
    sem_post(&read_protect);
}

void main()
{
    sem_init(&write_protect, 0, 1);
    sem_init(&read_protect, 0, 1);
    sem_init(&item_protect, 0, 1);

    int rnum, wnum;
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    pthread_t read[100];
    pthread_t write[100];

    printf("Enter the number of readers : ");
    scanf("%d", &rnum);
    printf("\nEnter the number of writers : ");
    scanf("%d", &wnum);
    printf("\n");

    for (int i = 0; i < rnum; i++)
    {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }

    for (int i = 0; i < wnum; i++)
    {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }

    for (int i = 0; i < rnum; i++)
    {
        pthread_join(read[i], NULL);
    }
    for (int i = 0; i < wnum; i++)
    {
        pthread_join(write[i], NULL);
    }

    sem_destroy(&read_protect);
    sem_destroy(&write_protect);
    shmctl(shmid, IPC_RMID, NULL);
    pthread_exit(NULL);
}