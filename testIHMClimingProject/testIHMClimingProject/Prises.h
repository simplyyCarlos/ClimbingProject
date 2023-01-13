#pragma once
#include "dbmanager.h"

class Prises
{
private:
	float x, y;
	DbManager* db;
public:
	Prises(float _x, float _y);
	~Prises();
	float getX();
	float getY();
};