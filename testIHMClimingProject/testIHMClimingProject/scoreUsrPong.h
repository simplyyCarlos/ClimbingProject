#pragma once
#include "ui_scoresUsrPongMenu.h"
#include "dbmanager.h"
#include "observer.h"
/**
 * @brief Window of the score menue for the Pong game for the user connected
*/
class scoreUsrPong : public QWidget, public Observer
{
	Q_OBJECT
public:
	/**
	 * @brief Constructor of the class
	 * @param _parent window that create this window
	*/
	scoreUsrPong(QWidget* _parent);
	/**
	 * @brief Desctructor of the class
	*/
	~scoreUsrPong();
	/**
	 * @brief Method that update the view when there is change in the model inherit from Observer class
	*/
	void updateModel();
private:
	Ui::scoresUsrPongMenuClass ui;
	QWidget* parent;
	DbManager* db;
private slots:
	/**
	* @brief Action when the button "back" is pressed that go back to the parent window
	*/
	void pushbackButton();
};

