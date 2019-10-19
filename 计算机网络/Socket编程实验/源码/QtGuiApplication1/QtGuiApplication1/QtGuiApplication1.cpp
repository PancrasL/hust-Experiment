#include "QtGuiApplication1.h"
#include<QMessageBox>
#include<qdebug.h>
#include <process.h>
#include<mutex>
#include<qfiledialog.h>
#include<Config.h>
#include<string>
static Config config;
const Config def("127.0.0.1", 5050, "D:\\WebServer", 5050);
extern mutex L;
unsigned WINAPI RunSrv(void *arg)
{
	Server *pSrv;
	pSrv = (Server *)arg;
	if (pSrv->WinsockStartup() == -1) return 0;
	if (pSrv->ServerStartup() == -1) return 0;
	if (pSrv->ListenStartup() == -1) return 0;
	pSrv->Loop();
	return 1;
}
int start = 0;
QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	config = def;
	srv.setConfig(def);
	//启动服务器
	QObject::connect(this->ui.START, &QPushButton::clicked, [this]() {
		if (start == 0)
		{
			start = 1;
			HANDLE hd;
			hd = (HANDLE)_beginthreadex(NULL, 0, RunSrv, (void *)&(this->srv), 0, 0);
			this->update_info();
		}
	});

	//关闭服务器
	QObject::connect(this->ui.STOP, &QPushButton::clicked, [this]() {
		if (start == 1)
		{
			closesocket(this->srv.srvSocket);
			L.lock();
			qDebug() << "server closed success!\n";
			L.unlock();
			start = 0;
			this->srv.srvSocket = SOCKET_ERROR;
		}
	});

	//获取目录
	QObject::connect(this->ui.SELECT_FILE, &QPushButton::clicked, [this]() {
		QString file_name = QFileDialog::getExistingDirectory(NULL, "caption", ".");
		config.HOMEDIR = file_name.toStdString();
		this->ui.Hdir->setText(file_name);
	});

	//配置服务器
	QObject::connect(this->ui.Apply, &QPushButton::clicked, [this]() {
		string IP;
		config.SERVERADDRESS = (this->ui.IP_1->text()
			+ '.'
			+ this->ui.IP_2->text()
			+ '.'
			+ this->ui.IP_3->text()
			+ '.'
			+ this->ui.IP_4->text()
			).toStdString();
		config.MAXCONNECTION = this->ui.MAX_CONNECTION->text().toInt();
		config.PORT = this->ui.PORT->text().toInt();
		srv.setConfig(config);
		L.lock();
		qDebug() << "current config:" << endl;
		qDebug() << "SERVERADDRESS = " << config.SERVERADDRESS.c_str() << endl;
		qDebug() << "PORT = " << config.PORT << endl;
		qDebug() << "HOMEDIR = " << config.HOMEDIR.c_str() << endl;
		qDebug() << "MAXCONNECTION = " << config.MAXCONNECTION << endl;
		qDebug() << "server config success" << endl;
		qDebug() << "Effective after restarting the server" << endl << endl;
		L.unlock();
		this->update_info();
	});

	//恢复默认
	QObject::connect(this->ui.Reset, &QPushButton::clicked, [this]() {
		this->srv.setConfig(def);
		config = def;
		L.lock();
		qDebug() << "Restore default success" << endl;
		qDebug() << "current config:" << endl;
		qDebug() << "SERVERADDRESS = " << def.SERVERADDRESS.c_str() << endl;
		qDebug() << "PORT = " << def.PORT << endl;
		qDebug() << "HOMEDIR = " << def.HOMEDIR.c_str() << endl;
		qDebug() << "MAXCONNECTION = " << def.MAXCONNECTION << endl;
		qDebug() << "Effective after restarting the server" << endl << endl;
		L.unlock();
		this->update_info();
	});
	//清空窗口信息
	QObject::connect(this->ui.clear, &QPushButton::clicked, [this]() {
		this->ui.textBrowser->clear();
	});
}
void QtGuiApplication1::update_info()
{
	QString q;
	q = QString::fromStdString(config.SERVERADDRESS.c_str());
	this->ui.cur_ip->setText(q);
	q = QString::number(config.PORT);
	this->ui.cur_port->setText(q);
	q = QString::fromStdString(config.HOMEDIR);
	this->ui.cur_dir->setText(q);
	q = QString::number(config.MAXCONNECTION);
	this->ui.cur_max->setText(q);
}
