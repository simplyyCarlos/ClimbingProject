#include "AbstractController.h"

ControllerRemoveParcours::ControllerRemoveParcours()
{
	db = db->getInstance();
}

void ControllerRemoveParcours::control(int id)
{
	string tmp = "DELETE FROM Parcours WHERE id_Parcours=" + to_string(id) + " ;";;
	const char* query = tmp.c_str();
	db->setSql(query);
	db->callRc();
	db->testQuery();
}