#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 64

struct msg_buffer {
   long msg_type;
   char msg[MSG_SIZE];
} message;

int main()
{

    key_t my_key = ftok("shmfile",65);// creates a unique key

    int msg_id = msgget(my_key, 0666 | IPC_CREAT); //gives identifier associated with key
    message.msg_type = 1;

    printf("Write Data : ");
    fgets(message.msg, MSG_SIZE-1, stdin);
    msgsnd(msg_id, &message, sizeof(message), 0);
    printf("Message passed: %s\n",message.msg);


    return 0;
}
