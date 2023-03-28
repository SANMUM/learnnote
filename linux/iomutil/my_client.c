#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include<netdb.h>
#define SA struct sockaddr
#define PORT 8080
#define MAX 80
void func(int sockfd) { 
    char buff[MAX]; 
    int n; 
    for (;;) { 

        bzero(buff, sizeof(buff)); 
        printf("Enter the string : "); 
        n = 0; 
        //从控制台读取消息
        while ((buff[n++] = getchar()) != '\n') 
            ; 
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 

        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
int main(int argc,char **argv){
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if( sockfd == -1 ){
        printf("client socket create failed...\n");
    }
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if(connect(sockfd,(SA*) &server_addr,sizeof(server_addr)) !=0){
        printf("connect failed ...\n");
        exit(0);
    }
    else{
        printf("connect ok...\n");
    }

    func(sockfd); 
  
    // 关闭套接字
    close(sockfd); 
}
