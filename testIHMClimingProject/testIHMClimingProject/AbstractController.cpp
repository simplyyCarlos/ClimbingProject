#include "AbstractController.h"

ControllerRemoveParcours::ControllerRemoveParcours()
{
	db = db->getInstance();
}

void ControllerRemoveParcours::control(int id)
{
	db->removeParcours(id);
}