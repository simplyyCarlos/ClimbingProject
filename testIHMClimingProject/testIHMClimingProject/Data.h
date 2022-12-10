#pragma once
#include <qvector.h>
#include <qpoint.h>

class Data
{
private:
	QVector<QPointF*> listPrise;
	bool calibrate;
public:
	Data();
	~Data();
	QVector<QPointF*> getPrise() { return listPrise; }
	void addPrise(QPointF*);
	bool getCalibrate() { return calibrate; }
	void setCalibrate(bool b) { calibrate = b; }

};

