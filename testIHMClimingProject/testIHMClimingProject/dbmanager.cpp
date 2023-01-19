#include "dbmanager.h"
#include "qdir.h"

DbManager* DbManager::instance = nullptr;

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
        instance = new DbManager(QDir::currentPath() + "/../climbingProject.db");
    }
    return instance;
}

bool DbManager::isOpen() const
{
    return sqldb.isOpen();
}

bool DbManager::addParcours(QString name, int diff, QString date) {

    bool success = false;

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO Parcours (Nom,Difficulte,Date) VALUES (:name,:diff,:date)");
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

bool DbManager::addJoueur(QString name, QString mdp) {

    bool success = false;

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO Joueurs (pseudo,password) VALUES (:name,:mdp)");
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

bool DbManager::removeParcours(int id)
{
    bool success = false;

    if (parcoursExist(id))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM Parcours WHERE id_Parcours = (:id)");
        queryDelete.bindValue(":id", id);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove data failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove data failed: id doesnt exist";
    }
    notifyObserver();
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

QVector<QVector<QString>>* DbManager::getScoresParcours() const
{
    QSqlQuery query("SELECT j.pseudo,h.chrono,p.Nom,h.date_jeu FROM Historique h,Joueurs j,Parcours p WHERE h.id_Joueur = j.id_Joueur and h.id_Parcours = p.id_Parcours and h.jeu = 'Parcours' ORDER BY h.score DESC;");
    int idPseudo = query.record().indexOf("pseudo");
    int idChrono = query.record().indexOf("chrono");
    int idName = query.record().indexOf("Nom");
    int idDate = query.record().indexOf("date_jeu");
    QVector<QVector<QString>>* res = new  QVector<QVector<QString>>();
    while (query.next()) {
        QVector<QString> data;
        data.append(query.value(idPseudo).toString());
        data.append(query.value(idChrono).toString());
        data.append(query.value(idName).toString());
        data.append(query.value(idDate).toString());
        res->append(data);
    }
    return res;
}

QVector<QVector<QString>>* DbManager::getScoresPong() const
{
    QSqlQuery query("SELECT j.pseudo,h.score,p.Nom,h.date_jeu FROM Historique h,Joueurs j,Parcours p WHERE h.id_Joueur = j.id_Joueur and h.id_Parcours = p.id_Parcours and h.jeu = 'Pong' ORDER BY h.score DESC;");
    int idPseudo = query.record().indexOf("pseudo");
    int idScore = query.record().indexOf("score");
    int idName = query.record().indexOf("Nom");
    int idDate = query.record().indexOf("date_jeu");
    QVector<QVector<QString>>* res = new  QVector<QVector<QString>>();
    while (query.next()) {
        QVector<QString> data;
        data.append(query.value(idPseudo).toString());
        data.append(query.value(idScore).toString());
        data.append(query.value(idName).toString());
        data.append(query.value(idDate).toString());
        res->append(data);
    }
    return res;
}

QVector<QVector<QString>>* DbManager::getScoresTwister() const
{
    QSqlQuery query("SELECT j.pseudo,h.score,h.date_jeu FROM Historique h,Joueurs j,Parcours p WHERE h.id_Joueur = j.id_Joueur and h.id_Parcours = p.id_Parcours and h.jeu = 'Twister' ORDER BY h.score DESC;");
    int idPseudo = query.record().indexOf("pseudo");
    int idScore = query.record().indexOf("score");
    int idDate = query.record().indexOf("date_jeu");
    QVector<QVector<QString>>* res = new  QVector<QVector<QString>>();
    while (query.next()) {
        QVector<QString> data;
        data.append(query.value(idPseudo).toString());
        data.append(query.value(idScore).toString());
        data.append(query.value(idDate).toString());
        res->append(data);
    }
    return res;
}

bool DbManager::getLogin(QString log, QString mdp) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Joueurs WHERE pseudo = (:log) and password = (:mdp)");
    query.bindValue(":log", log);
    query.bindValue(":mdp", mdp);

    int exists = false;

    if (query.exec())
    {
        if (query.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "data exists failed: " << query.lastError();
    }

    return exists;
}

bool DbManager::pseudoExists(QString log) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT pseudo FROM Joueurs WHERE pseudo = (:log)");
    checkQuery.bindValue(":log", log);

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

bool DbManager::parcoursExist(int id) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM Parcours WHERE id_Parcours = (:id)");
    checkQuery.bindValue(":id", id);

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

void DbManager::addObserver(Observer* observer)
{
    observerList.append(observer);
}

void DbManager::removeObserver(Observer* observer)
{
    observerList.remove(observerList.indexOf(observer));
}

void DbManager::notifyObserver() const
{
    for (auto index : observerList) {
        index->updateModel();
    }
}