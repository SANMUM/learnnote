#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int ret;

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 连接服务器
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    server_addr.sin_port = htons(SERVER_PORT);
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // 发送数据
    strcpy(buffer, "Hello, world!");
    ret = send(sockfd, buffer, strlen(buffer), 0);
    if (ret == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    // 接收数据
    ret = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (ret == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    // 输出数据
    buffer[ret] = '\0';
    printf("Received: %s\n", buffer);

    // 关闭套接字
    close(sockfd);

    return 0;
}

