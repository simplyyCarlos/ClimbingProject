#pragma once
#include "dbmanager.h"
#include <string>

class Prises
{
private:
	float x, y;
	DbManager* db;
public:
	Prises(float _x, float _y, DbManager* _db);
	float getX();
	float getY();
	DbManager* get
	();
};