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
public:
	TwisterMenu(QWidget*, Data*);
	~TwisterMenu();

private slots:
	void openJeu();
	void pushbackButton();

};

