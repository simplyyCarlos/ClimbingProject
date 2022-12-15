#include "Parcours.h"

int Parcours::id = 0;

Parcours::Parcours(int _difficulte, QString _nom)
	:difficulte(_difficulte),nom(_nom)
{
	db = db->getInstance();
	id = id++;
	QString query = "INSERT INTO Parcours VALUES (" + QString::number(id) + " , '" + nom + "' , " +QString::number(difficulte)+ ");";
	db->addParcours(id,nom,difficulte,date);
	db->setSql(query);
	db->callRc();
	db->testQuery();
	db->closeDb();
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

DbManager* Parcours::getDatabase()
{
	return db;
}
