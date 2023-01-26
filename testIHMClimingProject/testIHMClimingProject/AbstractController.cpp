#include "AbstractController.h"

ControllerRemoveParcours::ControllerRemoveParcours()
{
	db = db->getInstance();
}

ControllerRemoveParcours::~ControllerRemoveParcours()
{
}

void ControllerRemoveParcours::control(int id, QString jeu)
{
	db->removeParcours(id);
}

ControllerAddScore::ControllerAddScore()
{
	db = db->getInstance();
}

ControllerAddScore::~ControllerAddScore()
{
}

void ControllerAddScore::control(int id, QString jeu)
{
	db->addScore(id, jeu);
}
