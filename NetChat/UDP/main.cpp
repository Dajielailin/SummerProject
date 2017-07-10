/*服务器端对接受的数据进行判断，如果客户端发送来的数据是“q”,
	服务器回复一个"q"，聊天终止；
	否则，服务器将接收到的信息和对方的IP地址格式化打印到屏幕上，然后通过键盘回复消息
*/
//注意使用套接字，要向工程中添加ws2_32.lib库文件，方法：
// 右键工程名->build options->linker settings->add(C/program files(x86)/Microsoft SDKs/windows搜索ws2_32.lib文件)
#include<Winsock2.h>
#include<stdio.h>
int  main(int argc, char *argv[])
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

	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);	//第一个参数固定，第二个参数基于UDP协议
														//第三个参数指定为0，表示该函数将根据地址格式和套接字类别，自动选择一个合适的协议

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("115.156.217.168");//inet_addr("115.156.216.215");//htonl(INADDR_ANY);//htonl()将一个u_long值从主机字节顺序转换为TCP/IP的网络字节顺序
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);	//为网络程序指定端口号-6000

	//绑定套接字
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//把套接字sockSrv绑定到本地地址和指定的端口号上
														 //将套接字设为监听模式，准备接受客户请求
	//listen(sockSrv, 5);//可接受连接请求的最大个数为5
	char recvbuff[100];
	char sendbuff[100];
	char tempbuff[100];

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		//等待并接收数据
		recvfrom(sockSrv,recvbuff,100,0,(SOCKADDR*)&addrClient,&len);
		if ('q' == recvbuff[0])
		{
			sendto(sockSrv,"q",strlen("q")+1,0,(SOCKADDR*)&addrClient,len);
			printf("Chat end!\n");
			break;
		}
		//如果接受的第一个字符不是'q',服务器先把客户端发送内容打印出来
		sprintf(tempbuff,"%s say : %s",inet_ntoa(addrClient.sin_addr),recvbuff);
		//inet_ntoa()将一个以in结构存储的主机网络地址转换为以点分十进制表示的字符串
		printf("%s\n",tempbuff);
		//然后从键盘输入，发送给客户端
		printf("Please input data:\n");
		gets(sendbuff);
		sendto(sockSrv,sendbuff,strlen(sendbuff)+1,0,(SOCKADDR*)&addrClient,len);

	}
	//关闭套接字
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}
