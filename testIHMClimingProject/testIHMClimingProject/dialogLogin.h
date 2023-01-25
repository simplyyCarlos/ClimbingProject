#pragma once
#include <QtWidgets/qdialog.h>
#include "ui_dialogLogin.h"
#include "dbmanager.h"
#include "UserConnected.h";

class dialogLogin : public QDialog
{
	Q_OBJECT;
public:
	dialogLogin(QWidget* parent);
	~dialogLogin();
private:
	Ui::DialogClass ui;
	DbManager* db;
	UserConnected* uc;
private slots:
	void validerConnexion();
};

