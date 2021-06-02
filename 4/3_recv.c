#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
    mqd_t msg_q;
    char str[10];
    struct mq_attr *attr = malloc(sizeof(struct mq_attr));
    int priority;

    msg_q = mq_open("/test_q", O_RDWR);

    if (msg_q == -1)
    {
        printf("Error!\n");
    }
    else
    {
        printf("Messages:\n");
        mq_getattr(msg_q, attr);

        mq_receive(msg_q, str, attr->mq_msgsize, &priority);
        printf("%s - %d\n", str, priority);
        mq_receive(msg_q, str, attr->mq_msgsize, &priority);
        printf("%s - %d\n", str, priority);
        mq_receive(msg_q, str, attr->mq_msgsize, &priority);
        printf("%s - %d\n", str, priority);
    }
}
