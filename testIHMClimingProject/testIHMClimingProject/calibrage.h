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
#include <filesystem>
#include <iostream>
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
using namespace std;
namespace py = pybind11;
using namespace boost::interprocess;



class Calibrage : public QWidget {
	Q_OBJECT
public:
	Calibrage(QWidget* _parent, Data* dt);
	Calibrage(Calibrage*);
	~Calibrage();

	void calibrage();
	//void set_matrix(py::array_t<double>);
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
