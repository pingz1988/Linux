```C
/*
步骤：
1、通过 socket() 系统调用创建一个套接字；  
2、通过 connect() 系统调用将创建的套接字连接到TCP服务器上；  
3、数据收发；数据收发的方式有很多，其中最简单的方式是使用系统调用 read() 和 write() 进行数据收发；
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char* msg){
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

int main(int argc, char* argv[])
{
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  char buffer[256] = {0};

  if(argc < 3){
    // 使用客户端的方式为 ：执行文件名   主机名或IP   端口号
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(1);
  }
  portno = atoi(argv[2]);
  // 创建套接字
  sockfd = socket(AF_INET, SOCK_STREAM, 0);  
  if(sockfd == NULL) exit("Error opening socket");
  
  // 设置待连接服务器参数
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET ;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(portno);
  
  // 连接指定服务器
  if(connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
    error("Error connecting");
  printf("Please enter the massage : ");
  fgets(buffer, 255, stdin);
  // 向服务器发送数据
  n = write(sockfd, buffer, strlen(buffer));
  if(n < 0) error("Error writing to socket");
  memset(buffer, 0, 256);
  // 读取服务器发送过来的数据
  n = read(sockfd, buffer, 255);
  if(n < 0)
    error("Error reading from socket");
  printf("%s\n", buffer);
  return 0;
}
```
