#pragma once
#include <qvector.h>
#include <qpoint.h>
#include "observer.h"
#include "Circle.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

class Data
{
private:
	static Data* instance;
	QVector<QPointF*> listPrise;
	bool calibrate;
	QVector<Observer*> listObserver;
	cv::Matx33f matCali;
	Data();
public:
	~Data();
	static Data* getInstance();
	QVector<QPointF*> getPrise() { return listPrise; }
	cv::Matx33f getMatrice() { return matCali; }
	void calibragePrise(double, double);
	void addPrise(QPointF*);
	bool getCalibrate() { return calibrate; }
	void setCalibrate(bool b) { calibrate = b; }
	void setMatrice(double[9]);
	void setMatrice(cv::Mat);
};

