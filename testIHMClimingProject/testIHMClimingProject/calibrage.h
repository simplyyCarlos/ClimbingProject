#pragma once
#include "ui_calibrage.h"
#include "charucoboard.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "View.h"
#include "Data.h"
#include<thread>
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")
#include <pybind11/embed.h>
#include <pybind11/attr.h>
#include <pybind11/pytypes.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <sstream>
#include <iostream>
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/features2d.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
namespace py = pybind11;
using namespace boost::interprocess;
using namespace cv;




class Calibrage : public QWidget {
	Q_OBJECT
public:
	Calibrage(QWidget* _parent);
	Calibrage(Calibrage*);
	~Calibrage();

	void calibrage();
private:
	Ui::calibrageClass ui;
	Charucoboard* cb;
	QWidget* parent;
    View* view;
	Data* dt;
	QString filename = "savedImage.jpg";
	std::thread t;

	void getMatrice();
	void getImage();
private slots:
	void saveCalibration();
};
