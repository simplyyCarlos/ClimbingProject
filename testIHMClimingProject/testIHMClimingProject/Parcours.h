#pragma once
#include "Prises.h"
#include "qvector.h"
#include "qstring.h"
#include "Database.h"
class Parcours
{
private:
	static int id;
	int difficulte;
	QString nom;
	QVector<Prises*> listPrise;
	Database* db;
public:
	Parcours(int _difficulte, QString _nom,Database* _db);
	void add(Prises* p);
	void remove(int i);
	int getId();
	int getDifficulte();
	Database* getDatabase();
};

