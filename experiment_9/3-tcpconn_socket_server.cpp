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

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *username = "admin";
    char *connection_msg = "Connection established.\n";

    // 创建套接字
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 绑定套接字到指定的IP地址和端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听连接请求
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // 接受连接请求
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // 读取用户名
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Received username: %s\n", buffer);

    // 验证用户名
    if (strcmp(buffer, username) == 0) {
        // 发送连接正确的消息
        send(new_socket, connection_msg, strlen(connection_msg), 0);

        // 显示客户端的IP地址和端口
        char *client_ip = inet_ntoa(address.sin_addr);
        int client_port = ntohs(address.sin_port);
        printf("Client IP: %s\n", client_ip);
        printf("Client Port: %d\n", client_port);
    } else {
        // 发送连接错误的消息
        char *error_msg = "Invalid username.\n";
        send(new_socket, error_msg, strlen(error_msg), 0);
    }

    close(new_socket);
    close(server_fd);

    return 0;
}