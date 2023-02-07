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
class testIHMClimingProject : public QMainWindow
{
    Q_OBJECT

public:
    testIHMClimingProject(QWidget *parent = nullptr);
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
    void openConnexion();
    void openMenuJeu();
    void openMenuEdition();
    void openCreation();
};
