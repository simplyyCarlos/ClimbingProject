#include "AbstractController.h"

ControllerRemoveParcours::ControllerRemoveParcours()
{
	db = db->getInstance();
}

ControllerRemoveParcours::~ControllerRemoveParcours()
{
}

void ControllerRemoveParcours::control(int id)
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

void ControllerAddScore::control(int sc, QString jeu)
{
	db->addScore(sc, jeu);
}
