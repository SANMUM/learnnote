
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
  

void func(int sockfd) { 
    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX); 
  
        //读取客户端发送的消息
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        //将读取内容原封不动地发送回去
        while ((buff[n++] = getchar()) != '\n') 
            ; 
  
        // 将缓冲区发送给客户端
        write(sockfd, buff, sizeof(buff)); 
  
        // 如果msg包含“exit”，那么服务器退出和聊天结束。
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 
  
int main(int argc, char const *argv[]){

    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    //初始化服务端socket信息
    bzero(&servaddr, sizeof(servaddr)); 
  
    //使用默认的ip和port 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    //绑定指定ip和端口
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // 现在服务器已经准备好监听
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
  
     //处理来自客户端的连接
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
  

    func(connfd); 
  
    // 关闭套接字
    close(sockfd); 
} 

