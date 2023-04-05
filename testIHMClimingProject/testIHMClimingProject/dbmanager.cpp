#include "dbmanager.h"
#include "qdir.h"
#include "qstandardpaths.h"
#include <qapplication.h>

DbManager* DbManager::instance = nullptr;

DbManager::DbManager(const QString &path)
{
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/climbingProject.db";
    qDebug() << path;
    qDebug() << dbPath;

    QCoreApplication::addLibraryPath(qApp->applicationDirPath());

    // Add the SQLite driver and check if it's available
    sqldb = QSqlDatabase::addDatabase("QSQLITE");
    QStringList drivers = QSqlDatabase::drivers();
    if (!drivers.contains("QSQLITE")) {
        qDebug() << "SQLite driver not available";
        return;
    }

    if (!QFile::exists(dbPath)) {
        qDebug() << "copy executed";
        QFile::copy(":/testIHMClimingProject/climbingProject.db", dbPath);
    }

    sqldb.setDatabaseName(dbPath);
    uc = uc->getInstance();
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
        qDebug() << "Database closed";
    }
}

DbManager* DbManager::getInstance()
{
    if (instance == nullptr) {
        instance = new DbManager(":/testIHMClimingProject/climbingProject.db");
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
        qDebug() << "add parcours succed";
    }
    else
    {
        qDebug() << "add parcours failed: " << queryAdd.lastError();
    }

    return success;
}

bool DbManager::addScore(int score, QString jeu) {

    QSqlQuery queryAdd;
    bool success = false;
    QString player = uc->getName();
    int idPlayer = getIdJoueur(player);
    if (idPlayer == 7) {
        player = "anonyme";
    }
    if (jeu == "Twister" || jeu == "Pong") {
        queryAdd.prepare("INSERT INTO Historique (id_Joueur,date_jeu,score,jeu) VALUES (:idJ,:date,:score,:jeu)");
        queryAdd.bindValue(":idJ", idPlayer);
        queryAdd.bindValue(":date", currentDateTime());
        queryAdd.bindValue(":score", score);
        queryAdd.bindValue(":jeu", jeu);
    }
    else {
        queryAdd.prepare("INSERT INTO Historique (id_Joueur,id_Parcours,date_jeu,score,jeu) VALUES (:idJ,:idP,:date,:chrono,:jeu)");
        queryAdd.bindValue(":idJ", idPlayer);
        queryAdd.bindValue(":idP", 1);
        queryAdd.bindValue(":date", currentDateTime());
        queryAdd.bindValue(":chrono", score);
        queryAdd.bindValue(":jeu", jeu);
    }

    if (queryAdd.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "add dt/aqi failed: " << queryAdd.lastError();
    }
    notifyObserver();
    return success;
}

int DbManager::getIdJoueur(QString player)
{
    QSqlQuery query;
    query.prepare("SELECT id_Joueur FROM Joueurs WHERE pseudo = (:ply)");
    query.bindValue(":ply", player);
    int idJoueur = query.record().indexOf("id_Joueur");

    if (query.exec())
    {
        if (query.next())
        {
            return query.value(idJoueur).toInt();
        }
    }
    else
    {
        return 7;
        qDebug() << "data exists failed: " << query.lastError();
    }
}

QString DbManager::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
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
    QSqlQuery query("SELECT j.pseudo,h.chrono,p.Nom,h.date_jeu FROM Historique h,Joueurs j,Parcours p WHERE h.id_Joueur = j.id_Joueur and h.id_Parcours = p.id_Parcours and h.jeu = 'Parcours' GROUP BY j.pseudo ORDER BY h.score DESC; ");
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
    QSqlQuery query("SELECT DISTINCT j.pseudo,h.score,h.date_jeu FROM Historique h,Joueurs j,Parcours p WHERE h.id_Joueur = j.id_Joueur and h.jeu = 'Pong' GROUP BY j.pseudo ORDER BY h.score DESC;");
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

QVector<QVector<QString>>* DbManager::getScoresTwister() const
{
    QSqlQuery query("SELECT DISTINCT j.pseudo,h.score,h.date_jeu FROM Historique h,Joueurs j,Parcours p WHERE h.id_Joueur = j.id_Joueur and h.jeu = 'Twister' GROUP BY j.pseudo ORDER BY h.score DESC;");
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

QVector<QVector<QString>>* DbManager::getUsrScoresParcours() const {
    QSqlQuery query("SELECT j.pseudo,h.chrono,p.Nom,h.date_jeu FROM Historique h,Joueurs j,Parcours p WHERE h.id_Joueur = j.id_Joueur and h.id_Parcours = p.id_Parcours and h.jeu = 'Parcours' and j.pseudo = '"+ uc->getName() + "' ORDER BY h.score DESC; ");
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

QVector<QVector<QString>>* DbManager::getUsrScoresPong() const {
    QSqlQuery query("SELECT DISTINCT j.pseudo,h.score,p.Nom,h.date_jeu FROM Historique h,Joueurs j,Parcours p WHERE h.id_Joueur = j.id_Joueur and h.jeu = 'Pong' and j.pseudo = '" + uc->getName() + "' ORDER BY h.score DESC;");
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

QVector<QVector<QString>>* DbManager::getUsrScoresTwister() const {
    QSqlQuery query("SELECT DISTINCT j.pseudo,h.score,h.date_jeu FROM Historique h,Joueurs j,Parcours p WHERE h.id_Joueur = j.id_Joueur and h.jeu = 'Twister' and j.pseudo = '" + uc->getName() + "' ORDER BY h.score DESC;");
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