#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <string.h> 
#define PORT 8080
#define SA struct sockaddr 
#define MAX 80
void func(int sockfd){
    char buff[MAX];
    int n;
    while (1)
    {
        bzero(buff,MAX);
        read(sockfd,buff,sizeof(buff));
        printf("From client: %s \t \n",buff);
        bzero(buff,MAX);
        n = 0;
        while ((buff[n++] = getchar()) !='\n');
        write(sockfd,buff,sizeof(buff));

        if(strncmp("exit",buff,4) == 0){
            printf("server Exit...\n");
            break;
        }

        

    }
    

}
int main(int argc, char **argv){
    //declared some file description
    int sockfd,connfd;
    socklen_t len;
    //decleared server and client address
    struct sockaddr_in servaddr, cliaddr; 
    // create socket word
    sockfd = socket(AF_INET,SOCK_STREAM,0); 
    if (sockfd == -1){
        printf("socket creation fail...\n");
        exit(0);
    }
    else{
        printf("socket ok!\n");
    }
    //initial server address,such as ip, port and protocol
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htonl(PORT);

    // bind specific ip and port with socket
    if(bind(sockfd,(SA *)&servaddr,sizeof(servaddr)) != 0){
        printf("blind failed ...\n");
        exit(0);
    }
    else{
        printf("Socket bind done...\n");
    }


    // 现在服务器已经准备好监听
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    //deal with resuests from client
    len = sizeof(cliaddr);
    connfd = accept(sockfd,(SA *) &cliaddr,&len);
    if(connfd <0 ){
        printf("server accept failed...\n");
        exit(0);
    } 
    else{
        printf("server accept done...\n ");
    }
    func(connfd);

    close(sockfd);

}