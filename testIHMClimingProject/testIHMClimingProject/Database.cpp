#include "Database.h"

QMap <QString, QString> Database::resultat = {};

Database::Database(const char* file)
{
    this->file = file;
    rc = sqlite3_open(file, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }
}

int Database::callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    resultat.clear();
    fprintf(stderr, "%s: ", (const char*)data);
    for (i = 0; i < argc; i++) {
        QString tmp = azColName[i];
        QString res = argv[i];
        resultat.insert(tmp,res);
    }
    return 0;
}

void Database::testQuery()
{
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Query Execute Succesfully\n");
    }
}

const char* Database::getSql()
{
    return sql;
}

void Database::setSql(const char* query)
{
    std::strncpy(sql, query, strlen(query));
}

void Database::callRc()
{
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
}

void Database::closeDb()
{
    sqlite3_close(db);
}

QMap<QString, QString> Database::getResult()
{
    return resultat;
}

void Database::addObserver(Observer* observer)
{
    observerList.append(observer);
}

void Database::removeObserver(Observer* observer)
{
    observerList.remove(observerList.indexOf(observer));
}

void Database::notifyObserver() const
{
    for (auto index : observerList) {
        index->updateModel();
    }
}

Database::Database(Database* db)
{
    this->db = db->db;
    this->zErrMsg = db->zErrMsg;
    this->rc = db->rc;
    this->sql = db->sql;
    this->data = db->data;
    this->observerList = db->observerList;
    this->resultat = db->resultat;
    this->file = db->file;

    rc = sqlite3_open(file, &this->db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(this->db));
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }
}