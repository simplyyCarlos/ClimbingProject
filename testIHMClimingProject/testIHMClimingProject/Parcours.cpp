#include "Parcours.h"

int Parcours::id = 0;

Parcours::Parcours(int _difficulte, QString _nom,QString _date)
	:difficulte(_difficulte),nom(_nom),date(_date)
{
	db = db->getInstance();
	id = id++;
	db->addParcours(id,nom,difficulte,date);
}

Parcours::~Parcours()
{
}

void Parcours::add(Prises* p)
{
	listPrise.append(p);
}

void Parcours::remove(int i)
{
	listPrise.remove(i);
}

int Parcours::getId()
{
	return id;
}

int Parcours::getDifficulte()
{
	return difficulte;
}
