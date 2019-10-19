/********************************************************************************
** Form generated from reading UI file 'QtGuiApplication1.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIAPPLICATION1_H
#define UI_QTGUIAPPLICATION1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiApplication1Class
{
public:
    QWidget *centralWidget;
    QTextBrowser *textBrowser;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *START;
    QPushButton *STOP;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *Reset;
    QPushButton *Apply;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpinBox *IP_1;
    QLabel *label_5;
    QSpinBox *IP_2;
    QLabel *label_6;
    QSpinBox *IP_3;
    QLabel *label_7;
    QSpinBox *IP_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpinBox *PORT;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QTextBrowser *Hdir;
    QToolButton *SELECT_FILE;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpinBox *MAX_CONNECTION;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *l1;
    QLabel *cur_ip;
    QHBoxLayout *horizontalLayout_9;
    QLabel *l2;
    QLabel *cur_port;
    QHBoxLayout *horizontalLayout_11;
    QLabel *l3;
    QTextBrowser *cur_dir;
    QHBoxLayout *horizontalLayout_10;
    QLabel *l4;
    QLabel *cur_max;
    QPushButton *clear;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiApplication1Class)
    {
        if (QtGuiApplication1Class->objectName().isEmpty())
            QtGuiApplication1Class->setObjectName(QStringLiteral("QtGuiApplication1Class"));
        QtGuiApplication1Class->resize(1133, 568);
        QtGuiApplication1Class->setContextMenuPolicy(Qt::CustomContextMenu);
        QtGuiApplication1Class->setAutoFillBackground(false);
        QtGuiApplication1Class->setDocumentMode(false);
        centralWidget = new QWidget(QtGuiApplication1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(0, 0, 631, 471));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(770, 0, 195, 31));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        START = new QPushButton(layoutWidget);
        START->setObjectName(QStringLiteral("START"));

        horizontalLayout_3->addWidget(START);

        STOP = new QPushButton(layoutWidget);
        STOP->setObjectName(QStringLiteral("STOP"));

        horizontalLayout_3->addWidget(STOP);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(890, 230, 195, 30));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        Reset = new QPushButton(layoutWidget1);
        Reset->setObjectName(QStringLiteral("Reset"));

        horizontalLayout_8->addWidget(Reset);

        Apply = new QPushButton(layoutWidget1);
        Apply->setObjectName(QStringLiteral("Apply"));

        horizontalLayout_8->addWidget(Apply);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(640, 60, 441, 163));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(15);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(15, 15, 15, 15);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));
        label->setLayoutDirection(Qt::RightToLeft);
        label->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        IP_1 = new QSpinBox(layoutWidget2);
        IP_1->setObjectName(QStringLiteral("IP_1"));
        IP_1->setMaximumSize(QSize(31, 16777215));
        IP_1->setMouseTracking(false);
        IP_1->setFocusPolicy(Qt::WheelFocus);
        IP_1->setContextMenuPolicy(Qt::DefaultContextMenu);
        IP_1->setLayoutDirection(Qt::LeftToRight);
        IP_1->setFrame(false);
        IP_1->setButtonSymbols(QAbstractSpinBox::NoButtons);
        IP_1->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        IP_1->setMaximum(255);

        horizontalLayout->addWidget(IP_1);

        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        IP_2 = new QSpinBox(layoutWidget2);
        IP_2->setObjectName(QStringLiteral("IP_2"));
        IP_2->setMaximumSize(QSize(31, 16777215));
        IP_2->setMouseTracking(false);
        IP_2->setFocusPolicy(Qt::WheelFocus);
        IP_2->setContextMenuPolicy(Qt::DefaultContextMenu);
        IP_2->setLayoutDirection(Qt::LeftToRight);
        IP_2->setFrame(false);
        IP_2->setAlignment(Qt::AlignCenter);
        IP_2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        IP_2->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        IP_2->setMaximum(255);

        horizontalLayout->addWidget(IP_2);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        IP_3 = new QSpinBox(layoutWidget2);
        IP_3->setObjectName(QStringLiteral("IP_3"));
        IP_3->setMaximumSize(QSize(31, 16777215));
        IP_3->setMouseTracking(false);
        IP_3->setFocusPolicy(Qt::WheelFocus);
        IP_3->setContextMenuPolicy(Qt::DefaultContextMenu);
        IP_3->setLayoutDirection(Qt::LeftToRight);
        IP_3->setFrame(false);
        IP_3->setAlignment(Qt::AlignCenter);
        IP_3->setButtonSymbols(QAbstractSpinBox::NoButtons);
        IP_3->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        IP_3->setMaximum(255);

        horizontalLayout->addWidget(IP_3);

        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout->addWidget(label_7);

        IP_4 = new QSpinBox(layoutWidget2);
        IP_4->setObjectName(QStringLiteral("IP_4"));
        IP_4->setMaximumSize(QSize(31, 16777215));
        IP_4->setMouseTracking(false);
        IP_4->setFocusPolicy(Qt::WheelFocus);
        IP_4->setContextMenuPolicy(Qt::DefaultContextMenu);
        IP_4->setLayoutDirection(Qt::LeftToRight);
        IP_4->setFrame(false);
        IP_4->setAlignment(Qt::AlignCenter);
        IP_4->setButtonSymbols(QAbstractSpinBox::NoButtons);
        IP_4->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        IP_4->setMaximum(255);

        horizontalLayout->addWidget(IP_4);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setLayoutDirection(Qt::RightToLeft);
        label_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(label_2);

        PORT = new QSpinBox(layoutWidget2);
        PORT->setObjectName(QStringLiteral("PORT"));
        PORT->setMaximumSize(QSize(200, 16777215));
        PORT->setMouseTracking(false);
        PORT->setFocusPolicy(Qt::WheelFocus);
        PORT->setContextMenuPolicy(Qt::DefaultContextMenu);
        PORT->setAcceptDrops(false);
        PORT->setWrapping(false);
        PORT->setFrame(false);
        PORT->setAlignment(Qt::AlignCenter);
        PORT->setButtonSymbols(QAbstractSpinBox::NoButtons);
        PORT->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        PORT->setMaximum(65535);

        horizontalLayout_4->addWidget(PORT);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(16777215, 16777215));
        label_3->setLayoutDirection(Qt::RightToLeft);
        label_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(label_3);

        Hdir = new QTextBrowser(layoutWidget2);
        Hdir->setObjectName(QStringLiteral("Hdir"));
        Hdir->setMaximumSize(QSize(16777215, 21));

        horizontalLayout_5->addWidget(Hdir);

        SELECT_FILE = new QToolButton(layoutWidget2);
        SELECT_FILE->setObjectName(QStringLiteral("SELECT_FILE"));
        SELECT_FILE->setFocusPolicy(Qt::ClickFocus);
        SELECT_FILE->setAcceptDrops(false);
        SELECT_FILE->setToolButtonStyle(Qt::ToolButtonIconOnly);
        SELECT_FILE->setAutoRaise(false);

        horizontalLayout_5->addWidget(SELECT_FILE);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setLayoutDirection(Qt::RightToLeft);
        label_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(label_4);

        MAX_CONNECTION = new QSpinBox(layoutWidget2);
        MAX_CONNECTION->setObjectName(QStringLiteral("MAX_CONNECTION"));
        MAX_CONNECTION->setMaximumSize(QSize(200, 16777215));
        MAX_CONNECTION->setMouseTracking(false);
        MAX_CONNECTION->setFocusPolicy(Qt::WheelFocus);
        MAX_CONNECTION->setContextMenuPolicy(Qt::DefaultContextMenu);
        MAX_CONNECTION->setAcceptDrops(false);
        MAX_CONNECTION->setWrapping(false);
        MAX_CONNECTION->setFrame(false);
        MAX_CONNECTION->setAlignment(Qt::AlignCenter);
        MAX_CONNECTION->setButtonSymbols(QAbstractSpinBox::NoButtons);
        MAX_CONNECTION->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        MAX_CONNECTION->setMaximum(200000);

        horizontalLayout_6->addWidget(MAX_CONNECTION);


        verticalLayout->addLayout(horizontalLayout_6);

        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(642, 292, 322, 186));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setSpacing(22);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(15, 15, 15, 15);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        l1 = new QLabel(layoutWidget3);
        l1->setObjectName(QStringLiteral("l1"));
        l1->setBaseSize(QSize(0, 0));

        horizontalLayout_7->addWidget(l1);

        cur_ip = new QLabel(layoutWidget3);
        cur_ip->setObjectName(QStringLiteral("cur_ip"));
        cur_ip->setMinimumSize(QSize(200, 0));
        cur_ip->setMaximumSize(QSize(200, 16777215));
        cur_ip->setBaseSize(QSize(0, 0));

        horizontalLayout_7->addWidget(cur_ip);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        l2 = new QLabel(layoutWidget3);
        l2->setObjectName(QStringLiteral("l2"));
        l2->setBaseSize(QSize(0, 0));

        horizontalLayout_9->addWidget(l2);

        cur_port = new QLabel(layoutWidget3);
        cur_port->setObjectName(QStringLiteral("cur_port"));
        cur_port->setMinimumSize(QSize(200, 0));
        cur_port->setMaximumSize(QSize(200, 16777215));
        cur_port->setBaseSize(QSize(0, 0));

        horizontalLayout_9->addWidget(cur_port);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        l3 = new QLabel(layoutWidget3);
        l3->setObjectName(QStringLiteral("l3"));
        l3->setBaseSize(QSize(0, 0));

        horizontalLayout_11->addWidget(l3);

        cur_dir = new QTextBrowser(layoutWidget3);
        cur_dir->setObjectName(QStringLiteral("cur_dir"));
        cur_dir->setMinimumSize(QSize(0, 31));
        cur_dir->setMaximumSize(QSize(16777215, 31));

        horizontalLayout_11->addWidget(cur_dir);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        l4 = new QLabel(layoutWidget3);
        l4->setObjectName(QStringLiteral("l4"));
        l4->setBaseSize(QSize(0, 0));

        horizontalLayout_10->addWidget(l4);

        cur_max = new QLabel(layoutWidget3);
        cur_max->setObjectName(QStringLiteral("cur_max"));
        cur_max->setMinimumSize(QSize(200, 0));
        cur_max->setMaximumSize(QSize(200, 16777215));
        cur_max->setBaseSize(QSize(0, 0));

        horizontalLayout_10->addWidget(cur_max);


        verticalLayout_2->addLayout(horizontalLayout_10);

        clear = new QPushButton(centralWidget);
        clear->setObjectName(QStringLiteral("clear"));
        clear->setGeometry(QRect(540, 470, 93, 28));
        QtGuiApplication1Class->setCentralWidget(centralWidget);
        layoutWidget->raise();
        textBrowser->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        clear->raise();
        menuBar = new QMenuBar(QtGuiApplication1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1133, 26));
        QtGuiApplication1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiApplication1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtGuiApplication1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGuiApplication1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtGuiApplication1Class->setStatusBar(statusBar);

        retranslateUi(QtGuiApplication1Class);

        QMetaObject::connectSlotsByName(QtGuiApplication1Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiApplication1Class)
    {
        QtGuiApplication1Class->setWindowTitle(QApplication::translate("QtGuiApplication1Class", "QtGuiApplication1", Q_NULLPTR));
        START->setText(QApplication::translate("QtGuiApplication1Class", "START", Q_NULLPTR));
        STOP->setText(QApplication::translate("QtGuiApplication1Class", "STOP", Q_NULLPTR));
        Reset->setText(QApplication::translate("QtGuiApplication1Class", "\346\201\242\345\244\215\351\273\230\350\256\244", Q_NULLPTR));
        Apply->setText(QApplication::translate("QtGuiApplication1Class", "\345\272\224\347\224\250", Q_NULLPTR));
        label->setText(QApplication::translate("QtGuiApplication1Class", "\351\205\215\347\275\256\346\234\215\345\212\241\345\231\250ip:", Q_NULLPTR));
        IP_1->setSpecialValueText(QApplication::translate("QtGuiApplication1Class", "127", Q_NULLPTR));
        label_5->setText(QApplication::translate("QtGuiApplication1Class", ".", Q_NULLPTR));
        IP_2->setSpecialValueText(QApplication::translate("QtGuiApplication1Class", "0", Q_NULLPTR));
        label_6->setText(QApplication::translate("QtGuiApplication1Class", ".", Q_NULLPTR));
        IP_3->setSpecialValueText(QApplication::translate("QtGuiApplication1Class", "0", Q_NULLPTR));
        label_7->setText(QApplication::translate("QtGuiApplication1Class", ".", Q_NULLPTR));
        IP_4->setSpecialValueText(QApplication::translate("QtGuiApplication1Class", "1", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtGuiApplication1Class", "\351\205\215\347\275\256\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\345\217\267:", Q_NULLPTR));
        PORT->setSpecialValueText(QApplication::translate("QtGuiApplication1Class", "5050", Q_NULLPTR));
        label_3->setText(QApplication::translate("QtGuiApplication1Class", "\351\205\215\347\275\256\346\240\271\347\233\256\345\275\225\357\274\232", Q_NULLPTR));
        SELECT_FILE->setText(QApplication::translate("QtGuiApplication1Class", "\347\233\256\345\275\225...", Q_NULLPTR));
        label_4->setText(QApplication::translate("QtGuiApplication1Class", "\351\205\215\347\275\256\346\234\200\345\244\247\350\277\236\346\216\245\346\225\260\357\274\232", Q_NULLPTR));
        MAX_CONNECTION->setSpecialValueText(QApplication::translate("QtGuiApplication1Class", "5050", Q_NULLPTR));
        l1->setText(QApplication::translate("QtGuiApplication1Class", "IP\357\274\232", Q_NULLPTR));
        cur_ip->setText(QString());
        l2->setText(QApplication::translate("QtGuiApplication1Class", "\347\253\257\345\217\243\345\217\267:", Q_NULLPTR));
        cur_port->setText(QString());
        l3->setText(QApplication::translate("QtGuiApplication1Class", "\347\233\256\345\275\225:", Q_NULLPTR));
        l4->setText(QApplication::translate("QtGuiApplication1Class", "\346\234\200\345\244\247\350\277\236\346\216\245\346\225\260:", Q_NULLPTR));
        cur_max->setText(QString());
        clear->setText(QApplication::translate("QtGuiApplication1Class", "clear", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiApplication1Class: public Ui_QtGuiApplication1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPPLICATION1_H
