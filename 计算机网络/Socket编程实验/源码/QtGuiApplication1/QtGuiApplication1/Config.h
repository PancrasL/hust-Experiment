#pragma once
#include <string>
#include <winsock2.h>
using namespace std;

//����������Ϣ
struct Config
{
    string SERVERADDRESS;   //��������ַ
	int PORT;				//�������˿�
	string HOMEDIR;			//��Ŀ¼
	int MAXCONNECTION;		//���������
	Config(string srvAddr, int Port, string HDir, int MaxCon)
	{
		SERVERADDRESS = srvAddr;
		PORT = Port;
		HOMEDIR = HDir;
		MAXCONNECTION = MaxCon;
	}
	Config(void) {};
	~Config(void) {};
};
