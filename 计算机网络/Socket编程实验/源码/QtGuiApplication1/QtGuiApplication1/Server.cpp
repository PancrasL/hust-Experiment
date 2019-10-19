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
	WSACleanup(); //����winsock ���л���
}
struct Parameter
{
	SOCKET sock;
	string msg;
};
unsigned WINAPI ProcessRequest(void *arg);					//��������
unsigned WINAPI StopServer(void *arg);
void SendErrorMSG(SOCKET sock,string error="error");		//�յ���������󣬻ظ�������Ϣ
string SendData(SOCKET sock, const string &filename);		//�ظ�����
string ComtentType(string filename);
//��ʼ��Winsock
int Server::WinsockStartup(){
	WSADATA wsaData;//���ڷ���Winsock�Ļ�����Ϣ   
	int rtn;		//Winsock��ʼ�������ķ���ֵ
	WORD  wVersionRequested = MAKEWORD(MAJORVERSION, MINORVERSION); //Winsock�汾�ţ����ֽڴΰ汾�����ֽ����汾��

	//��ʼ�� winsock
	rtn = WSAStartup(wVersionRequested, &wsaData);

	if (rtn) { //�������ֵ����0����Winsock��ʼ��ʧ��
		L.lock();
		qDebug() << "Winsock startup error!\n";
		L.unlock();
		return -1;
	}

	//�жϷ��ص�Winsock�汾��
	if (LOBYTE(wsaData.wVersion) != MAJORVERSION || HIBYTE(wsaData.wVersion) != MINORVERSION) { //����汾����
		WSACleanup();  //���Winsock
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

//��ʼ��Server����������sockect���󶨵�IP��PORT
int Server::ServerStartup(){
	//���� TCP socket
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
	//���÷�����IP��ַ�Ͷ˿ں�
	this->srvAddr.sin_family = AF_INET;
	this->srvAddr.sin_port =  htons(config.PORT);
	//this->srvAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//���Զ��ҵ����������ʵ�IP��ַ
	this->srvAddr.sin_addr.S_un.S_addr = inet_addr(config.SERVERADDRESS.c_str()); //��������һ������IP��ַ�ķ���

	//�� socket to Server's IP and port
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

//��ʼ����,�ȴ��ͻ�����������
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

//���ܿͻ��˷�������������ݲ�ת��
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

//��������

unsigned WINAPI ProcessRequest(void *arg)
{
	if (flag == 0) return 1;
	char buf[BUF_SIZE];//������
	string filename;//������ļ���
	string firstline;//�����ĵĵ�һ������
	string method, fileDir;//����ʽ���ļ�·��
	string msg;//��ʾ��Ϣ
	SOCKET clientSocket = ((Parameter*)arg)->sock;
	int cnt=recv(clientSocket, buf, BUF_SIZE, 0);
	msg = ((Parameter *)arg)->msg;
	delete (Parameter *)arg;
	if (strstr(buf, "HTTP/") == NULL)//�����ܷ�http����
	{
		SendErrorMSG(clientSocket,"������󣬲����ܷ�http����");
		closesocket(clientSocket);
		return 0;
	}
	buf[cnt] = 0;
	msg.append(buf);
	firstline.assign(strtok(buf, "\n"));//��ȡ�����ĵĵ�һ������
	int begin, end;
	
	end = firstline.find_first_of(' ');
	method = firstline.substr(0, end);//��ȡ����ʽ
	//msg.append(firstline).append("\n");
	
	begin = firstline.find_first_of('/');
	end = firstline.find_first_of(' ',begin);
	filename.assign(firstline.substr(begin+1, end - begin));//��ȡ�ļ�·��
	for (int i = 0; i < filename.size(); i++)//����б��ת��Ϊб��
		if (filename[i] == '/') filename[i] = '\\';
	if (method!="GET")
		SendErrorMSG(clientSocket,"������󣬲����ܷ�GET����");
	filename = config.HOMEDIR + '\\' + filename;//��ȫ����·��
	msg = msg + "request file name:" + filename + '\n';
	msg+=SendData(clientSocket, filename);//ͨ���׽���clientSocket������Ϣ
	SendData(clientSocket, filename);
	L.lock();
	qDebug() << msg.c_str();
	L.unlock();
	return 1;
}
//�ظ���������
void SendErrorMSG(SOCKET sock,string error)
{
	string protocol = "HTTP/1.0 400 Bad Request\r\n\r\n";
	string content;
	content = "<html><head><title>NETWORK</title></head><body><br> " + error + "</body></html>";

	send(sock, protocol.c_str(), protocol.length(), 0);
	send(sock, content.c_str(), content.length(), 0);
	closesocket(sock);
	
}
//�����ļ�
string SendData(SOCKET sock, const string &filename)
{
	string protocol = "HTTP/1.0 200 OK\r\n";			//Э������
	string servName = "Server: simple web server\r\n";	//����������
	string cntLen = "Content-length:";					//�ļ�����
	string cntType = "Content-type: ";					//�ļ�����
	
	FILE *file;
	file = fopen(filename.c_str(), "rb");
	if (file==NULL)//���ļ�ʧ��
	{
		SendErrorMSG(sock,"�ļ� "+filename.substr(filename.find_last_of('\\'))+" ������");
		closesocket(sock);
		return "File:"+filename+"unfind\nsend error\n"+"**********************************\n";
	}
	string ct = ComtentType(filename);
	cntType+= ct + "\r\n\r\n";	//��ȡ�ļ�����
	fseek(file, 0, SEEK_END);//��λ���ļ���β����ȡ�ļ�����
	int fileSize = ftell(file);
	fseek(file,0,SEEK_SET);//���¶�λ���ļ���ͷ
	
	//���ͻظ�����
	cntLen += to_string(fileSize) + "\r\n";//�����ļ�����
	send(sock, protocol.c_str(), protocol.length(), 0);
	send(sock, servName.c_str(), servName.length(), 0);
	send(sock, cntLen.c_str(), cntLen.length(), 0);
	send(sock, cntType.c_str(), cntType.length(), 0);
	//����ʵ������
	char *buf = new char[BUF_SIZE];
	if (buf == NULL)//�ռ����ʧ�ܣ��쳣�˳�
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

//�����ļ��������ļ�����
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
