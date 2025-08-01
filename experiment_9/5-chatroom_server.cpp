/*
编写基于TCP协议网络的聊天程序
要求发送程序和接收程序能够接收键盘输入并此之间相互发送数据
*/

#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BACKLOG 1
#define MAXSENDLEN 1024
#define MAXRECEVLEN 1024

int main()
{
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

    while (1)
    {
        // 5.接收发送数据
        char sendbuf[MAXSENDLEN];
        char recvbuf[MAXRECEVLEN];
        bzero(recvbuf, sizeof(recvbuf));
        bzero(sendbuf, sizeof(sendbuf));

        int len = recv(connectfd, recvbuf, MAXRECEVLEN, 0);
        if (strcmp(recvbuf,"exit\n") == 0)
        {
            break;
        }
        
        if (len > 0)
        {
            fputs(recvbuf, stdout);
        }
        printf("输入： ");
        fgets(sendbuf,sizeof(sendbuf), stdin);
        send(connectfd, sendbuf,strlen(sendbuf), 0);

        if (strcmp(sendbuf,"exit\n") == 0)
        {
            break;
        }

        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    close(connectfd);
    close(sockfd);
    return 0;
}