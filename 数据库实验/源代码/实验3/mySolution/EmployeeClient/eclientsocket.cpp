#include "eclientsocket.h"
#include "trans_protocol.h"
#include <QMessageBox>
#include <QDebug>
EClientSocket::EClientSocket(QObject *parent) : QObject(parent)
{

}

void EClientSocket::connectServer()
{
    while(initConnection()==false)
    {
        int choose= QMessageBox::question(nullptr, tr("服务器连接异常"),QString(tr("与服务器连接失败，是否重新连接？")),QMessageBox::Yes | QMessageBox::No);
        if(choose==QMessageBox::No)
            exit(-2);
    }
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(recvData()));
}

bool EClientSocket::initConnection()
{
    clientSocket = new QTcpSocket();
    clientSocket->connectToHost(ip,port);
    if(!clientSocket->waitForConnected(30000))
    {
        return false;
    }
    return true;
}

void EClientSocket::split(char *buf, QVector<QString> &msg)
{
    char *line;
    line = strtok(buf,"\n");
    while(line)
    {
        msg.push_back(line);
        line = strtok(nullptr,"\n");
    }
}

void EClientSocket::sendData(int requestType, unsigned int requestSize, const char *requestMsg)
{
    qDebug()<<"---------------向服务器发送消息：---------------";
    qDebug()<<requestMsg;
    /*发送报文*/
    clientSocket->write((char *)&requestType, sizeof(int));
    clientSocket->write((char *)&requestSize, sizeof(int));
    clientSocket->write(requestMsg, requestSize);
}

void EClientSocket::recvData()
{
    /*接收报文头*/
    int replyType,replySize;
    clientSocket->read((char *)&replyType, sizeof(int));
    clientSocket->read((char *)&replySize, sizeof(int));

    /*接受报文内容*/
    char *buf = new char[replySize];
    clientSocket->read(buf, replySize);
    qDebug()<<"---------------收到来自服务器的消息：---------------"<<endl<<buf;
    /*处理报文*/
    QVector<QString> info;
    split(buf, info);
    switch (replyType) {
    case PROTOCOL::LOGIN_REPLY:
        if(info.size() == 2)
        {
            if(info[0] == "login success")
            {
                emit loginReply(true, info[1] == "level0");
            }
            else
                emit loginReply(false);
        }
        break;
    case PROTOCOL::EP_GET_ORDER_REPLY:
        emit getOrderReply(info);
        break;
    case PROTOCOL::EP_CCL_OR_CFM_REPLY:
        emit CclOrCfmReply(info);
        break;
    case PROTOCOL::EP_BACK_CAR_REPLY:
        emit backCarReply(info);
        break;
    case PROTOCOL::EP_BROKEN_REPLY:
        emit brokenReply(info);
        break;
    case PROTOCOL::EP_RECORD_REPLY:
        emit recordReply(info);
        break;
    default:
        break;
    }
    delete [] buf;
}

void EClientSocket::handleTryLogin(const QString &msg)
{
    std::string s = msg.toStdString();
    sendData(PROTOCOL::EMPLOYEE_LOGIN, s.length()+1, s.c_str());
}

void EClientSocket::handleGetOrder(const QString &msg)
{
    std::string s = msg.toStdString();
    sendData(PROTOCOL::EMPLOYEE_GET_ORDER, s.length()+1, s.c_str());
}

void EClientSocket::cancleOrConfirmOrder(const QString &msg)
{
    std::string s = msg.toStdString();
    sendData(PROTOCOL::EMPLOYEE_CCL_OR_CFM, s.length()+1, s.c_str());
}

void EClientSocket::handleBackCar(const QString &msg)
{
    std::string s = msg.toStdString();
    sendData(PROTOCOL::EMPLOYEE_BACK_CAR, s.length()+1, s.c_str());
}

void EClientSocket::handleBroken(const QString &msg)
{
    std::string s = msg.toStdString();
    sendData(PROTOCOL::EMPLOYEE_BROKEN_INFO, s.length()+1, s.c_str());
}

void EClientSocket::handleRecord(const QString &msg)
{
    std::string s = msg.toStdString();
    sendData(PROTOCOL::EMPLOYEE_RECORD, s.length()+1, s.c_str());
}
