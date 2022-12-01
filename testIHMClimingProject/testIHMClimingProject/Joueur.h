#pragma once
#include "qstring.h"
#include "Database.h"
class Joueur
{
private:
	int id;
	QString pseudo, password;
	Database* db;
public:
	Joueur(int _id,QString _pseudo, QString _password, Database* _db);
	int getId();
	QString getPseudo();
	QString getPassword();
	Database* getDatabase();
};

