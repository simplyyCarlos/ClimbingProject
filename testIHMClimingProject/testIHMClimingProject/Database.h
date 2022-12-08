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
    char* sql;
    const char* data = "Callback function called";
    QVector<Observer*> observerList;
    static QMap<QString, QString> resultat;

public:
    Database(const char* file);
    static int callback(void* data, int argc, char** argv, char** azColName);
    void testQuery();
    const char* getSql();
    void setSql(const char* query);
    void callRc();
    void closeDb();
    QMap<QString, QString> getResult();
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notifyObserver() const;
};

