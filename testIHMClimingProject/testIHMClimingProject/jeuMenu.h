#pragma once
#include "ui_jeuMenu.h"
#include "choixParcoursMenu.h"
#include "dbmanager.h"
#include "PongMenu.h";

class jeuMenu : public QWidget
{
    Q_OBJECT

public:
    jeuMenu(DbManager* _db,QWidget* _parent);
    ~jeuMenu();

private:
    Ui::jeuMenuClass ui;
    QWidget* parent;
    choixParcoursMenu* cpm;
    PongMenu* pm;
    DbManager* db;
private slots:
    void pushbackButton();
    void openMenuChoixParcours();
    void openPongMenu();
};

