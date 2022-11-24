#pragma once
#include "qstring.h"
class Joueur
{
private:
	int id;
	QString pseudo, password;
public:
	Joueur(int _id,QString _pseudo, QString _password);
	int getId();
	QString getPseudo();
	QString getPassword();
};

