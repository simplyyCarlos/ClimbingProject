#pragma once
#include "ui_calibrage.h"

class Calibrage : public QWidget {
	Q_OBJECT
public:
	Calibrage(QWidget* _parent);
	~Calibrage();
private:
	Ui::calibrageClass ui;
	QWidget* parent;
private slots:

};