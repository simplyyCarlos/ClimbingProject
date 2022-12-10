#include "Data.h"

Data::Data()
{
	calibrate = false;
}

Data::~Data()
{
}

void Data::addPrise(QPointF* pos) {
	listPrise.append(pos);
}