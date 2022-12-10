#pragma once
#include "ui_calibrage.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets/QMainWindow>
#include "View.h"
#include "Data.h"
#include<thread>
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")




class Calibrage : public QWidget {
	Q_OBJECT
public:
	Calibrage(QWidget* _parent, Data* dt);
	~Calibrage();

	void calibrage();
private:
	Ui::calibrageClass ui;
	QWidget* parent;
    View* view;
	Data* dt;
	const QString filename = "savedImage.jpg";
	std::thread* t;


	void getImage();
private slots:
	void saveCalibration();
};
