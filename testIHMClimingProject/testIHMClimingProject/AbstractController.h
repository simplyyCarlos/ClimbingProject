#pragma once
#include "dbmanager.h"
class AbstractController
{
public:
	virtual ~AbstractController() {}
	virtual void control(int id) = 0;
};

class ControllerRemoveParcours : public AbstractController
{
private:
	DbManager* db;
public:
	ControllerRemoveParcours(DbManager* _db);
	void control(int id);
};