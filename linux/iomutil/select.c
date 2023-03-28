#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/select.h>

#define SERV_PORT 8080

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];

    struct sockaddr_in clie_addr, serv_addr;
    socklen_t clie_addr_len;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //SO_REUSEADDR允许重用本地地址端口

    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 128);

    fd_set rset, allset;
    int ret, maxfd = 0;
    maxfd = listenfd;
    FD_ZERO(&allset); //集合全部设为0
    FD_SET(listenfd, &allset);

    while (1)
    {
        rset = allset;
        ret = select(maxfd + 1, &rset, NULL, NULL, NULL); //返回有事件发生的个数
        if (FD_ISSET(listenfd, &rset))
        {
            clie_addr_len = sizeof(clie_addr);
            connfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
            printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)), ntohs(clie_addr.sin_port));

            FD_SET(connfd, &allset); //将一个集合中的事件“加入”
            if (maxfd < connfd)
                maxfd = connfd;
            if (ret == 1)
                continue; //说明select只返回一个，并且只是listenfd，无需后续执行
        }
        int n = 0;//read读到的字节数
        for (int i = listenfd + 1; i < maxfd + 1; ++i)
        {
            if (FD_ISSET(i, &rset)) //判断文件描述符是否在集合中
            {
                n = read(i, buf, sizeof(buf));
                if (n == 0)
                {
                    close(i);
                    FD_CLR(i, &allset); //将一个集合中的事件“拿走”
                }
                else if (n == -1)
                {
                }
                else
                    for (int j = 0; j < n; ++j)
                        buf[j] = toupper(buf[j]);
                write(i, buf, n);
                write(STDOUT_FILENO, buf, n);
                // write(STDOUT_FILENO,'\n',2);
            }
        }
    }

    close(listenfd);
    return 0;
}
