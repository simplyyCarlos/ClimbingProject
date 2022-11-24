#include "Joueur.h"

Joueur::Joueur(int _id, QString _pseudo, QString _password)
	: id(_id),pseudo(_pseudo),password(_password)
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
