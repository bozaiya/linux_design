/*
使用套接字通信方式
实现从客户端发送一条消息后，服务器端接收这条消息并在服务器端显示
Receive message from客户端：********
*/

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXDATASIZE 1024

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
    
    char buf[MAXDATASIZE];
    // 3、发送数据
    fgets(buf, sizeof(buf), stdin);
    send(sockfd, buf, strlen(buf), 0);

    close(sockfd);
    exit(EXIT_SUCCESS);
    
    return 0;
}