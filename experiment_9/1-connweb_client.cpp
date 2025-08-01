/*
编写一个客户端程序，使它能够连接到一个web服务器
请求一个文档，然后显示结果
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation error");
        return 1;
    }

    // 设置服务器地址和端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);  // 使用HTTP默认端口80
    if (inet_pton(AF_INET, "14.215.177.39", &(server_addr.sin_addr)) <= 0) {
        perror("Invalid address/ Address not supported");
        return 1;
    }

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    // 构造HTTP请求
    char request[BUFFER_SIZE];
    snprintf(request, BUFFER_SIZE, "GET /path/to/document HTTP/1.1\r\n"
                                   "Host: 14.215.177.39\r\n"
                                   "Connection: close\r\n"
                                   "\r\n");

    // 发送请求
    if (send(sockfd, request, strlen(request), 0) < 0) {
        perror("Request sending failed");
        return 1;
    }

    // 接收并显示响应
    char response[BUFFER_SIZE];
    memset(response, 0, BUFFER_SIZE);
    int bytes_received;
    while ((bytes_received = recv(sockfd, response, BUFFER_SIZE - 1, 0)) > 0) {
        printf("%s", response);
        memset(response, 0, BUFFER_SIZE);
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}