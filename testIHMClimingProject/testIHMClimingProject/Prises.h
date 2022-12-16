#pragma once
#include "dbmanager.h"
#include <string>

class Prises
{
private:
	float x, y;
	DbManager* db;
public:
	Prises(float _x, float _y);
	float getX();
	float getY();
};