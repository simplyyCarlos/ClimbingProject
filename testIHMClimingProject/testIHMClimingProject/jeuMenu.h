#pragma once
#include "ui_jeuMenu.h"
#include "choixParcoursMenu.h"
#include "dbmanager.h"
#include "PongMenu.h"
#include "twisterMenu.h"


class jeuMenu : public QWidget
{
    Q_OBJECT

public:
    jeuMenu(QWidget* _parent, Data* dt);
    ~jeuMenu();

private:
    Ui::jeuMenuClass ui;
    QWidget* parent;
    choixParcoursMenu* cpm;
    PongMenu* pm;
    DbManager* db;
    TwisterMenu* tw;
    Data* dt;
private slots:
    void pushbackButton();
    void openMenuChoixParcours();
    void openTwister();
    void openReflex();
    void openPongMenu();
};

