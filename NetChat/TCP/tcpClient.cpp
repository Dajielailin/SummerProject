#include<Winsock2.h>
#include<stdio.h>
void main()
{
	//加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1,1);
	err = WSAStartup(wVersionRequested,&wsaData);
	if (err != 0)
	{
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return;
	}

	//创建套接字
	SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("115.156.217.168");//127.0.0.1是服务器的IP地址，
	//inet_addr()将点分十进制的IP地址转换为u_long型数据
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);	//客户端与服务器使用端口一致
	//向服务器发出请求连接
	connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

	//接收数据
	char recvbuff[100];
	recv(sockClient, recvbuff, 100, 0);
	printf("%s\n",recvbuff);
	//发送数据
	send(sockClient,"This is lusi",strlen("This is lusi")+1,0);
	//关闭套接字
	closesocket(sockClient);//释放套接字
	WSACleanup();			//终止对套接字的使用
	//while (1);
}