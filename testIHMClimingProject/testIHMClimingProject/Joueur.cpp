#include "Joueur.h"

int Joueur::id = 0;

Joueur::Joueur(QString _pseudo, QString _password)
	: pseudo(_pseudo),password(_password)
{
	id = id++;
	db = db->getInstance();
	db->addJoueur(id,pseudo,password);
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

DbManager* Joueur::getDb()
{
	return db;
}
