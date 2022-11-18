#pragma once
#include "ui_jeuMenu.h"
#include "choixParcoursMenu.h"
#include "scoresMenu.h"

class jeuMenu : public QWidget
{
    Q_OBJECT

public:
    jeuMenu(QWidget* _parent);
    ~jeuMenu();

private:
    Ui::jeuMenuClass ui;
    QWidget* parent;
    choixParcoursMenu* cpm;
    scoresMenu* sm;
private slots:
    void pushbackButton();
    void openMenuChoixParcours();
    void openScoresMenu();
};

