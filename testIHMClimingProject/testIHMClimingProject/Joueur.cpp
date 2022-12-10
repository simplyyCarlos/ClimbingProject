#include "Joueur.h"

int Joueur::id = 0;

Joueur::Joueur(QString _pseudo, QString _password, Database* _db)
	: pseudo(_pseudo),password(_password),db(_db)
{
	id = id++;
	string tmp = "INSERT INTO Joueurs VALUES (" + to_string(id) + " , '" + pseudo.toStdString() + "' , " + to_string(std::hash<std::string>{}(password.toStdString())) + ");";
	const char* query = tmp.c_str();
	db->setSql(query);
	db->callRc();
	db->testQuery();
	db->closeDb();
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
