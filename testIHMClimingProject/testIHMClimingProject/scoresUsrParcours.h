#pragma once
#include "ui_scoresUsrParcoursMenu.h"
#include "dbmanager.h"
#include "observer.h"
/**
 * @brief Window of the score menue for the Parcours game for the user connected
*/
class scoresUsrParcours : public QWidget, public Observer
{
	Q_OBJECT
public:
	/**
	 * @brief Constructor of the class
	 * @param _parent window that create this window
	*/
	scoresUsrParcours(QWidget* _parent);
	/**
	 * @brief Desctructor of the class
	*/
	~scoresUsrParcours();
	/**
	 * @brief Method that update the view when there is change in the model inherit from Observer class
	*/
	void updateModel();
private:
	Ui::scoresUsrParcoursMenuClass ui;
	QWidget* parent;
	DbManager* db;
private slots:
	/**
	* @brief Action when the button "back" is pressed that go back to the parent window
	*/
	void pushbackButton();
};

