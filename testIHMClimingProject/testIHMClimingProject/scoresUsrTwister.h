#pragma once
#include "ui_scoresUsrTwisterMenu.h"
#include "dbmanager.h"
#include "observer.h"
class scoresUsrTwister : public QWidget, public Observer
{
	Q_OBJECT
public:
	scoresUsrTwister(QWidget* _parent);
	~scoresUsrTwister();
	void updateModel();
private:
	Ui::scoresUsrTwisterMenuClass ui;
	QWidget* parent;
	DbManager* db;
private slots:
	void pushbackButton();
};

