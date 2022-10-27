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

1. 待定以
2. 待定二
3. 待定三

# 信息的表示和处理

1. 信息存储

   - 每台计算机都有一个字长，指明指针的标称大小，虚拟地址是以这样的一个字来编码，字长决定的最重要的系统参数是虚拟地址空寂的最大大小，对于字长为w位的机器，虚地址空间范围为0~$2^w-1$,程序最多访问$2^w$个字节

2. 大端机和小端机

   - 在内存中按照从低有效字节到最高有效字节的顺序存储对象称为小端法(little endian);在内存中从最高有效字节到最低有效字节的顺序存储称为大端法(big endian)。0x01234567在两种不同机器的存储方式

     ![image-20221026111330197](./CSapp.assets/image-20221026111330197.png)

     ```c++
     typedef unsigned char *byte_pointer;
     void show_bytes(byte_pointer start, size_t len) {
         size_t i;
         for (i = 0; i < len; i++)
     	printf("%p\t0x%.2x\n", &start[i], start[i]); 
         printf("\n");
     }
     void show_int(int x) {
         show_bytes((byte_pointer) &x, sizeof(int)); 
     }
     void show_float(float x) {
         show_bytes((byte_pointer) &x, sizeof(float));
     }
     void show_pointer(void *x) {
         show_bytes((byte_pointer) &x, sizeof(void *));
     }
     /* $end show-bytes */
     
     ```

3. 浮点数表示

   标准：$V = (-1)^s*M*2^E$

   - 符号(sign)，s=0是正数，s=1是负数，数值0的符号位解释作为特殊处理
   - 尾数(significand)，M是一个二进制小数，范围是1~2-ε，或者0 ~ 1-ε
   - 阶码(exponent)，E的作用是对浮点数加权，权重是2的E次幂(可能是负数)，将浮点数的位表示划分三个字段，分别对这些值编码
   - k位阶码字段exp=e~k-1~...e~1~e~0~编码阶码E
   - n位小数字段frac=f~n-1~...f~1~f~0~编码尾数M，但是编码出来的值也依赖阶码字段的值是否等于0

   两种常见格式: 单精度：1、8、23；双精度：1、11、52

   ![image-20221026134426575](./CSapp.assets/image-20221026134426575.png)

    根据exp的值，被编码的值分成三种不同的情况

   ![image-20221026134746574](./CSapp.assets/image-20221026134746574.png)

   - 规格化值

     当exp的位模式不全为0也不全为1，E = e - bias，其中e为无符号数，Bias等于$2^k-1^-1$(单精度127，双精度1023)，即单精度阶码E的取值范围为-126~127，双精度阶码E的取值范围为-1022-1023

     小数字段frac被描述为小数值f,其中0≤f<1，其二进制表示0.f~n-1~...f~1~f~0~，尾数定义M = 1+f。这种方式叫做隐含开头1的表示，通过调整阶码E,使M 的范围在1≤M<2

   - 非规格化值

     阶码全为0时，阶码值E=1-Bias，尾数的值为M=f，不包含隐含的开头1

   - 特殊值

     阶码全为1的时候，小数域全为0，得到的值表示无穷，当s=0时，表示+∞，s = 1时，表示-∞。当小数域为非零时，表示NAN

4. 待定

5. 待定

6. 待定

# 程序机器级表示

1. x86整数寄存器

   ![image-20221026142307286](./CSapp.assets/image-20221026142307286.png)

   对于一般函数来说，第一个参数存放在 %rdi，第二个参数存放到 %rsi 中，第三个参数存在%rdx，从函数中返回结果存放到 %rax 中

   - movq A,B指令

     ![image-20221026143224965](./CSapp.assets/image-20221026143224965.png)

     (%rax)表示rax寄存器中存储的为一个内存地址，使用()表示去除这个内存中的数据

     D(%rax)` 表示在这个内存地址上进行偏移，然后取出内容，相当于 `(%rax + D)

     D(%rax, %rbx, S)` 相当于 `(%rax + s * %rbx + d)`，其中 %rbx 不可以被替换为 rsp, S 只能取 1,2,4,8

     ![image-20221026143636046](./CSapp.assets/image-20221026143636046.png)

     ![image-20221026143653481](./CSapp.assets/image-20221026143653481.png)

   - leaq指令 ： 从内存数据读到寄存器

     leaq src,dst

     src通常是个表达式，用于将表达式计算结果存放到dst中

     ```c++
     leaq (%rdi, %rdi, 2), %rax	# t = x + x * 2
     salq $2, %rax	# t << 2
     ```

     区别 ：假设eax存放的是地址，leaq (eax+2*eax),eax 表示将内存地址为eax的值的3倍放到eax中，相当于创建指针并解引用；movq (eax+2*eax),eax 表示取内存地址eax+2*eax里面的值放到eax里面，至于值是什么，不知道M[.....]

   - 位标记(控制流中)

     1. CF，Carry Flag 表示进位标记，用于 unsigned 类型
     2. SF，Sign Flag，用于 signed 类型，表示 if res < 0
     3. ZF，Zero Flag，计算结果为 if res == 0
     4. OF，Overflow Flag，用于 signed 类型，判断补码是否溢出 (a > 0 && b > 0 & res < 0) || (a < 0 && b < 0 && t >= 0)

   - compq b,a

     计算a-b的并且不改变结果，只产生位标记

   - testq a,b

     用于计算a&b，通常与自身比较，testq a,a

     ZF = 1 if a & b == 0

     SF = 1 if a & b < 0

   - set指令

     ![image-20221026162019966](./CSapp.assets/image-20221026162019966.png)

     setne %rax 将ZF标志位取反存放到rax寄存器中

   - movzbl %al, %eax

     movzbl 全称 move with zero extension byte to long，将 al 中的值移到 eax 中，并且将剩余位置零。

     setg %al   当>时，将al设置为1

     ![image-20221026164455811](./CSapp.assets/image-20221026164455811.png)

   - J*指令 跳转指令

     ![image-20221026164748327](./CSapp.assets/image-20221026164748327.png)

     ![image-20221026165103769](./CSapp.assets/image-20221026165103769.png)

2. **procedures过程调用**

   - 控制执行流程(stack)

     1. 过程调用(call)：rip存放当前执行指令的地址，遇到call指令，会发生三件事，rip的值更新为call label中的指令地址，栈指针减少8(64位机)，并且将调用之后的栈指针地址写入栈顶部

     2. 返回地址：   rip执行call指令，直至遇到ret

     3. 过程返回(ret)：ret逆转call效果，假定栈顶部有一个想要跳转的地址，rip值更新为栈顶(call中栈指针减少后的那个)，此时从栈中pop出该地址，栈指针增加，然后继续按照原来的方式继续运行

        `ret指令将始终采取栈指针指向的地址并将它作为返回地址`

   - 传递数据

     对于函数传递参数来说，前 6 个参数分别传递给 rdi, rsi, rdx, rcx, r8, r9 寄存器，之后的参数传递到栈中；返回值传递到 rax 中。对于浮点数会有专门的寄存器

   - 管理局部参数

     通常这些参数和环境变量会存储在栈的每一个对应的栈帧中。 

   - 寄存器保存规则

     1. `Caller Saved`：调用者在调用 `call` 命令之前将临时值保存到其栈帧中。%r10，%r11

     2. `Callee Saved`：被调用者在被调用之前将临时值保存到栈帧中，结束调用时候恢复调用者栈帧中的临时变量。%rbx，%rbp,%r12~%r14

        ![image-20221026221620950](./CSapp.assets/image-20221026221620950.png)

        当进行函数调用时，会将调用者的信息（临时变量，可选参数，调用者和被调用者寄存器信息，返回地址）等入栈，等待被调用者函数执行完毕再恢复原状。

   - 待定

3. 
