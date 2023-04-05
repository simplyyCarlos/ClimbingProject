#pragma once
#include "ui_twister.h"
#include "Data.h"
#include "qscreen.h"
#include "qpainter.h"
#include "qpen.h"
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
#include <iostream>
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstdlib>
#include <fstream>
#include <cmath>



namespace py = pybind11;
using namespace boost::interprocess;

class TwisterMenu;

class Reflex : public QWidget
{
private:
	Ui::twisterClass ui;
	TwisterMenu* parent;
	Data* dt;
	float* tabMain;
	QVector<QPointF*> listObjectif, listTouche, prise;
	bool continueThread;
	int largeur, hauteur;

	void paintEvent(QPaintEvent*) override;
	void detectionMain();
	void algorithmeJeu();
	void caliPosMain(QPolygonF*, QPolygonF*);
	void caliPosMain(QPointF& center1, QPointF& center2);

public:
	Reflex(TwisterMenu*);
	~Reflex();
	void lancerJeu();
	void setContinue();

};


