#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include <QObject>
class QTcpSocket;
class ClientSocket : public QObject
{
    Q_OBJECT
public:
    ClientSocket();
    ~ClientSocket();
    void connectServer();//连接服务器

private:
    /*服务器连接*/
    QString ip = "127.0.0.1";//服务器地址
    unsigned short port = 6050;//服务器端口
    QTcpSocket * clientSocket;//与服务器连接的Socket
    bool initConnection();//初始化网络连接

    /*收发数据*/
    void split(char * msg, QVector<QString> &vec);//将报文分割保存到msg中
    void sendData(int requestType, unsigned int requestSize, const char *requestMsg);//发送报文
private slots:
    void recvData();
    void handleTryLogin(const QString &msg);
    void handleTryRegist(const QString &msg);
    void handleTryFindPwd(const QString &msg);
    void handleTryGetQuestion(const QString &msg);
    void handleTryGetRentCarInfo(const QString &msg);
signals:
    void loginReply(bool success);
    void registReply(bool success, const QString &msg);
    void findPwdReply(bool success);
    void getQuestionReply(bool success, const QString &msg);
    void getRentCarInfoReply(bool success, const QVector<QString> &info);
};

#endif // CLIENTSOCKET_H
