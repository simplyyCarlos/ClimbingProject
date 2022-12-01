#pragma once
#include "Database.h"
class Prises
{
private:
	float x, y;
	Database* db;
public:
	Prises(float _x, float _y, Database* _db);
	float getX();
	float getY();
	Database* getDatabase();
};