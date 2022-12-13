#pragma once
#include <qvector.h>
#include <qpoint.h>
#include "observer.h"
#include "Circle.h"

class Data : public Observable
{
private:
	QVector<QPointF*> listPrise;
	bool calibrate;
	QVector<Observer*> listObserver;
public:
	Data();
	~Data();
	QVector<QPointF*> getPrise() { return listPrise; }
	void calibragePrise(double, double);
	void addPrise(QPointF*);
	bool getCalibrate() { return calibrate; }
	void setCalibrate(bool b) { calibrate = b; }
	void addObserver(Observer* observer) override;
	void removeObserver(Observer* observer) override;
	void notifyObserver() const override;

};

