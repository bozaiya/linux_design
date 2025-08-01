/*
编写基于TCP协议网络的聊天程序
要求发送程序和接收程序能够接收键盘输入并此之间相互发送数据
*/

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXSIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server;
    int port = 8080;

    // 1、创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket() error.");
        exit(1);
    }
    
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // 2、连接
    if (connect(sockfd, (struct sockaddr*)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("connect error.");
        exit(1);
    }
    
    char buf[MAXSIZE];
    
    while (1)
    {
        // 5.接收数据
        char sendbuf[MAXSIZE];
        char recvbuf[MAXSIZE];
        bzero(recvbuf, sizeof(recvbuf));
        bzero(sendbuf, sizeof(sendbuf));

        printf("输入: ");
        fgets(sendbuf,sizeof(sendbuf), stdin);
        send(sockfd, sendbuf,strlen(sendbuf), 0);

        int len = recv(sockfd, recvbuf, MAXSIZE, 0);
        if (strcmp(recvbuf,"exit\n") == 0)
        {
            break;
        }
        
        if (len > 0)
        {
            fputs(recvbuf, stdout);
        }

        if (strcmp(sendbuf,"exit\n") == 0)
        {
            break;
        }
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));


    }

    close(sockfd);
    exit(EXIT_SUCCESS);
    
    return 0;
}