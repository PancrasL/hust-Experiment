#pragma once
#include <winsock2.h>
#include <string>
#include<Config.h>
#pragma comment(lib, "Ws2_32.lib")
#define BUF_SIZE 65536
#define BUF_SMALL 100
#define MAJORVERSION 2  //Winsock主版本号
#define MINORVERSION 2	//Winsock次版本号
//服务器
class Server
{
private:
	SOCKET newSocket;					//实际与客户端连接的socket
	sockaddr_in srvAddr,clientAddr;		//服务器端、客户端IP地址
	int clientAddrSize;					//客户端地址结构的大小
public:
	SOCKET srvSocket;					//服务器socket
	Server(void);
	virtual ~Server(void);
	virtual int WinsockStartup();		//初始化Winsock
	virtual int ServerStartup();		//初始化Server，包括创建SOCKET，绑定到IP和PORT
	virtual int ListenStartup();		//开始监听客户端请求
	virtual int Loop();					//循环执行"等待客户端请求"->“新建线程回复报文”->”等待客户端请求“
	virtual void setConfig(Config cfg);//设置服务器配置
	virtual Config getConfig();			//获取服务器配置
};
