#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
 
 
#define MSG_ERR(msg) do{\
	fprintf(stderr, "line: %d ", __LINE__);\
	perror(msg);\
}while(0)
 
#define PORT 8080
#define IP   "192.168.1.104"
 
int main(int argc, const char *argv[])
{
	// 创建流式套接字
	int cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(cfd < 0)
	{
		MSG_ERR("socket");
		return -1;
	}
 
	// 绑定客户端自身的IP和端口（非必须）
	// 如果不绑定，程序运行后，由系统自动绑定
	
 
	// 填充要连接的服务器的地址信息结构体
	// 因为知道了服务器的信息 客户端才能连接服务器
	struct sockaddr_in sin;
	sin.sin_family       = AF_INET;
	sin.sin_port         = htons(PORT);
	sin.sin_addr.s_addr  = inet_addr(IP);
 
	// 连接服务器
	if(connect(cfd,(struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		MSG_ERR("connect");
		return -1;
	}
	printf("connect is success\n");
 
	char buf[128] = "";
	ssize_t res = 0;
 
	fd_set readfds, tempfds;
	FD_ZERO(&readfds);
	FD_ZERO(&tempfds);
 
	FD_SET(0,&readfds);
	FD_SET(cfd,&readfds);
 
	int maxfd = cfd;
 
	while(1)
	{
		tempfds = readfds;
		res = select(maxfd+1, &tempfds, NULL, NULL, NULL);
		if(res < 0)
		{
			MSG_ERR("select");
			return -1;
		}
		else if(0 == res)
		{
			printf("超时...\n");
			break;
		}
		
		// 运行到此处，集合中有文件描述符准备就绪
		// 下一步遍历判断
		for(int i=0; i <= maxfd; i++)
		{
			if(FD_ISSET(i, &tempfds) == 0)
			{
				continue;
			}
 
			// 运行到此处，已找到i表示的文件描述符
			// 从下面判断中选择，并运行
			if(0 == i)
			{
				// 从终端获取数据
				bzero(buf, sizeof(buf));
				printf("请输入：");
				fgets(buf, sizeof(buf), stdin);
				buf[strlen(buf)-1] = 0;
 
				// 发给服务器
				if(send(cfd, buf, sizeof(buf), 0) < 0)
				{
					MSG_ERR("send");
					return -1;
				}
				printf("发送成功\n");
			}
 
			else if(cfd == i)
			{
				// 从服务器收
				bzero(buf, sizeof(buf));
				res = recv(cfd, buf, sizeof(buf), 0);
				if(res < 0)
				{
					MSG_ERR("recv");
					return -1;
				}
				else if(0 == res)
				{
					printf("服务器退出\n");
					break;
				}
				printf("%s\n", buf);
			}
		}
	}
 
	// 关闭文件描述符
	close(cfd);
	return 0;
}