#pragma once
#include <QtWidgets/qdialog.h>
#include "ui_dialogCreation.h"
#include "dbmanager.h"
#include "UserConnected.h"

class dialogCreation : public QDialog
{
	Q_OBJECT;
public:
	dialogCreation(QWidget* parent);
	~dialogCreation();
private:
	Ui::CreationClass ui;
	DbManager* db;
	UserConnected* uc;
private slots:
	void validerCreation();
};

