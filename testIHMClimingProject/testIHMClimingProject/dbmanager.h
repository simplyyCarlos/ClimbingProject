#pragma once

#include "QtSql/qsqldatabase.h"
#include "QtSql/qsqlerror.h"
#include "QtSql/qsqlquery.h"
#include "QtSql/qsqlrecord.h"
#include "qvector.h"
#include "qdebug.h"
#include "observer.h"

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
class DbManager : public Observable
{
private:
    static DbManager* instance;
    QSqlDatabase sqldb;
    QVector<Observer*> observerList;
    /**
    * @brief Constructor
    *
    * Constructor sets up connection with db and opens it
    * @param path - absolute path to db file
    */
    DbManager(const QString& path);
public:

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    static DbManager* getInstance();
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

    bool addJoueur(QString name, QString mdp);

    bool addPrises(float x, float y);

    /**
     * @brief Remove data of dt "dt" from db
     * @param dt - dt of data to remove.
     * @return true - data removed successfully, false - data not removed
     */
    bool removeParcours(int dt);

    /**
     * @brief Check if data of dt "dt" exists in db
     * @param dt - dt of data to  to check.
     * @return true - data exists, false - data does not exist
     */
    bool pseudoExists(QString log) const;

    /**
     * @brief Print values of all data in db
     */
    void printAllData() const;

    /**
     * @brief return values of all data in db
     */
    QVector<QVector<QString>>* getAllParcours() const;

    QVector<QVector<QString>>* getScoresParcours() const;

    QVector<QVector<QString>>* getScoresPong() const;

    QVector<QVector<QString>>* getScoresTwister() const;

    bool getLogin(QString log, QString mdp);
    /**
     * @brief Remove all data from db
     * @return true - all data removed successfully, false - not removed
     */
    bool removeAllData();

    int returnNbRow();

    void addObserver(Observer* observer) override;
    void removeObserver(Observer* observer) override;
    void notifyObserver() const override;
};