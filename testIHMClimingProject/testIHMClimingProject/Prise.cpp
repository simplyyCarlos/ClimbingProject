#include"Prise.h"

Prise::Prise(QPointF* _p, int _c) :p(_p), color(_c)
{
}

Prise::~Prise()
{
}

QPointF* Prise::getPrise() {
	return p;
}

QColor Prise::getColor() {
	switch (color)
	{
	case(0):
		return red;
	case(1):
		return blue;
	case(2):
		return green;
	case(3):
		return yellow;
	default:
		return red;
	}
}