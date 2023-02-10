#pragma once
#include <QtWidgets/qdialog.h>
#include "ui_dialogLogin.h"
#include "dbmanager.h"
#include "UserConnected.h";
/**
 * @brief Dialog that open to connect a user to the application
*/
class dialogLogin : public QDialog
{
	Q_OBJECT;
public:
	/**
	 * @brief Constructor of the class
	 * @param parent window that create this class 
	*/
	dialogLogin(QWidget* parent);
	/**
	 * @brief Destructor of the class
	*/
	~dialogLogin();
private:
	Ui::DialogClass ui;
	DbManager* db;
	UserConnected* uc;
private slots:
	/**
	 * @brief Action to check if the login information are good
	*/
	void validerConnexion();
};

