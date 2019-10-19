#pragma once
#include <string>
#include <winsock2.h>
using namespace std;

//保存配置信息
struct Config
{
    string SERVERADDRESS;   //服务器地址
	int PORT;				//服务器端口
	string HOMEDIR;			//主目录
	int MAXCONNECTION;		//最大连接数
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
