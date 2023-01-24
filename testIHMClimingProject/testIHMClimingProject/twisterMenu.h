#pragma once
#include "twister.h";
#include "ui_twisterMenu.h"


class TwisterMenu : public QWidget
{
private:
	Ui::twisterMenuClass ui;
	QWidget* parent;
	Data* dt;
	Twister* tw;
	int score;
public:
	TwisterMenu(QWidget*, Data*);
	~TwisterMenu();
	void addPoint();
	void loose();

private slots:
	void openJeu();
	void pushbackButton();
};


