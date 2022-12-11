#pragma once
#include "sqlite3.h"
#include <iostream>
#include "qmap.h"
#include "qvector.h"
#include "qstring.h"
#include "observer.h"

using namespace std;
class Database : public Observable
{
private:
	sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    char* sql = nullptr;
    const char* data = "Callback function called";
    QVector<Observer*> observerList;
    static QVector<QString> resultat;
    const char* file;

public:
    Database(const char* file);
    static int callback(void* data, int argc, char** argv, char** azColName);
    void testQuery();
    const char* getSql();
    void setSql(const char* query);
    void callRc();
    void closeDb();
    QVector<QString> getResult();
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notifyObserver() const;
    Database(Database* db);
    void clearResult();
    Database& operator=(const Database& _db);
};

