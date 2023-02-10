#pragma once
#include <QtWidgets/qdialog.h>
#include "ui_dialogCreation.h"
#include "dbmanager.h"
#include "UserConnected.h"
/**
 * @brief Dialog to create an account in the application
*/
class dialogCreation : public QDialog
{
	Q_OBJECT;
public:
	/**
	 * @brief Constructor of the class
	 * @param parent window that create this class 
	*/
	dialogCreation(QWidget* parent);
	/**
	 * @brief Destructor of the class
	*/
	~dialogCreation();
private:
	Ui::CreationClass ui;
	DbManager* db;
	UserConnected* uc;
private slots:
	/**
	 * @brief Action that check if the condition to create an account are good
	*/
	void validerCreation();
};

