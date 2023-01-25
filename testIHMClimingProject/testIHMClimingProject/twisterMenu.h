#pragma once
#include "twister.h"
#include "ui_twisterMenu.h"
#include "scoresTwisterMenu.h"
#include "UserConnected.h"
#include "dbmanager.h"


class TwisterMenu : public QWidget
{
private:
	Ui::twisterMenuClass ui;
	QWidget* parent;
	Data* dt;
	DbManager* db;
	Twister* tw;
	int score;
	scoresTwisterMenu* stm;
	UserConnected* uc;
public:
	TwisterMenu(QWidget*, Data*);
	~TwisterMenu();
	void addPoint();
	void loose();

private slots:
	void openJeu();
	void pushbackButton();
	void openScoresTwisterMenu();
};


