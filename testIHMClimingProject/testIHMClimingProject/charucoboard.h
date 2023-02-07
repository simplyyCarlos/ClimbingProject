#pragma once
#include "ui_charucoboard.h"
#include "qscreen.h"

class Charucoboard : public QWidget
{
public:
	Charucoboard();
	~Charucoboard();

private:
	QWidget* parent;
	Ui::charucoboardClass ui;
};
