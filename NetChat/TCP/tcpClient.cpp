#include<Winsock2.h>
#include<stdio.h>
void main()
{
	//�����׽��ֿ�
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

	//�����׽���
	SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("115.156.217.168");//127.0.0.1�Ƿ�������IP��ַ��
	//inet_addr()�����ʮ���Ƶ�IP��ַת��Ϊu_long������
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);	//�ͻ����������ʹ�ö˿�һ��
	//�������������������
	connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

	//��������
	char recvbuff[100];
	recv(sockClient, recvbuff, 100, 0);
	printf("%s\n",recvbuff);
	//��������
	send(sockClient,"This is lusi",strlen("This is lusi")+1,0);
	//�ر��׽���
	closesocket(sockClient);//�ͷ��׽���
	WSACleanup();			//��ֹ���׽��ֵ�ʹ��
	//while (1);
}