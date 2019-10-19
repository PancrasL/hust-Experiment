#ifndef ECLIENTSOCKEY_H
#define ECLIENTSOCKEY_H

#include <QObject>
#include <QTcpSocket>
class EClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit EClientSocket(QObject *parent = nullptr);
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
    void handleGetOrder(const QString &msg);
    void cancleOrConfirmOrder(const QString &msg);
    void handleBackCar(const QString &msg);
    void handleBroken(const QString &msg);
    void handleRecord(const QString &msg);
signals:
    void loginReply(bool success, bool isSellEmployee = 0);
    void getOrderReply(const QVector<QString> &info);
    void CclOrCfmReply(const QVector<QString> &info);
    void backCarReply(const QVector<QString> &info);
    void brokenReply(const QVector<QString> &info);
    void recordReply(const QVector<QString> &info);
};

#endif // ECLIENTSOCKEY_H
