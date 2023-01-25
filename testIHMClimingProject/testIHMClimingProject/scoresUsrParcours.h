#pragma once
#include "ui_scoresUsrParcoursMenu.h"
#include "dbmanager.h"
#include "observer.h"
class scoresUsrParcours : public QWidget, public Observer
{
	Q_OBJECT
public:
	scoresUsrParcours(QWidget* _parent);
	~scoresUsrParcours();
	void updateModel();
private:
	Ui::scoresUsrParcoursMenuClass ui;
	QWidget* parent;
	DbManager* db;
private slots:
	void pushbackButton();
};

