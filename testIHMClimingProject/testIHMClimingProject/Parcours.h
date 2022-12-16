#pragma once
#include "Prises.h"
#include "qvector.h"
#include "qstring.h"
#include "dbmanager.h"
#include "observer.h"

class Parcours
{
private:
	static int id;
	int difficulte;
	QString nom;
	QString date;
	QVector<Prises*> listPrise;
	DbManager* db;
	QVector<Observer*> observerList;
public:
	Parcours(int _difficulte, QString _nom,QString _date);
	void add(Prises* p);
	void remove(int i);
	int getId();
	int getDifficulte();
};

