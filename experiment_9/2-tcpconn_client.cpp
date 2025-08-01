/*
编写一个基于TCP的服务器端程序，使服务器能够等待客户端的连接请求
一旦有客户端连接，服务器显示出客户端的IP地址和端口，并向服务器发送欢迎信息
*/

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
    int sockfd;    //套接字
    int num;    //接收大小
    char buf[MAXDATASIZE];  //缓冲区
    //头文件netinet/in.h
    struct sockaddr_in server;

    char *ip = "127.0.0.1";
    int port = 8080;

    // 1、创建socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket() error\n");
        exit(1);
    }
    
    // 头文件string.h
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // 头文件arpa/inet.h
    inet_pton(AF_INET, ip, &server.sin_addr);

    // 2、连接服务器地址
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        printf("connect() error\n");
        exit(1);
    }

    char *str = "hello server, I'm client";
    // 3、发送数据
    if ((num == send(sockfd, str, strlen(str),0)) == -1)
    {
        printf("send() error\n");
        exit(1);
    }

    close(sockfd);
    return 0;
}