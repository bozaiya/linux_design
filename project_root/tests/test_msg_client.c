#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 100

struct message_buffer
{
    long message_type;
    char message_text[MAX_MESSAGE_SIZE];
};

int main()
{
    key_t key;
    int msgid;
    struct message_buffer message;

    // 生成一个唯一的key
    key = ftok("message_queue_program", 65);

    // 创建消息队列
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        printf("创建消息队列失败\n");
        return 1;
    }

    while (1)
    {
        printf("输入要发送的消息：\n");
        fgets(message.message_text, MAX_MESSAGE_SIZE, stdin);
        message.message_type = 1;

        // 发送消息到队列
        if (msgsnd(msgid, &message, sizeof(message), 0) == -1)
        {
            printf("发送消息失败\n");
            return 1;
        }

        if (strcmp(message.message_text, "exit\n") == 0)
        {
            break;
        }
    }

    return 0;
}

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512

int main()
{
    struct msg_st
    {
        int msg_type;
        char msg_text[MAX_TEXT];
    };

    struct msg_st senddata;
    key_t key;
    int msgid;
    char buf[80];

    if (key = ftok(".", 65) == -1)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    if (msgid = msgget(key, 0666 | IPC_CREAT) == -1)
    {
        printf("连接失败\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("Enter the message to sen: ");
        //fflush(stdin);
        scanf("%s", buf);
        senddata.msg_type = 1;
        strcpy(senddata.msg_text, buf);

        if ((msgsnd(msgid, (void *)&senddata, MAX_TEXT, 0)) == -1)
        {
            printf("发送失败");
            exit(EXIT_FAILURE);
        }
        if (strcmp(buf, "end") == 0)
        {
            break;
        }
    }
    return 0;
}
*/