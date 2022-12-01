#include "Joueur.h"

Joueur::Joueur(int _id, QString _pseudo, QString _password, Database* _db)
	: id(_id),pseudo(_pseudo),password(_password),db(_db)
{
}

int Joueur::getId()
{
	return id;
}

QString Joueur::getPseudo()
{
	return pseudo;
}

QString Joueur::getPassword()
{
	return password;
}

Database* Joueur::getDatabase()
{
	return db;
}
