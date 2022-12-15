#include "Prises.h"

Prises::Prises(float _x, float _y, DbManager* _db)
	: x(_x),y(_y),db(_db)
{
	string tmp = "INSERT INTO Prises VALUES (" + to_string(x) + " , " + to_string(y) + ");";
	const char* query = tmp.c_str();
	db->setSql(query);
	db->callRc();
	db->testQuery();
	db->closeDb();
}

float Prises::getX()
{
	return x;
}

float Prises::getY()
{
	return y;
}

DbManager* Prises::get
()
{
	return db;
}
