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
	ControllerRemoveParcours();
	~ControllerRemoveParcours();
	void control(int id) override;
};

class ControllerAddScore : public AbstractController
{
private:
	DbManager* db;
public:
	ControllerAddScore();
	~ControllerAddScore();
	void control(int sc, QString jeu);
};