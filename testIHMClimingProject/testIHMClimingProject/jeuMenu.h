#pragma once
#include "ui_jeuMenu.h"
#include "choixParcoursMenu.h"
#include "scoresMenu.h"
#include "Database.h"
#include "twisterMenu.h"


class jeuMenu : public QWidget
{
    Q_OBJECT

public:
    jeuMenu(Database* _db,QWidget* _parent, Data* dt);
    ~jeuMenu();

private:
    Ui::jeuMenuClass ui;
    QWidget* parent;
    choixParcoursMenu* cpm;
    scoresMenu* sm;
    Database* db;
    TwisterMenu* tw;
    Data* dt;
private slots:
    void pushbackButton();
    void openMenuChoixParcours();
    void openTwister();
    void openScoresMenu();
};

