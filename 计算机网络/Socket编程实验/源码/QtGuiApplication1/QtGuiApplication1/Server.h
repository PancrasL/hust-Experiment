#pragma once
#include <winsock2.h>
#include <string>
#include<Config.h>
#pragma comment(lib, "Ws2_32.lib")
#define BUF_SIZE 65536
#define BUF_SMALL 100
#define MAJORVERSION 2  //Winsock���汾��
#define MINORVERSION 2	//Winsock�ΰ汾��
//������
class Server
{
private:
	SOCKET newSocket;					//ʵ����ͻ������ӵ�socket
	sockaddr_in srvAddr,clientAddr;		//�������ˡ��ͻ���IP��ַ
	int clientAddrSize;					//�ͻ��˵�ַ�ṹ�Ĵ�С
public:
	SOCKET srvSocket;					//������socket
	Server(void);
	virtual ~Server(void);
	virtual int WinsockStartup();		//��ʼ��Winsock
	virtual int ServerStartup();		//��ʼ��Server����������SOCKET���󶨵�IP��PORT
	virtual int ListenStartup();		//��ʼ�����ͻ�������
	virtual int Loop();					//ѭ��ִ��"�ȴ��ͻ�������"->���½��̻߳ظ����ġ�->���ȴ��ͻ�������
	virtual void setConfig(Config cfg);//���÷���������
	virtual Config getConfig();			//��ȡ����������
};
