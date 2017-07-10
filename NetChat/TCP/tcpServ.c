//#include<Winsock2.h>
//#include<stdio.h>
//#include<iostream>
//using namespace std;
//void main()
//{
//	加载套接字库
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	int err;
//	wVersionRequested = MAKEWORD(1, 1);
//
//	err = WSAStartup(wVersionRequested, &wsaData);	//加载套接字库-核心
//	if (err != 0)
//	{
//		return;
//	}
//	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
//	{
//		WSACleanup();
//		return;
//	}
//	创建用于监听的套接字
//	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);	//第一个参数固定，第二个参数基于TCP协议
//														第三个参数指定为0，表示该函数将根据地址格式和套接字类别，自动选择一个合适的协议
//
//	SOCKADDR_IN addrSrv;
//	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//htonl()将一个u_long值从主机字节顺序转换为TCP/IP的网络字节顺序
//	addrSrv.sin_family = AF_INET;
//	addrSrv.sin_port = htons(6000);	//为网络程序指定端口号-6000
//
//									绑定套接字
//	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//把套接字sockSrv绑定到本地地址和指定的端口号上
//														 将套接字设为监听模式，准备接受客户请求
//	listen(sockSrv, 5);//可接受连接请求的最大个数为5
//
//	SOCKADDR_IN addrClient;
//	int len = sizeof(SOCKADDR);
//
//	while (1)
//	{
//		等待客户请求到来
//		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);//利用addrClient变量接受客户端的地址信息
//																		accept返回一个新套接字（sockSrv-旧套接字仍用于监听客户端的链接请求）与客户端通信
//		char sendbuff[100];
//		sprintf(sendbuff, "Welcome %s to http://www.sunxin.org",
//			inet_ntoa(addrClient.sin_addr));	//inet_ntoa()返回一个以点分十进制格式表示的IP地址字符串
//												发送数据
//		send(sockConn, sendbuff, strlen(sendbuff) + 1, 0);
//		char recvbuff[100];
//		接收数据
//		recv(sockConn, recvbuff, 100, 0);
//		打印接受的数据
//		printf("%s\n", recvbuff);
//		关闭套接字
//		closesocket(sockConn);
//
//	}
//
//}