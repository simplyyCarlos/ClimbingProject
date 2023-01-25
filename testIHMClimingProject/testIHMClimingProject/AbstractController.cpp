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