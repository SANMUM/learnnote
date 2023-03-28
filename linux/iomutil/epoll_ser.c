#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>

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

    // 创建epoll实例
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    // 添加监听套接字到epoll实例中
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listen_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev) == -1) {
        perror("epoll_ctl EPOLL_CTL_ADD");
        exit(EXIT_FAILURE);
    }

    // 创建epoll_event数组
    struct epoll_event events[MAX_EVENTS];

    // 循环等待事件
    while (1) {
        ret = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (ret == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        // 遍历所有的事件，处理事件
        for (i = 0; i < ret; i++) {
            if (events[i].data.fd == listen_fd) {
                // 处理监听套接字的事件
                conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                if (conn_fd == -1) {
                    perror("accept");
                    continue;
                }

                // 将新连接添加到epoll实例中
                ev.events = EPOLLIN;
                ev.data.fd = conn_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev) == -1) {
                    perror("epoll_ctl EPOLL_CTL_ADD");
                    continue;
                }
            } else {
                // 处理客户端连接的事件
                ret = recv(events[i].data.fd, buffer, BUFFER_SIZE, 0);
                if (ret == -1) {
                    perror("conne fail");
                } else if (ret == 0) {
                    // 客户端关闭连接
                    printf("client closed connection\n");
                    close(events[i].data.fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                } else {
                    // 输出接收到的数据
                    buffer[ret] = '\0';
                    printf("received %d bytes: %s", ret, buffer);

                    // 将接收到的数据回传给客户端
                    ret = send(events[i].data.fd, buffer, ret, 0);
                    if (ret == -1) {
                        perror("send");
                    }
                }
            }
        }
    }

    return 0;
}

