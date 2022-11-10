#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_testIHMClimingProject.h"

class testIHMClimingProject : public QMainWindow
{
    Q_OBJECT

public:
    testIHMClimingProject(QWidget *parent = nullptr);
    ~testIHMClimingProject();

private:
    Ui::testIHMClimingProjectClass ui;
    QString currentFile;
private slots:
    void openConnexion();

};
