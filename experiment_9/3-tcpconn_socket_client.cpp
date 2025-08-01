/*
编写一个基于TCP协议的网络通信程序
要求服务器通过套接字连接、要求输出用户名
判断用户名正确后，向客户端发送连接正确的字符串，在服务器显示客户端的IP地址和端口
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};
    char *username = "admin";

    // 创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // 将IP地址转换为二进制格式
    if (inet_pton(AF_INET, SERVER_IP, &(server_address.sin_addr)) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    // 发送用户名
    send(sockfd, username, strlen(username), 0);

    // 接收服务器的响应
    read(sockfd, buffer, BUFFER_SIZE);
    printf("%s\n", buffer);

    close(sockfd);

    return 0;
}