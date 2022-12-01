#include "Database.h"

Database::Database(const char* file)
{
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
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
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
    sql = query;
}

void Database::callRc()
{
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
}

void Database::closeDb()
{
    sqlite3_close(db);
}
