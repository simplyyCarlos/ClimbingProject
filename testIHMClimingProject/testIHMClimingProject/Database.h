#pragma once
#include "sqlite3.h"
#include <iostream>

using namespace std;
class Database
{
private:
	sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    const char* sql;
    const char* data = "Callback function called";
public:
    Database(const char* file);
    static int callback(void* data, int argc, char** argv, char** azColName);
    void testQuery();
    const char* getSql();
    void setSql(const char* query);
    void callRc();
    void closeDb();
};

