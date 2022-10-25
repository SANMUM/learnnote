# 系统级I/O

1. 读写文件

   ![image-20221024214707935](./CSapp.assets/image-20221024214707935.png)

2. 共享文件

   - 描述符表：该进程打开的文件描述符来索引，每个打开的描述符表项指向**文件表**中的一个表项（每个进程一张表）

   - 文件表：打开文件的集合由该表表示，所有进程共享该表，表项有**当前文件的位置**、**引用计数**、**指向v-node表中对应表项的指针**

   - v-node表： 同文件表一样，所有进程共享该表，包含stat结构中的大多数信息，包括st_mode和st_size成员

     ![image-20221024214732629](./CSapp.assets/image-20221024214732629.png)

3. I/O重定向

   ![image-20221024215918467](./CSapp.assets/image-20221024215918467.png)

   ![image-20221024215939474](./CSapp.assets/image-20221024215939474.png)

   调用dup2(4,1)后，两描述符都指向B,即描述符oldfd，从此以后标准输出重定向到了文件B,newfd -> oldfd

4. 待定1

5. 待定2

6. 待定3

   # 网络编程

   1. 字节转换、IP地址和点分十进制转换
   
      ```c++
      #include<arpa/inet.h>
      uint32_t htonl(uint32_t hostlong);
      uint16_t htons(uint32_t hostshort);
      																								#返回：按照网络字节顺序的值
      uint32_t ntohl(uint32_t netlong)
      uint16_t ntohs(uint16_t netshort)		
          																							#返回：按照主机字节顺序的值
      int inet_pton(AF_INET,const char* src,void* dst);
      																	#返回：若成功则为1，若src为非法点分十进制则为0，若出错则为-1
      const char* inet_ntop(AF_INET,const void* src,char* dst,socklen_t size);
      																		#返回：若成功则指向点分十进制字符串的指针，若出错则为NULL
       
      ```
   
      "n"代表网络，"p"代表表示，"h"代表主机
   
   2. 套接字接口
   
      - 一个套接字就是通信的一个端点，套接字就是一个有相应描述符的打开文件，套接字地址存放在sockaddr_in的16个字节结构中，sin_family成员AF_INET，sin_port成员是一个16位的端口号，sin_addr成员就是一个32位的IP地址。IP地址和端口号总是以网络字节顺序（大端法）存放的
   
      ```C++
      /* IP socket address structure */
      struct sockaddr_in{
          uint16_t	sin_family;		/* Protocol family (always AF_INET) */
          uint16_t 	sin_port;		/* Port number in network byte order */
          struct in_addr sin_addr;	 /* IP address in network byte order */
          unsigned char sin_zero[8];	 /* Pad to sizeof(struct sockaddr)
      }
      
      /* generic socket address structure (for connect ,bind, and accept) */
      struct sockaddr {
          uint16_t sa_family;		/* Protocal family */
          char sa_data[14]; /*Address data */
      }
      ```
   
      - socket函数
   
        ```c++
        #include<sys/types.h>
        #include<sys/socket.h>
        int socket(int domain,int type,int protocol);
        #返回：若成功，则返回非负描述符，出错为-1
        ```
   
      - connect函数
   
        客户端通过调用connect函数建立和服务器的连接，connect试图和套接字地址为addr的服务器建立一个因特网
   
        ```c++
        #include<sys/socket.h>
        int connect(int clientfd,const struct sockaddr* addr,socklen_t addrlen);
        //返回:若成功则为0，出错则返回-1.
        ```
   
      - bind函数、listen函数和accept函数，服务器用它们来和客户端建立连接
   
        ```c++
        #include<sys/socket.h>
        int bind(int sockfd,const struct sockaddr* addr,socketlen_t addrlen);
        //返回：成功则为0，出错则为-1
        int listen(int sockfd,int backlog);
        //返回：若成功则为0，出错则为-1
        int accept(int listenfd,struct sockaddr* addr,int* addelen);
        //返回：若成功则为非负连接描述符，若出错则为-1
        ```
   
   3. 主机和服务转换
   
      - getaddrinfo()函数
   
        getaddrinfo函数将主机名、主机地址、服务明和端口号的字符串转化成套接字地址结构
   
        ![image-20221025161000986](./CSapp.assets/image-20221025161000986.png)
   
      - getnamenameinfo()函数
   
        getnameinfo函数与getaddrinfo函数是相反的，将一个套接字地址结构转换成相应的主机和服务名字符串
   
        ![image-20221025161411114](./CSapp.assets/image-20221025161411114.png)
   
   4. 待定四
   
      # 并发编程



