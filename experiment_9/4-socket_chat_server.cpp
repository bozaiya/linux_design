/*
使用套接字通信方式
实现从客户端发送一条消息后，服务器端接收这条消息并在服务器端显示
Receive message from客户端：********
*/

#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BACKLOG 1
#define MAXRECEVLEN 1024

int main()
{
    int port = 8080;

    int sockfd,connectfd; //套接字
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
    if (bind(sockfd, (struct sockaddr *) &server, sizeof(struct sockaddr)) < 0)
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
    
    // 5.接收数据
    char buf[MAXRECEVLEN];
    bzero(buf, sizeof(buf));
    printf("Receive message from客户端: ");

    int ret = recv(connectfd, buf, MAXRECEVLEN, 0);
    if (ret > 0)
    {
        fputs(buf, stdout);
    }
    
    close(connectfd);
    close(sockfd);
    return 0;
}