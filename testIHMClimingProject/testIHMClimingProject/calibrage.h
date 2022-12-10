#pragma once
#include "ui_calibrage.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets/QMainWindow>
#include "View.h"


class Calibrage : public QWidget {
	Q_OBJECT
public:
	Calibrage(QWidget* _parent);
	~Calibrage();
private:
	Ui::calibrageClass ui;
	QWidget* parent;
    View* view;
	const QString filename = "partie1.jpg";
private slots:

};
