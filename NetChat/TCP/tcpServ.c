//#include<Winsock2.h>
//#include<stdio.h>
//#include<iostream>
//using namespace std;
//void main()
//{
//	�����׽��ֿ�
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	int err;
//	wVersionRequested = MAKEWORD(1, 1);
//
//	err = WSAStartup(wVersionRequested, &wsaData);	//�����׽��ֿ�-����
//	if (err != 0)
//	{
//		return;
//	}
//	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
//	{
//		WSACleanup();
//		return;
//	}
//	�������ڼ������׽���
//	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);	//��һ�������̶����ڶ�����������TCPЭ��
//														����������ָ��Ϊ0����ʾ�ú��������ݵ�ַ��ʽ���׽�������Զ�ѡ��һ�����ʵ�Э��
//
//	SOCKADDR_IN addrSrv;
//	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//htonl()��һ��u_longֵ�������ֽ�˳��ת��ΪTCP/IP�������ֽ�˳��
//	addrSrv.sin_family = AF_INET;
//	addrSrv.sin_port = htons(6000);	//Ϊ�������ָ���˿ں�-6000
//
//									���׽���
//	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//���׽���sockSrv�󶨵����ص�ַ��ָ���Ķ˿ں���
//														 ���׽�����Ϊ����ģʽ��׼�����ܿͻ�����
//	listen(sockSrv, 5);//�ɽ������������������Ϊ5
//
//	SOCKADDR_IN addrClient;
//	int len = sizeof(SOCKADDR);
//
//	while (1)
//	{
//		�ȴ��ͻ�������
//		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);//����addrClient�������ܿͻ��˵ĵ�ַ��Ϣ
//																		accept����һ�����׽��֣�sockSrv-���׽��������ڼ����ͻ��˵�����������ͻ���ͨ��
//		char sendbuff[100];
//		sprintf(sendbuff, "Welcome %s to http://www.sunxin.org",
//			inet_ntoa(addrClient.sin_addr));	//inet_ntoa()����һ���Ե��ʮ���Ƹ�ʽ��ʾ��IP��ַ�ַ���
//												��������
//		send(sockConn, sendbuff, strlen(sendbuff) + 1, 0);
//		char recvbuff[100];
//		��������
//		recv(sockConn, recvbuff, 100, 0);
//		��ӡ���ܵ�����
//		printf("%s\n", recvbuff);
//		�ر��׽���
//		closesocket(sockConn);
//
//	}
//
//}