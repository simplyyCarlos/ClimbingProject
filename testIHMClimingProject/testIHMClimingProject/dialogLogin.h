#pragma once
#include <QtWidgets/qdialog.h>
#include "ui_dialogLogin.h"
#include "dbmanager.h"


class dialogLogin : public QDialog
{
	Q_OBJECT;
public:
	dialogLogin(QWidget* parent);
	~dialogLogin();
private:
	Ui::DialogClass ui;
	DbManager* db;
private slots:
	void validerConnexion();
};

