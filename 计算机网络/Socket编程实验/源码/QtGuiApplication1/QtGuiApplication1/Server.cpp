#pragma once
#include "Server.h"
#include <process.h>
#include "Config.h"
#include<qdebug.h>
#include<mutex>
static Config config;
int flag = 1;
extern mutex L;
Server::Server(void)
{
}
Server::~Server(void)
{
	WSACleanup(); //清理winsock 运行环境
}
struct Parameter
{
	SOCKET sock;
	string msg;
};
unsigned WINAPI ProcessRequest(void *arg);					//处理请求
unsigned WINAPI StopServer(void *arg);
void SendErrorMSG(SOCKET sock,string error="error");		//收到的请求错误，回复错误信息
string SendData(SOCKET sock, const string &filename);		//回复报文
string ComtentType(string filename);
//初始化Winsock
int Server::WinsockStartup(){
	WSADATA wsaData;//用于返回Winsock的环境信息   
	int rtn;		//Winsock初始化函数的返回值
	WORD  wVersionRequested = MAKEWORD(MAJORVERSION, MINORVERSION); //Winsock版本号，高字节次版本，低字节主版本号

	//初始化 winsock
	rtn = WSAStartup(wVersionRequested, &wsaData);

	if (rtn) { //如果返回值不是0，则Winsock初始化失败
		L.lock();
		qDebug() << "Winsock startup error!\n";
		L.unlock();
		return -1;
	}

	//判断返回的Winsock版本号
	if (LOBYTE(wsaData.wVersion) != MAJORVERSION || HIBYTE(wsaData.wVersion) != MINORVERSION) { //如果版本不对
		WSACleanup();  //清除Winsock
		L.lock();
		qDebug() << "Winsock version error!\n";
		L.unlock();
		return -1;
	}
	L.lock();
	qDebug() << "Winsock startup ok!\n";
	L.unlock();
	return 0;
}

//初始化Server，包括创建sockect，绑定到IP和PORT
int Server::ServerStartup(){
	//创建 TCP socket
	this->srvSocket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
	if(this->srvSocket == INVALID_SOCKET){
		L.lock();
		qDebug() << "Server socket creare error !\n";
		L.unlock();
		WSACleanup();
		return -1;
	}
	L.lock();
	qDebug() << "Server socket create ok!\n";
	L.unlock();
	//设置服务器IP地址和端口号
	this->srvAddr.sin_family = AF_INET;
	this->srvAddr.sin_port =  htons(config.PORT);
	//this->srvAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//会自动找到服务器合适的IP地址
	this->srvAddr.sin_addr.S_un.S_addr = inet_addr(config.SERVERADDRESS.c_str()); //这是另外一种设置IP地址的方法

	//绑定 socket to Server's IP and port
	int rtn = ::bind(this->srvSocket,(LPSOCKADDR)&(this->srvAddr),sizeof(this->srvAddr));
	if(rtn == SOCKET_ERROR){
		L.lock();
		qDebug()<< "Server socket bind error!\n";
		L.unlock();
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}
	L.lock();
    qDebug()<< "Server socket bind ok!\n";
	L.unlock();
	return 0;
}

//开始监听,等待客户的连接请求
int Server::ListenStartup(){
	int rtn = listen(this->srvSocket,config.MAXCONNECTION);
	if(rtn == SOCKET_ERROR){
		L.lock();
		qDebug() << "Server socket listen error!\n";
		L.unlock();
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}
	L.lock();
	qDebug()<< "Server socket listen ok!\n";
	L.unlock();
	return 0;
}

//接受客户端发来的请求和数据并转发
int Server::Loop(){
	HANDLE hThreadStopSrv,hThreadProcess;
	DWORD dwThreadID,id2;
	
	string s;
	flag = 1;
	while (flag)
	{
		this->clientAddrSize = sizeof(this->clientAddr);
		this->newSocket = accept(this->srvSocket, (SOCKADDR *)&clientAddr,&clientAddrSize);
		
		Parameter *p = new Parameter;
		s.clear();
		s= s + "connect request : " + inet_ntoa(clientAddr.sin_addr) + " : " + to_string(ntohs(clientAddr.sin_port)) + '\n';
		p->msg = s; p->sock = newSocket;
		if (this->srvSocket == SOCKET_ERROR) break;
		hThreadProcess = (HANDLE)_beginthreadex(NULL, 0, ProcessRequest, (void*)p, 0, (unsigned *)&dwThreadID);
	}
	return -1;
}
void Server::setConfig(Config cfg)
{
	config = cfg;
}
Config Server::getConfig()
{
	return Config(config);
}

//处理请求

unsigned WINAPI ProcessRequest(void *arg)
{
	if (flag == 0) return 1;
	char buf[BUF_SIZE];//缓冲区
	string filename;//请求的文件名
	string firstline;//请求报文的第一行数据
	string method, fileDir;//请求方式，文件路径
	string msg;//提示消息
	SOCKET clientSocket = ((Parameter*)arg)->sock;
	int cnt=recv(clientSocket, buf, BUF_SIZE, 0);
	msg = ((Parameter *)arg)->msg;
	delete (Parameter *)arg;
	if (strstr(buf, "HTTP/") == NULL)//不接受非http请求
	{
		SendErrorMSG(clientSocket,"请求错误，不接受非http请求");
		closesocket(clientSocket);
		return 0;
	}
	buf[cnt] = 0;
	msg.append(buf);
	firstline.assign(strtok(buf, "\n"));//获取请求报文的第一行数据
	int begin, end;
	
	end = firstline.find_first_of(' ');
	method = firstline.substr(0, end);//获取请求方式
	//msg.append(firstline).append("\n");
	
	begin = firstline.find_first_of('/');
	end = firstline.find_first_of(' ',begin);
	filename.assign(firstline.substr(begin+1, end - begin));//获取文件路径
	for (int i = 0; i < filename.size(); i++)//将反斜杠转换为斜杠
		if (filename[i] == '/') filename[i] = '\\';
	if (method!="GET")
		SendErrorMSG(clientSocket,"请求错误，不接受非GET请求");
	filename = config.HOMEDIR + '\\' + filename;//补全完整路径
	msg = msg + "request file name:" + filename + '\n';
	msg+=SendData(clientSocket, filename);//通过套接字clientSocket发送信息
	SendData(clientSocket, filename);
	L.lock();
	qDebug() << msg.c_str();
	L.unlock();
	return 1;
}
//回复错误请求
void SendErrorMSG(SOCKET sock,string error)
{
	string protocol = "HTTP/1.0 400 Bad Request\r\n\r\n";
	string content;
	content = "<html><head><title>NETWORK</title></head><body><br> " + error + "</body></html>";

	send(sock, protocol.c_str(), protocol.length(), 0);
	send(sock, content.c_str(), content.length(), 0);
	closesocket(sock);
	
}
//发送文件
string SendData(SOCKET sock, const string &filename)
{
	string protocol = "HTTP/1.0 200 OK\r\n";			//协议类型
	string servName = "Server: simple web server\r\n";	//服务器名称
	string cntLen = "Content-length:";					//文件长度
	string cntType = "Content-type: ";					//文件类型
	
	FILE *file;
	file = fopen(filename.c_str(), "rb");
	if (file==NULL)//打开文件失败
	{
		SendErrorMSG(sock,"文件 "+filename.substr(filename.find_last_of('\\'))+" 不存在");
		closesocket(sock);
		return "File:"+filename+"unfind\nsend error\n"+"**********************************\n";
	}
	string ct = ComtentType(filename);
	cntType+= ct + "\r\n\r\n";	//获取文件类型
	fseek(file, 0, SEEK_END);//定位到文件结尾来获取文件长度
	int fileSize = ftell(file);
	fseek(file,0,SEEK_SET);//重新定位到文件开头
	
	//发送回复报文
	cntLen += to_string(fileSize) + "\r\n";//计算文件长度
	send(sock, protocol.c_str(), protocol.length(), 0);
	send(sock, servName.c_str(), servName.length(), 0);
	send(sock, cntLen.c_str(), cntLen.length(), 0);
	send(sock, cntType.c_str(), cntType.length(), 0);
	//发送实际内容
	char *buf = new char[BUF_SIZE];
	if (buf == NULL)//空间分配失败，异常退出
	{
		exit(-1);
	}
	int k = fread(buf, 1, BUF_SIZE, file);
	while (k)
	{
		send(sock, buf, k, 0);
		k = fread(buf, 1, BUF_SIZE, file);
	}
	delete[] buf;
	closesocket(sock);
	return cntType + "send success\n" + "---------------------------------------\n";
}

//根据文件名返回文件类型
string ComtentType(string filename)
{
	int index;
	index = filename.find_last_of('.');
	int end;
	end = filename.find_last_of(' ');
	string extension(filename.substr(index+1,end-index-1));
	
	string ht("html");
	if(extension==ht)
		return "text/html";
	else
		return extension;
}
