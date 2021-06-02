#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MSG_SIZE 64

struct msg_buffer {
   long msg_type;
   char msg[MSG_SIZE];
} message;

void cleanString(char* str) {
  int str_len=strlen(str);
  if(str[str_len-1]=='\n') {
    str[str_len-1]='\0';
  }
}
void pallindromeCheck(char* str) {
  int str_len=strlen(str);
  int flag=1;
  int check1=0;
  int check2=str_len-1;
  while(check1<check2) {
    if(str[check1]!=str[check2]) {
      flag=0;
      break;
    }
    check1++;
    check2--;
  }
  if(flag==1) {
    printf("String is pallindrome\n");
  }
  else {
    printf("String is not pallindrome\n");
  }

}
int main()
{

    key_t my_key;
    int msg_id;
    my_key = ftok("progfile", 65); //create unique key
    msg_id = msgget(my_key, 0666 | IPC_CREAT); //create message queue and return id
    msgrcv(msg_id, &message, sizeof(message), 1, 0);
    printf("Data by passing: %s\n",message.msg);
    cleanString(message.msg);
    pallindromeCheck(message.msg);

    msgctl(msg_id, IPC_RMID, NULL);


    return 0;
}
