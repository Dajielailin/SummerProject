/*�������˶Խ��ܵ����ݽ����жϣ�����ͻ��˷������������ǡ�q��,
	�������ظ�һ��"q"��������ֹ��
	���򣬷����������յ�����Ϣ�ͶԷ���IP��ַ��ʽ����ӡ����Ļ�ϣ�Ȼ��ͨ�����̻ظ���Ϣ
*/
//ע��ʹ���׽��֣�Ҫ�򹤳������ws2_32.lib���ļ���������
// �Ҽ�������->build options->linker settings->add(C/program files(x86)/Microsoft SDKs/windows����ws2_32.lib�ļ�)
#include<Winsock2.h>
#include<stdio.h>
int  main(int argc, char *argv[])
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

	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);	//��һ�������̶����ڶ�����������UDPЭ��
														//����������ָ��Ϊ0����ʾ�ú��������ݵ�ַ��ʽ���׽�������Զ�ѡ��һ�����ʵ�Э��

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("115.156.217.168");//inet_addr("115.156.216.215");//htonl(INADDR_ANY);//htonl()��һ��u_longֵ�������ֽ�˳��ת��ΪTCP/IP�������ֽ�˳��
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);	//Ϊ�������ָ���˿ں�-6000

	//���׽���
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//���׽���sockSrv�󶨵����ص�ַ��ָ���Ķ˿ں���
														 //���׽�����Ϊ����ģʽ��׼�����ܿͻ�����
	//listen(sockSrv, 5);//�ɽ������������������Ϊ5
	char recvbuff[100];
	char sendbuff[100];
	char tempbuff[100];

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		//�ȴ�����������
		recvfrom(sockSrv,recvbuff,100,0,(SOCKADDR*)&addrClient,&len);
		if ('q' == recvbuff[0])
		{
			sendto(sockSrv,"q",strlen("q")+1,0,(SOCKADDR*)&addrClient,len);
			printf("Chat end!\n");
			break;
		}
		//������ܵĵ�һ���ַ�����'q',�������Ȱѿͻ��˷������ݴ�ӡ����
		sprintf(tempbuff,"%s say : %s",inet_ntoa(addrClient.sin_addr),recvbuff);
		//inet_ntoa()��һ����in�ṹ�洢�����������ַת��Ϊ�Ե��ʮ���Ʊ�ʾ���ַ���
		printf("%s\n",tempbuff);
		//Ȼ��Ӽ������룬���͸��ͻ���
		printf("Please input data:\n");
		gets(sendbuff);
		sendto(sockSrv,sendbuff,strlen(sendbuff)+1,0,(SOCKADDR*)&addrClient,len);

	}
	//�ر��׽���
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}
