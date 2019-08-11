#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 10000

int main()
{
	// 创建socket
	int sockfd = -1;
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		printf("create socket failed.\n");
		return -1;
	}

	// 绑定
	struct  sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
        	printf("bind error\n");
        	return(1);
    	}

	// 监听
	if(listen(sockfd, 5) < 0)
	{
	        printf("listen error\n");
        	return(1);
    	}		


	// 接受连接
	int clientfd = -1;
	struct  sockaddr_in client;
	socklen_t client_len = sizeof(client);
	while(1)
	{
		if ((clientfd = accept(sockfd, (struct sockaddr*)&client, &client_len)) < 0)
		{
			printf("accpet error\n");
			return(-1);

		}
		else
		{
			// 连接成功，接收（发送）数据
			char buff[100] = {0};
			if (recv(clientfd, buff, 100, 0) < 0)
				printf("recv error\n");
			else
				printf("recv buff: %s\n", buff);
			
			usleep(1000);
		}
	}
	

	return 0;
}
