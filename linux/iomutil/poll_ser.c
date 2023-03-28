#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int listen_fd, conn_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int ret, i;

    // 创建监听套接字
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 绑定地址和端口
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);
    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // 监听端口
    if (listen(listen_fd, SOMAXCONN) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // 创建pollfd数组
    struct pollfd fds[MAX_EVENTS];
    fds[0].fd = listen_fd;
    fds[0].events = POLLIN;

    // 循环等待事件
    while (1) {
        ret = poll(fds, MAX_EVENTS, -1);
        if (ret == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        // 遍历所有的文件描述符，处理事件
        for (i = 0; i < MAX_EVENTS; i++) {
            if (fds[i].revents == 0) {
                continue;
            }

            // 处理监听套接字的事件
            if (fds[i].fd == listen_fd) {
                // 接受客户端连接
                conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                if (conn_fd == -1) {
                    perror("accept");
                    continue;
                }

                // 将新连接添加到pollfd数组中
                for (i = 1; i < MAX_EVENTS; i++) {
                    if (fds[i].fd == -1) {
                        fds[i].fd = conn_fd;
                        fds[i].events = POLLIN;
                        break;
                    }
                }

                if (i == MAX_EVENTS) {
                    fprintf(stderr, "too many connections\n");
                    close(conn_fd);
                }
            } else {
                // 处理客户端连接的事件
                ret = recv(fds[i].fd, buffer, BUFFER_SIZE, 0);
                if (ret == -1) {
                    perror("recv");
                    continue;
                }

                if (ret == 0) {
                    // 客户端关闭连接
                    close(fds[i].fd);
                    fds[i].fd = -1;
                } else {
                    // 处理客户端发送的数据
                    
                    ret = send(fds[i].fd, buffer, ret, 0);
                    if (ret == -1) {
                        perror("send");
                    }
                }
            }
        }
    }

    return 0;
}

