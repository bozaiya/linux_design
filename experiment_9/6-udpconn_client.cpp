/*
编写基于UDP协议网络聊天程序要求发送程序和接收程序
能够接收键盘输入并彼此之间相互发送数据
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8888
#define MAXSIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server;

    // 1、创建socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) <  0)
    {
        perror("socket() error.");
        exit(1);
    }
    
    int addrlen = sizeof(struct sockaddr_in);
    bzero(&server, addrlen);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    char recvbuf[MAXSIZE];
    char sendbuf[MAXSIZE];
    bzero(recvbuf, MAXSIZE);
    bzero(sendbuf, MAXSIZE);

    while (1)
    {
        printf("输入: ");
        fgets(sendbuf, sizeof(sendbuf), stdin);
        sendto(sockfd, sendbuf, sizeof(sendbuf), 0, (struct sockaddr*)&server, addrlen);
        if (strcmp(sendbuf,"exit\n")== 0)
        {
            break;
        }

        recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0,(struct sockaddr*)&server, (socklen_t*) &addrlen);
        if (strcmp(recvbuf,"exit\n")== 0)
        {
            break;
        }
        fprintf(stdout,"%s\n", recvbuf);
      
        memset(recvbuf, 0, sizeof(recvbuf));
        memset(sendbuf, 0, sizeof(sendbuf));
    }
    close(sockfd);
    return 0;
}