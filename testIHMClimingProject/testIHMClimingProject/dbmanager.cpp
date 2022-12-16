#include "dbmanager.h"
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlrecord.h>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    sqldb = QSqlDatabase::addDatabase("QSQLITE");
    sqldb.setDatabaseName(path);

    if (!sqldb.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (sqldb.isOpen())
    {
        sqldb.close();
    }
}

DbManager* DbManager::getInstance()
{
    if (instance == nullptr) {
        instance = new DbManager("/climbingProject.db");
    }
    return instance;
}

bool DbManager::isOpen() const
{
    return sqldb.isOpen();
}

bool DbManager::addParcours(int id, QString name, int diff, QString date) {

    bool success = false;

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO Parcours VALUES (:id,:name,:diff,:date)");
    queryAdd.bindValue(":id", id);
    queryAdd.bindValue(":name", name);
    queryAdd.bindValue(":diff", diff);
    queryAdd.bindValue(":date", date);

    if(queryAdd.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "add dt/aqi failed: " << queryAdd.lastError();
    }



    return success;
}

bool DbManager::addJoueur(int id, QString name, QString mdp) {

    bool success = false;

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO Joueurs VALUES (:id,:name,:mdp)");
    queryAdd.bindValue(":id", id);
    queryAdd.bindValue(":name", name);
    queryAdd.bindValue(":mdp", mdp);

    if (queryAdd.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "add dt/aqi failed: " << queryAdd.lastError();
    }



    return success;
}

bool DbManager::addPrises(float x, float y) {

    bool success = false;

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO Joueurs VALUES (:x,:y)");
    queryAdd.bindValue(":x", x);
    queryAdd.bindValue(":y", y);

    if (queryAdd.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "add dt/aqi failed: " << queryAdd.lastError();
    }



    return success;
}

bool DbManager::removeData(int dt)
{
    bool success = false;

    if (entryExists(dt))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM pollution WHERE dt = (:dt)");
        queryDelete.bindValue(":dt", dt);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove data failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove data failed: dt doesnt exist";
    }

    return success;
}

void DbManager::printAllData() const
{
    qDebug() << "Data in db:";
    QSqlQuery query("SELECT * FROM pollution");
    int idDt = query.record().indexOf("dt");
    int idAqi = query.record().indexOf("aqi");
    while (query.next())
    {
        int dt = query.value(idDt).toInt();
        int aqi = query.value(idAqi).toInt();
        qDebug() << "===" << dt << " " << aqi;
    }
}

QVector<QVector<QString>>* DbManager::getAllParcours() const
{
    QSqlQuery query("SELECT * FROM Parcours;");
    int idParcours = query.record().indexOf("id_Parcours");
    int idName = query.record().indexOf("Nom");
    int idDiff = query.record().indexOf("Difficulte");
    int idDate = query.record().indexOf("Date");
    QVector<QVector<QString>>* res = new  QVector<QVector<QString>>();
    while (query.next()) {
        QVector<QString> data;
        data.append(query.value(idParcours).toString());
        data.append(query.value(idName).toString());
        data.append(query.value(idDiff).toString());
        data.append(query.value(idDate).toString());
        res->append(data);
    }
    return res;
}

bool DbManager::entryExists(int dt) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT dt FROM pollution WHERE dt = (:dt)");
    checkQuery.bindValue(":dt", dt);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "data exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::removeParcours() {

}

bool DbManager::removeAllData()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM pollution");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all data failed: " << removeQuery.lastError();
    }

    return success;
}

int DbManager::returnNbRow()
{
    QSqlQuery query("SELECT count(*) FROM pollution;");
    int count = query.record().indexOf("count(*)");
    return query.value(count).toInt();
}
