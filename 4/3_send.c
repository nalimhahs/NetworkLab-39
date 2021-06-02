#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

void main()
{
    char msg1[] = "Hello!";
    char msg2[] = "Konichiwa!";
    char msg3[] = "Hola!";

    mqd_t msg_q;
    msg_q = mq_open("/test_q", O_CREAT | O_RDWR, 0666, NULL);

    if (msg_q == -1)
    {
        printf("Error creating queue!\n");
    }
    else
    {
        mq_send(msg_q, msg1, strlen(msg1), 3);
        mq_send(msg_q, msg2, strlen(msg2), 1);
        mq_send(msg_q, msg3, strlen(msg3), 2);
        printf("Successfully sent!\n");
    }
}
