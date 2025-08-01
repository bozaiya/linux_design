/*与其他进程通信*/
#include "communicate_pid.h"

void funciton_communicate()
{
    int flag = 1;
    int choice;

    while (flag)
    {
        printf("*1.receive message**\n");
        printf("*2.chat with others*\n");
        printf("******3.exit******\n");
        printf("~: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            /*消息队列*/
            key_t key;
            int msgid;
            struct message_buffer message;

            // 生成一个唯一的key
            key = ftok("message_queue_program", 65);

            // 连接到消息队列
            msgid = msgget(key, 0666 | IPC_CREAT);
            if (msgid == -1)
            {
                printf("连接消息队列失败\n");
                exit(EXIT_FAILURE);
            }

            while (1)
            {
                // 接收消息
                if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1)
                {
                    printf("接收消息失败\n");
                    exit(EXIT_FAILURE);
                }

                if (strcmp(message.message_text, "exit\n") == 0)
                {
                    break;
                }

                printf("接收到的消息：%s", message.message_text);
            }

            // 删除消息队列
            if (msgctl(msgid, IPC_RMID, NULL) == -1)
            {
                printf("删除消息队列失败\n");
                exit(EXIT_FAILURE);
            }

            break;

        case 2:
            int port = 8080;

            int sockfd, connectfd; // 套接字
            struct sockaddr_in server;
            struct sockaddr_in client;

            // 1、创建socket
            if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            {
                perror("sock() error.");
                exit(1);
            }

            server.sin_family = AF_INET;
            server.sin_port = htons(port);
            server.sin_addr.s_addr = htonl(INADDR_ANY);

            // 2、绑定socket
            if (bind(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) < 0)
            {
                perror("bind() error");
                exit(1);
            }

            // 3、监听
            if (listen(sockfd, BACKLOG) == -1)
            {
                perror("listen() error");
                exit(1);
            }

            socklen_t addrlen = sizeof(client);
            // 4、连接
            if ((connectfd = accept(sockfd, (struct sockaddr *)&client, &addrlen)) == -1)
            {
                perror("accept error.");
                exit(1);
            }

            char sendbuf[MAXSENDLEN];
            char recvbuf[MAXRECEVLEN];
            int c = 1;
            while (1)
            {
                bzero(recvbuf, sizeof(recvbuf));
                bzero(sendbuf, sizeof(sendbuf));
                // 5.接收数据
                int len = recv(connectfd, recvbuf, MAXRECEVLEN, 0);
                
                // 吃接收到的第一次回车
                if (c == 1)
                {
                    getchar();
                    c = 0;
                }  

                if (strcmp(recvbuf, "exit\n") == 0)
                {
                    break;
                }

                if (len > 0)
                {
                    fputs(recvbuf, stdout);
                }

                memset(recvbuf, 0, sizeof(recvbuf));

                // 6.发送数据
                printf("输入： ");
                fgets(sendbuf, sizeof(sendbuf), stdin);
                send(connectfd, sendbuf, strlen(sendbuf), 0);

                if (strcmp(sendbuf, "exit\n") == 0)
                {
                    break;
                }

                memset(sendbuf, 0, sizeof(sendbuf));
            }

            close(connectfd);
            close(sockfd);

            break;

        case 3:
            flag = 0;
            break;
        }
    }
}
