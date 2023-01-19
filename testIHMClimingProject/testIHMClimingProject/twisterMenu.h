#pragma once
#include "twister.h"
#include "ui_twisterMenu.h"
#include "scoresTwisterMenu.h"
#include "UserConnected.h"


class TwisterMenu : public QWidget
{
private:
	Ui::twisterMenuClass ui;
	QWidget* parent;
	Data* dt;
	Twister* tw;
	scoresTwisterMenu* stm;
	UserConnected* uc;
public:
	TwisterMenu(QWidget*, Data*);
	~TwisterMenu();
private slots:
	void openJeu();
	void pushbackButton();
	void openScoresTwisterMenu();
};

