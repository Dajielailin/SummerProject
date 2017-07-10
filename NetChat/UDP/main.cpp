#include<Winsock2.h>
#include<stdio.h>
int main(int argc, char *argv[])
{
	//加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);	//加载套接字库-核心
	if (err != 0)
	{
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return -1;
	}

	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);	//第一个参数固定，第二个参数基于UDP协议
														//第三个参数指定为0，表示该函数将根据地址格式和套接字类别，自动选择一个合适的协议

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("115.156.217.168");//inet_addr("115.156.216.215");//htonl(INADDR_ANY);//htonl()将一个u_long值从主机字节顺序转换为TCP/IP的网络字节顺序
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);	//为网络程序指定端口号-6000

	char recvbuff[100];
	char sendbuff[100];
	char tempbuff[200];

	int len = sizeof(SOCKADDR);
	while (1)
	{
		//发送数据
		printf("please input data:\n");
		gets(sendbuff);
		sendto(sockClient, sendbuff, strlen(sendbuff) + 1, 0, (SOCKADDR*)&addrSrv, len);
		//等待并接收数据
		recvfrom(sockClient, recvbuff, 100, 0, (SOCKADDR*)&addrSrv, &len);
		if ('q' == recvbuff[0])
		{
			sendto(sockClient, "q", 2, 0, (SOCKADDR*)&addrSrv, len);
			printf("Chat end \
				\n");
			break;
		}
		//客户端如果接受的第一个字符不是'q',则先将服务器发来的消息格式化打印到屏幕上
		sprintf(tempbuff, "%s say : %s", inet_ntoa(addrSrv.sin_addr), recvbuff);
		printf("%s\n", tempbuff);
	}
	//关闭套接字
	closesocket(sockClient);
	WSACleanup();
	return 0;
}
