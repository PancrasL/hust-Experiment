#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"
#include "Server.h"
#include"Config.h"
#include<iostream>
class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);
	Server srv;
	Ui::QtGuiApplication1Class ui;
	void update_info();
};
