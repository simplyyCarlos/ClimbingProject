#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_testIHMClimingProject.h"
#include "dialogLogin.h"
#include "jeuMenu.h"
#include "dbmanager.h"
#include "paramMenu.h"
#include "calibrage.h"
#include "Data.h"
#include "UserConnected.h"
#include "dialogCreation.h"
/**
 * @brief Main window where you can acced to all the different window and the connexion
*/
class testIHMClimingProject : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of the class
     * @param parent window that create this class 
    */
    testIHMClimingProject(QWidget *parent = nullptr);
    /**
     * @brief Destructor of the class
    */
    ~testIHMClimingProject();

private:
    Ui::testIHMClimingProjectClass ui;
    QString currentFile;
    jeuMenu* jm;
    DbManager* db;
    dialogLogin* log;
    dialogCreation* dc;
    paramMenu* pm;
    Data* dt;
    Calibrage* ca;
    UserConnected* uc;
private slots:
    /**
     * @brief Action to open the connexion dialog
    */
    void openConnexion();
    /**
     * @brief Action to open the game menue
    */
    void openMenuJeu();
    /**
     * @brief Action to open the parameter menu 
    */
    void openMenuEdition();
    /**
     * @brief Action to open the account creation window 
    */
    void openCreation();
};
