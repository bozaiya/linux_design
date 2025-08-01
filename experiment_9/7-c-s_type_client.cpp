/*
编写一个以客户机/服务器模式工作的程序
要求在客户端读取系统文件/etc/passwd的内容，传送到服务器
服务器接收字符串，并在显示器显示出来
*/

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/fcntl.h>
#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
    int sockfd;            // 套接字
    int num;               // 接收大小
    char buf[MAXDATASIZE]; // 缓冲区
    // 头文件netinet/in.h
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

    // 读取/etc/passwd数据
    int fd;
    if ((fd = open("/etc/passwd", O_RDONLY)) == -1)
    {
        perror("open error.");
        exit(1);
    }

    while (1)
    {
        int ret = read(fd, buf, MAXDATASIZE);
        // 3、发送数据
        if ((num == send(sockfd, buf, strlen(buf), 0)) == -1)
        {
            printf("send() error\n");
            exit(1);
        } else {
            close(fd);
            break;
        }
    }
    printf("send successfully\n");
    close(sockfd);
    return 0;
}