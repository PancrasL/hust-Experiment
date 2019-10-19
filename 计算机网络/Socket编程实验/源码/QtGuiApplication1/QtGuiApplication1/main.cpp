#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>
#include"ConnectGui.h"
#include<mutex>
std::mutex L;
static ConnectGui *pGui;
void message_handler(QtMsgType type, const QMessageLogContext &, const QString & msg) {
	Sleep(20);
	pGui->w.ui.textBrowser->append(msg);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ConnectGui obj;
	pGui = &obj;
	qInstallMessageHandler(message_handler);
	pGui->w.show();
	return a.exec();
}
