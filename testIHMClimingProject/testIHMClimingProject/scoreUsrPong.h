#pragma once
#include "ui_scoresUsrPongMenu.h"
#include "dbmanager.h"
#include "observer.h"
class scoreUsrPong : public QWidget, public Observer
{
	Q_OBJECT
public:
	scoreUsrPong(QWidget* _parent);
	~scoreUsrPong();
	void updateModel();
private:
	Ui::scoresUsrPongMenuClass ui;
	QWidget* parent;
	DbManager* db;
private slots:
	void pushbackButton();
};

