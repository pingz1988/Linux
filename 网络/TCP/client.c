#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define IP	"127.0.0.1"
#define PORT	10000


int main()
{
	int sockfd = -1;
	struct sockaddr_in server;

	// 创建socket
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		printf("create socket failed.\n");
		return -1;
	}
		
	// 连接server
	memset(&server, 0, sizeof(server));      /* Clear struct */
	server.sin_family = AF_INET;		 /* Internet/IP */
	server.sin_addr.s_addr = inet_addr(IP);  /* IP address */
	server.sin_port = htons(PORT);		 /* server port */
	if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		printf("connect server failed.\n");
		return -1;
	}
	
	
	printf("connect server success.\n");
	
	// 发送数据
	char *data = "123456";
	int len = strlen(data);
	if (len != send(sockfd, data, len, 0))
	{
		printf("missing data when send to server.\n");
		return -1;
	}

	printf("send data success. data: %s\n", data);	
	usleep(3000);	

	return 0;
}
