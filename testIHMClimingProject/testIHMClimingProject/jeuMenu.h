#pragma once
#include "ui_jeuMenu.h"
#include "choixParcoursMenu.h"
#include "scoresMenu.h"
#include "Database.h"
#include "PongMenu.h";

class jeuMenu : public QWidget
{
    Q_OBJECT

public:
    jeuMenu(Database* _db,QWidget* _parent);
    ~jeuMenu();

private:
    Ui::jeuMenuClass ui;
    QWidget* parent;
    choixParcoursMenu* cpm;
    scoresMenu* sm;
    PongMenu* pm;
    Database* db;
private slots:
    void pushbackButton();
    void openMenuChoixParcours();
    void openScoresMenu();
    void openPongMenu();
};

