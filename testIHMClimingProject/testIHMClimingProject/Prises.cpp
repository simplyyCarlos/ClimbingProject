#include "Prises.h"

Prises::Prises(float _x, float _y)
	: x(_x),y(_y)
{
	db = db->getInstance();
	db->addPrises(x, y);
}

float Prises::getX()
{
	return x;
}

float Prises::getY()
{
	return y;
}
