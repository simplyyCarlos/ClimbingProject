#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_testIHMClimingProject.h"
#include "dialogLogin.h"
#include "jeuMenu.h"
#include "editionMenu.h"

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
    editionMenu* em;
private slots:
    void openConnexion();
    void openMenuJeu();
    void openMenuEdition();
};
