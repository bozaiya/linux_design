/*
编写一个基于TCP的服务器端程序，使服务器能够等待客户端的连接请求
一旦有客户端连接，服务器显示出客户端的IP地址和端口，并向服务器发送欢迎信息
*/

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#define BACKLOG 1
#define MAXRECEVLEN 1024

int main(int argc, char *argv[])
{
    int listenfd, connectfd;   // 套接字
    struct sockaddr_in server; // 服务端地址
    struct sockaddr_in client; // 客户端地址

    char *ip = "127.0.0.1";
    int port = 8080;

    // 1、创建套接字
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket() error.");
        exit(1);
    }

    bzero(&server, sizeof(&server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    inet_pton(AF_INET, ip, &server.sin_addr);

    // 2、绑定套接字
    if (bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("bind() error.");
        exit(1);
    }

    // 3、监听套接字
    if (listen(listenfd, BACKLOG) == -1)
    {
        perror("listen() error.");
        exit(1);
    }

    socklen_t addrlen = sizeof(client);

    // 4、接收连接
    if ((connectfd = accept(listenfd, (struct sockaddr *)&client, &addrlen)) == -1)
    {
        perror("accept() error.");
        exit(1);
    }

    // 获取客户端的IP地址和端口
    char *client_ip = inet_ntoa(client.sin_addr);
    int client_port = ntohs(client.sin_port);
    printf("New client connected: %s:%d\n", client_ip, client_port);

    // 5.接收数据
    char buf[MAXRECEVLEN];
    bzero(buf, MAXRECEVLEN); // 先清空

    int ret = recv(connectfd, buf, MAXRECEVLEN, 0);
    if (ret > 0)
    {
        printf("%s", buf);
    }
    else
    {
        close(connectfd);
    }
    printf("\n");
    close(listenfd);
    return 0;
}