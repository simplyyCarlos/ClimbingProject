#include "Parcours.h"

int Parcours::id = 0;

Parcours::Parcours(int _difficulte, QString _nom, Database* _db)
	:difficulte(_difficulte),nom(_nom),db(_db)
{
	id = id++;
	string tmp = "INSERT INTO Parcours VALUES (" + to_string(id) + " , '" + nom.toStdString() + "' , " +to_string(difficulte)+ ");";
	const char* query = tmp.c_str();
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

Database* Parcours::getDatabase()
{
	return db;
}
