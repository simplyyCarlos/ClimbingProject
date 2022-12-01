#include "Prises.h"

Prises::Prises(float _x, float _y, Database* _db)
	: x(_x),y(_y),db(_db)
{
}

float Prises::getX()
{
	return x;
}

float Prises::getY()
{
	return y;
}

Database* Prises::getDatabase()
{
	return db;
}
