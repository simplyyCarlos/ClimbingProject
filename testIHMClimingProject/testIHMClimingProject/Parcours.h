#pragma once
#include "Prises.h"
#include "qvector.h"
#include "qstring.h"
class Parcours
{
private:
	int id, difficulte;
	QString nom;
	QVector<Prises*> listPrise;
public:
	Parcours(int _id, int _difficulte, QString _nom);
	void add(Prises* p);
	int getId();
	int getDifficulte();

};

