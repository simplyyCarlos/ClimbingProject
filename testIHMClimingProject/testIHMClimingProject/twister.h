#pragma once
#include "ui_twister.h"
#include "Data.h"
#include "qscreen.h"
#include "qpainter.h"
#include "qpen.h"


class Twister : public QWidget, public Observer
{
private:
	Ui::twisterClass ui;
	QWidget* parent;
	Data* dt;

	void paintEvent(QPaintEvent*) override;

public:
	Twister(QWidget*, Data*);
	~Twister();
	void updateModel();

};

