#include "clientsocket.h"
#include "trans_protocol.h"
#include <QTcpSocket>
#include <QMessageBox>
ClientSocket::ClientSocket()
{
    clientSocket = new QTcpSocket();
}

ClientSocket::~ClientSocket()
{
    delete clientSocket;
    qDebug()<<"ClientSocket's destructor";
}

bool ClientSocket::initConnection()
{
    clientSocket = new QTcpSocket();
    clientSocket->connectToHost(ip,port);
    if(!clientSocket->waitForConnected(30000))
    {
        return false;
    }
    return true;
}

void ClientSocket::connectServer()
{
    while(initConnection()==false)
    {
        int choose= QMessageBox::question(nullptr, tr("服务器连接异常"),QString(tr("与服务器连接失败，是否重新连接？")),QMessageBox::Yes | QMessageBox::No);
        if(choose==QMessageBox::No)
            exit(-2);
    }
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(recvData()));
}

void ClientSocket::split(char *buf, QVector<QString> &msg)
{
    char *line;
    line = strtok(buf,"\n");
    while(line)
    {
        msg.push_back(line);
        line = strtok(nullptr,"\n");
    }
}

void ClientSocket::sendData(int requestType, unsigned int requestSize, const char *requestMsg)
{
    qDebug()<<"---------------向服务器发送消息：---------------";
    qDebug()<<requestMsg;
    /*发送报文*/
    clientSocket->write((char *)&requestType, sizeof(int));
    clientSocket->write((char *)&requestSize, sizeof(int));
    clientSocket->write(requestMsg, requestSize);
}

void ClientSocket::recvData()
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
    QVector<QString> vec;
    split(buf, vec);
    switch (replyType) {
    case PROTOCOL::LOGIN_REPLY:
        if(vec.size() == 1)
        {
            if(vec[0] == "login success")
                emit loginReply(true);
            else
                emit loginReply(false);
        }
        break;
    case PROTOCOL::REGIST_REPLY:
        if(vec.size() == 1)
        {
            if(vec[0] == "regist success")
                emit registReply(true, "注册成功");
            else if(vec[0] == "account already exist")
                emit registReply(false, "用户已注册");
            else if(vec[0] == "regist defeat")
                emit registReply(false, "注册失败，请检查输入信息是否正确");
        }
        break;
    case PROTOCOL::GETQUESTION_REPLY:
        if(vec.size() == 2)
        {
            if(vec[0] == "get question success")
                emit getQuestionReply(true, vec[1]);
            else if(vec[0] == "get question defeat")
                emit getQuestionReply(false,"");
        }
        break;
    case PROTOCOL::FINDPWD_REPLY:
        if(vec.size() == 1)
        {
            if(vec[0] == "find password success")
                emit findPwdReply(true);
            else
                emit findPwdReply(false);
        }
        break;
    case PROTOCOL::RENTCARINFO_REPLY:
        if(vec.isEmpty())
            break;
        else if(vec[0] == "credit too low")
            emit getRentCarInfoReply(false, vec);
        else if(vec[0] == "rent car info")
            emit getRentCarInfoReply(true, vec);
        break;
    default:
        break;
    }
    delete [] buf;
}

void ClientSocket::handleTryLogin(const QString & msg)
{
    std::string s = msg.toStdString();
    sendData(PROTOCOL::USER_LOGIN, s.length()+1, s.c_str());
}

void ClientSocket::handleTryRegist(const QString & msg)
{
    std::string s = msg.toStdString();
    sendData(PROTOCOL::USER_REGIST, s.length()+1, s.c_str());
}

void ClientSocket::handleTryFindPwd(const QString & msg)
{
    std::string s = msg.toStdString();
    sendData(PROTOCOL::USER_FINDPWD, s.length()+1, s.c_str());
}

void ClientSocket::handleTryGetQuestion(const QString &msg)
{
    std::string s =msg.toStdString();
    sendData(PROTOCOL::USER_GETQUESTION, s.length()+1, s.c_str());
}

void ClientSocket::handleTryGetRentCarInfo(const QString &msg)
{
    std::string s =msg.toStdString();
    sendData(PROTOCOL::USER_GET_RENTCARINFO, s.length()+1, s.c_str());
}
