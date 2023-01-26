#pragma once
#include "dbmanager.h"
class AbstractController
{
public:
	virtual ~AbstractController() {}
	virtual void control(int id, QString jeu = "") = 0;
};

class ControllerRemoveParcours : public AbstractController
{
private:
	DbManager* db;
public:
	ControllerRemoveParcours();
	~ControllerRemoveParcours();
	void control(int id ,QString jeu = "") override;
};

class ControllerAddScore : public AbstractController
{
private:
	DbManager* db;
public:
	ControllerAddScore();
	~ControllerAddScore();
	void control(int id, QString jeu = "") override;
};