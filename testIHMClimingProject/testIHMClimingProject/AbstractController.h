#pragma once
#include "Database.h"
class AbstractController
{
public:
	virtual ~AbstractController() {}
	virtual void control(int id) = 0;
};

class ControllerRemoveParcours : public AbstractController
{
private:
	Database* db;
public:
	ControllerRemoveParcours(Database* _db);
	void control(int id);
};