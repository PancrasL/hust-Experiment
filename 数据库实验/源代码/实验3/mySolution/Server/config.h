#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

struct Config
{
    static const QString dataBase;
    static const QString hostName;
    static const QString dataBaseName;
    static const QString databaseUserName;
    static const QString databasePassword;
    static const QString ip;
    static const unsigned short port;
};
#endif // CONFIG_H
