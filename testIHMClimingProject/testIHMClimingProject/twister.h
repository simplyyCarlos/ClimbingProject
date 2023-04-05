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
#include "Prise.h"

#define red QColor(238,34,34)
#define blue QColor(34,55,238)
#define green QColor(75,215,75)
#define yellow QColor(240,255,42)
#define grey QColor(110, 110, 110)


namespace py = pybind11;
using namespace boost::interprocess;

class TwisterMenu;

class Twister : public QWidget
{
private:
	Ui::twisterClass ui;
	TwisterMenu* parent;
	Data* dt;
	float* tabMain;
	QVector<Prise*> priseList;
	QVector<int> listColor;
	bool continueThread;
	int largeur, hauteur;
	QColor handColor[2];

	void paintEvent(QPaintEvent*) override;
	void detectionMain();
	void algorithmeJeu();
	void caliPosMain(QPolygonF*, QPolygonF*);
	void caliPosMain(QPointF& center1, QPointF& center2);
	QColor randomColor();

public:
	Twister(TwisterMenu*);
	~Twister();
	void lancerJeu();
	void setContinue();

};

