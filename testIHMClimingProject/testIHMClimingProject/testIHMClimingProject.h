#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_testIHMClimingProject.h"
#include "dialogLogin.h"
#include "jeuMenu.h"
#include "editionMenu.h"
#include "Database.h"
#include "paramMenu.h"
class testIHMClimingProject : public QMainWindow
{
    Q_OBJECT

public:
    testIHMClimingProject(Database* _db,QWidget *parent = nullptr);
    ~testIHMClimingProject();

private:
    Ui::testIHMClimingProjectClass ui;
    QString currentFile;
    jeuMenu* jm;
    Database* db;
    dialogLogin* log;
    paramMenu* pm;
private slots:
    void openConnexion();
    void openMenuJeu();
    void openMenuEdition();
};
