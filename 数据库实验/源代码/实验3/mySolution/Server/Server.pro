#-------------------------------------------------
#
# Project created by QtCreator 2019-05-20T21:19:56
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD\..\protocol
INCLUDEPATH += $$PWD\charts
CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dbconnector.cpp \
    config.cpp \
    uclientservice.cpp \
    serversocket.cpp \
    vipdiscountdialog.cpp \
    addnewcar.cpp \
    addnewemployee.cpp \
    eclientservice.cpp \
    charts/customtablemodel.cpp \
    charts/tablewidget.cpp \
    statisticswindow.cpp

HEADERS += \
        mainwindow.h \
    dbconnector.h \
    config.h \
    uclientservice.h \
    serversocket.h \
    vipdiscountdialog.h \
    addnewcar.h \
    addnewemployee.h \
    eclientservice.h \
    charts/customtablemodel.h \
    charts/tablewidget.h \
    statisticswindow.h

FORMS += \
        mainwindow.ui \
    vipdiscountdialog.ui \
    addnewcar.ui \
    addnewemployee.ui \
    statisticswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
RC_ICONS = serverIcon.ico
