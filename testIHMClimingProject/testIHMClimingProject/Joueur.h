#pragma once
#include "qstring.h"
#include "Database.h"
class Joueur
{
private:
	static int id;
	QString pseudo, password;
	Database* db;
public:
	Joueur(QString _pseudo, QString _password, Database* _db);
	int getId();
	QString getPseudo();
	QString getPassword();
	Database* getDatabase();
};

