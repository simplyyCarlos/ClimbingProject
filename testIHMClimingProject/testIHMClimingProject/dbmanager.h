#pragma once

#include "QtSql/qsqldatabase.h"
#include "QtSql/qsqlerror.h"
#include "QtSql/qsqlquery.h"
#include "QtSql/qsqlrecord.h"
#include "qvector.h"
#include "qdebug.h"
#include "observer.h"
#include "UserConnected.h"

/**
 * \class DbManager
 *
 * \brief SQL 
 Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with sqlite.
 */
class DbManager : public Observable
{
private:
    static DbManager* instance;
    QSqlDatabase sqldb;
    QVector<Observer*> observerList;
    UserConnected* uc;
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
    /**
     * @brief Singleton method to initialize and get the instance 
     * @return the instance of the class
    */
    static DbManager* getInstance();
    /**
     * @brief Set up of the singleton, delete the destructor by copy
     * @param db 
    */
    DbManager(DbManager& db) = delete;
    /**
     * @brief Set up of the singleton, delete the override '=' method
     * @param  
    */
    void operator=(const DbManager&) = delete;
    /**
     * @brief Method that test if the database id open
     * @return true if is open false is is not
    */
    bool isOpen() const;

    /**
     * @brief Method to add parcours to the database
     * @param name Name of the parcours
     * @param diff in a scale of 1 to 10 the difficulty of the parcours
     * @param date the date of creation
     * @return true if it correctly added false if not 
    */
    bool addParcours(QString name, int diff, QString date);
    /**
     * @brief Method to add player to the database 
     * @param name pseudo of the player 
     * @param mdp password of the player 
     * @return true if it correctly added false if not 
    */
    bool addJoueur(QString name, QString mdp);
    /**
     * @brief Method to add a climbing hold to the database
     * @param x position x of the hold 
     * @param y position y of the hold
     * @return true if it correctly added false if not 
    */
    bool addPrises(float x, float y);
    /**
     * @brief Method to add score to the database 
     * @param score score at the end of the game to add
     * @param jeu name of the game that is played
     * @return true if it correctly added false if not
    */
    bool addScore(int score, QString jeu);
    /**
     * @brief Method to get the id of the player with his name
     * @param player name of the player 
     * @return the id associated to his name
    */
    int getIdJoueur(QString player);

    /**
     * @brief Method to get the current date and time
     * @return the current date and time
    */
    QString currentDateTime();

    /**
     * @brief method to remove a parcours from the database 
     * @param id id of the parcours to remove 
     * @return true if it correctly deleted false if not
    */
    bool removeParcours(int id);

    /**
     * @brief Check if the pseudo already exist in the database
     * @param log pseudo to test 
     * @return true if it's in the database false if not
    */
    bool pseudoExists(QString log) const;
    /**
     * @brief Check if the parcours exists
     * @param id It is the id of the parcours to check
     * @return true if it's in the database false if not
    */
    bool parcoursExist(int id) const;

    /**
     * @brief Method to get all the parcours in the database
     * @return a list of a list which contains all the information in a row
    */
    QVector<QVector<QString>>* getAllParcours() const;
    /**
     * @brief Method to get all the score of game mode Parcours in the database
     * @return a list of a list which contains all the information in a row
    */
    QVector<QVector<QString>>* getScoresParcours() const;
    /**
     * @brief Method to get all the score of game mode Pong in the database
     * @return a list of a list which contains all the information in a row
    */
    QVector<QVector<QString>>* getScoresPong() const;
    /**
     * @brief Method to get all the score of game mode Twister in the database
     * @return a list of a list which contains all the information in a row
    */
    QVector<QVector<QString>>* getScoresTwister() const;
    /**
     * @brief Method to get all the score of game mode Parcours in the database for the connected user
     * @return a list of a list which contains all the information in a row
    */
    QVector<QVector<QString>>* getUsrScoresParcours() const;
    /**
     * @brief Method to get all the score of game mode Pong in the database for the connected user
     * @return a list of a list which contains all the information in a row
    */
    QVector<QVector<QString>>* getUsrScoresPong() const;
    /**
     * @brief Method to get all the score of game mode Twister in the database for the connected user
     * @return a list of a list which contains all the information in a row
    */
    QVector<QVector<QString>>* getUsrScoresTwister() const;

    /**
     * @brief Check if the player name and his password exists in the database 
     * @param log pseudo of the player 
     * @param mdp password of the player 
     * @return true if it exists and password is correct false if not 
    */
    bool getLogin(QString log, QString mdp);
    /**
     * @brief Remove all data from db
     * @return true - all data removed successfully, false - not removed
     */

    /**
     * @brief Method inherited from Observable class that add and observer to observerList
     * @param observer object to add to the list
    */
    void addObserver(Observer* observer) override;
    /**
     * @brief Method inherited from Observable class that remove an observer from the list
     * @param observer 
    */
    void removeObserver(Observer* observer) override;
    /**
     * @brief Method inherited from Observable class that notify all observer when something change in the database
    */
    void notifyObserver() const override;
};