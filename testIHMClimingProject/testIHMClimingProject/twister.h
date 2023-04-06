#pragma once
#include "ui_twister.h"
#include "Data.h"
#include "Jeu.h"

#define red QColor(238,34,34)
#define blue QColor(34,55,238)
#define green QColor(75,215,75)
#define yellow QColor(240,255,42)
#define grey QColor(110, 110, 110)


namespace py = pybind11;
using namespace boost::interprocess;

class TwisterMenu;

class Twister : public Jeu
{
private:
	QVector<Prise*> priseList;
	QVector<int> listColor;
	QColor handColor[2];

	void paintEvent(QPaintEvent*) override;
	void algorithmeJeu() override;
	QColor randomColor();

public:
	Twister(TwisterMenu*);
};

