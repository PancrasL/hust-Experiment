#ifndef ServerSocket_H
#define ServerSocket_H
#include "dbconnector.h"
#include <QTcpSocket>
#include <QObject>
#include "myStruct.h"
class ServerSocket: public QObject
{
    Q_OBJECT

private:
    QTcpSocket *tcpSocket;
    QString userId;                 //登录人的id
    QString userName;               //登录人的姓名
public:
    ServerSocket();
    ~ServerSocket();
    bool isValid();
    void setTcpSocket(QTcpSocket *value);

private slots:
    //将字符串以'\n'分割后存放到QVector中
    void split(char *buf, QVector<QString> &msg);
    //接受客户端发来的信息
    void readData();
    //回复客户端信息
    void sendData(int replyType, unsigned int replySize, const char *replyMsg);
    //关闭连接
    void disConnect();
};

#endif // ServerSocket_H
