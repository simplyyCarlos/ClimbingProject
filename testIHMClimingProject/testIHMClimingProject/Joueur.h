#pragma once
#include "qstring.h"
#include "dbmanager.h"
#include "observer.h"
#include "qlist.h"

class Joueur
{
private:
	static int id;
	QString pseudo, password;
	DbManager* db;
	QVector<Observer*> observerList;
public:
	Joueur(QString _pseudo, QString _password);
	~Joueur();
	int getId();
	QString getPseudo();
	QString getPassword();
	DbManager* getDb();
};

