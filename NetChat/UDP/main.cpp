#include<Winsock2.h>
#include<stdio.h>
int main(int argc, char *argv[])
{
	//�����׽��ֿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);	//�����׽��ֿ�-����
	if (err != 0)
	{
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return -1;
	}

	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);	//��һ�������̶����ڶ�����������UDPЭ��
														//����������ָ��Ϊ0����ʾ�ú��������ݵ�ַ��ʽ���׽�������Զ�ѡ��һ�����ʵ�Э��

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("115.156.217.168");//inet_addr("115.156.216.215");//htonl(INADDR_ANY);//htonl()��һ��u_longֵ�������ֽ�˳��ת��ΪTCP/IP�������ֽ�˳��
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);	//Ϊ�������ָ���˿ں�-6000

	char recvbuff[100];
	char sendbuff[100];
	char tempbuff[200];

	int len = sizeof(SOCKADDR);
	while (1)
	{
		//��������
		printf("please input data:\n");
		gets(sendbuff);
		sendto(sockClient, sendbuff, strlen(sendbuff) + 1, 0, (SOCKADDR*)&addrSrv, len);
		//�ȴ�����������
		recvfrom(sockClient, recvbuff, 100, 0, (SOCKADDR*)&addrSrv, &len);
		if ('q' == recvbuff[0])
		{
			sendto(sockClient, "q", 2, 0, (SOCKADDR*)&addrSrv, len);
			printf("Chat end \
				\n");
			break;
		}
		//�ͻ���������ܵĵ�һ���ַ�����'q',���Ƚ���������������Ϣ��ʽ����ӡ����Ļ��
		sprintf(tempbuff, "%s say : %s", inet_ntoa(addrSrv.sin_addr), recvbuff);
		printf("%s\n", tempbuff);
	}
	//�ر��׽���
	closesocket(sockClient);
	WSACleanup();
	return 0;
}
