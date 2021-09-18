#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numreader = 0;

key_t key;
int shmid;

void *writer(void *wno)
{
    sem_wait(&wrt);

    key = ftok("shmfile", 65);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int *num = (int *)shmat(shmid, (void *)0, 0);

    cnt++;
    *num = cnt;

    printf("Data written in memory: %d\n", cnt);
    shmdt(num);

    sem_post(&wrt);
}
void *reader(void *rno)
{

    pthread_mutex_lock(&mutex);
    numreader++;
    if (numreader == 1)
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    key = ftok("shmfile", 65);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int *num = (int *)shmat(shmid, (void *)0, 0);

    printf("Data read from memory: %d\n", cnt);
    shmdt(num);

    pthread_mutex_lock(&mutex);
    numreader--;
    if (numreader == 0)
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{

    pthread_t read[100], write[100];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int rnum, wnum;
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

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

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}