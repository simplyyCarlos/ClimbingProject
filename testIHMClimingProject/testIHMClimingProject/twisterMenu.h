#pragma once
#include "twister.h"
#include "ui_twisterMenu.h"
#include "scoresTwisterMenu.h"
#include "UserConnected.h"
#include "dbmanager.h"
#include "AbstractController.h"
#include "Reflex.h"

/**
 * @brief Window of the main menu of the Twister game
*/
class TwisterMenu : public QWidget
{
private:
	Ui::twisterMenuClass ui;
	QWidget* parent;
	DbManager* db;
	Twister* tw;
	Reflex* rf;
	int score;
	scoresTwisterMenu* stm;
	UserConnected* uc;
	bool bTwister;
public:
	/**
	 * @brief Contrusctor of the class
	 * @param window that create this window
	 * @param data inported
	*/
	TwisterMenu(QWidget*);
	/**
	 * @brief Destructor of the class
	*/
	~TwisterMenu();
	void addPoint();
	void loose();
	void setBTwister(bool);

private slots:
	void openJeu();
	void pushbackButton();
	void openScoresTwisterMenu();
};


