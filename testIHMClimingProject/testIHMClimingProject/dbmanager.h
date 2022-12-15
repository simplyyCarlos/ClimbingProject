#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/qsqldatabase.h>
#include <QJsonObject>
#include <QVector>
#include "observer.h"
#include "Parcours.h"

/**
 * \class DbManager
 *
 * \brief SQL 
 Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with sqlite:
 * 1. $ sqlite3 pollution.db
 * 2. sqlite> CREATE TABLE pollution(ids integer primary key, dt interger, aqi integer);
 * 3. sqlite> .quit
 */
class DbManager
{
private:
    DbManager* instance;
    QSqlDatabase sqldb;
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    DbManager(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    DbManager* getInstance();
    DbManager(DbManager& db) = delete;
    void operator=(const DbManager&) = delete;

    bool isOpen() const;

    /**
     * @brief Add data to db
     * @param dt - date time
     * @param aqi - air quality indice
     * @return true - data added successfully, false - data not added
     */
    bool addParcours(QString name, int diff, QString date);

    /**
     * @brief Remove data of dt "dt" from db
     * @param dt - dt of data to remove.
     * @return true - data removed successfully, false - data not removed
     */
    bool removeData(int dt);

    /**
     * @brief Check if data of dt "dt" exists in db
     * @param dt - dt of data to  to check.
     * @return true - data exists, false - data does not exist
     */
    bool entryExists(int dt) const;

    /**
     * @brief Print values of all data in db
     */
    void printAllData() const;

    /**
     * @brief return values of all data in db
     */
    QVector<QVector<int>>* getAllData() const;

    /**
     * @brief Remove all data from db
     * @return true - all data removed successfully, false - not removed
     */
    bool removeAllData();

    int returnNbRow();
};

#endif // DBMANAGER_H
