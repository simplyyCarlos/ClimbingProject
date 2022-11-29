#include "Parcours.h"

Parcours::Parcours(int _id, int _difficulte, QString _nom)
	: id(_id),difficulte(_difficulte),nom(_nom)
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
