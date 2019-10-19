#include "serversocket.h"
#include "trans_protocol.h"
#include "mainwindow.h"
#include "uclientservice.h"
#include "eclientservice.h"
#include <QMessageBox>

ServerSocket::ServerSocket()
{

}

ServerSocket::~ServerSocket()
{
}

void ServerSocket::setTcpSocket(QTcpSocket *value)
{
    tcpSocket = value;
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disConnect()));
}

void ServerSocket::split(char *buf, QVector<QString> &msg)
{
    char *line;
    line = strtok(buf,"\n");
    while(line)
    {
        msg.push_back(line);
        line = strtok(nullptr,"\n");
    }
}

bool ServerSocket::isValid()
{
    return tcpSocket->isValid();
}

void ServerSocket::readData()
{
    /*读取报文*/

    //读取报文头
    int requestType, requestSize;
    tcpSocket->read((char *)(&requestType),sizeof(int));   //消息类型
    tcpSocket->read((char *)(&requestSize),sizeof(int));   //数据大小
    //读取报文内容
    char *buf = new char[requestSize+1];
    tcpSocket->read(buf, requestSize);
    qDebug()<<"---------------收到来自客户端的消息：---------------"<<endl<<buf;
    qDebug()<<"==============================================================";
    /*处理报文*/
    QString replyMsg;
    std::string msg;
    QVector<QString> info;
    split(buf,info);
    switch (requestType) {
    case PROTOCOL::DEBUG:
        if(info.size() == 1)
        {
            replyMsg = UClient::debug();
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::DEBUG, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::USER_LOGIN:
        if(info.size() == 2)
        {
            replyMsg = UClient::handleLogin(info, userId, userName);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::LOGIN_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::USER_REGIST:
        if(info.size() == 12)
        {
            replyMsg = UClient::handleRegist(info);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::REGIST_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::USER_GETQUESTION:
        if(info.size() == 3)
        {
            replyMsg = UClient::handleGetQuestion(info);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::GETQUESTION_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::USER_FINDPWD:
        if(info.size() == 3)
        {
            replyMsg = UClient::handleFindPwd(info);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::FINDPWD_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::USER_GET_RENTCARINFO:
        if(info.size() == 1)
        {
            replyMsg = UClient::handleGetRentCarInfo(info);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::RENTCARINFO_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::USER_GET_USERINFO:
        if(info.size() == 1)
        {
            replyMsg = UClient::handleGetUserInfo(info[0]);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::USERINFO_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::USER_RENTCAR:
        if(info.size() == 3)
        {
            replyMsg = UClient::handleRentCar(info);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::RENTCAR_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::USER_CONFIRM_RENTCAR:
        if(info.size() == 5)
        {
            replyMsg = UClient::generateRentOrder(info);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::CONFIRM_RENTCAR_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::USER_GET_HISTORYORDER:
        if(info.size() == 3)
        {
            replyMsg = UClient::getHistoryOrder(info);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::HISTORYORDER_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::EMPLOYEE_LOGIN:
        if(info.size() == 2)
        {
            replyMsg = EClient::handleELogin(info, userId, userName);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::LOGIN_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::EMPLOYEE_GET_ORDER:
        replyMsg = EClient::handleGetOrder(info);
        msg = replyMsg.toStdString();
        sendData(PROTOCOL::EP_GET_ORDER_REPLY, msg.length()+1, msg.c_str());
        break;
    case PROTOCOL::EMPLOYEE_CCL_OR_CFM:
        if(info.size() == 4)
        {
            replyMsg = EClient::handleCclOrCfm(info[0], info[1], info[2], info[3]);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::EP_CCL_OR_CFM_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::EMPLOYEE_BACK_CAR:
        if(info.size() == 3)
        {
            replyMsg = EClient::handleBackCar(info[0], info[1], info[2]);
            msg = replyMsg.toStdString();
            sendData(PROTOCOL::EP_BACK_CAR_REPLY, msg.length()+1, msg.c_str());
        }
        break;
    case PROTOCOL::EMPLOYEE_BROKEN_INFO:
        replyMsg = EClient::handleBroken(info);
        msg = replyMsg.toStdString();
        sendData(PROTOCOL::EP_BROKEN_REPLY, msg.length()+1, msg.c_str());
        break;
    case PROTOCOL::EMPLOYEE_RECORD:
        replyMsg = EClient::handleRecord(info);
        msg = replyMsg.toStdString();
        sendData(PROTOCOL::EP_RECORD_REPLY, msg.length()+1, msg.c_str());
        break;
    default:
        break;
    }
    delete [] buf;
}

void ServerSocket::sendData(int replyType, unsigned int replySize, const char *replyMsg)
{
    qDebug()<<"---------------向客户端发送消息：---------------";
    qDebug()<<replyMsg;
    qDebug()<<"=============================================";
    /*发送报文*/
    tcpSocket->write((char *)&replyType, sizeof(int));
    tcpSocket->write((char *)&replySize, sizeof(int));
    tcpSocket->write(replyMsg, replySize);

}

void ServerSocket::disConnect()
{
    qDebug()<<"close socket connect";
    delete this;
}
