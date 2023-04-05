#pragma once
#include "qpoint.h"
#include "qcolor.h"

#define red QColor(238,34,34)
#define blue QColor(34,55,238)
#define green QColor(75,215,75)
#define yellow QColor(240,255,42)

class Prise
{
public:
	Prise(QPointF*, int);
	~Prise();
	QPointF* getPrise();
	QColor getColor();

private:
	QPointF* p;
	int color;
};

