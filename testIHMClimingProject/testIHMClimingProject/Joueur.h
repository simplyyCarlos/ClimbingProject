#pragma once
#include "qstring.h"
#include "Database.h"
#include "observer.h"
#include "qlist.h"

class Joueur
{
private:
	static int id;
	QString pseudo, password;
	Database* db;
	QVector<Observer*> observerList;
public:
	Joueur(QString _pseudo, QString _password, Database* _db);
	int getId();
	QString getPseudo();
	QString getPassword();
	Database* getDatabase();
};

