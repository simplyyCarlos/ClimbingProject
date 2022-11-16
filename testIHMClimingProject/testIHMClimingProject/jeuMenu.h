#pragma once
#include "ui_jeuMenu.h"
#include "choixParcoursMenu.h"

class jeuMenu : public QWidget
{
    Q_OBJECT

public:
    jeuMenu(QWidget* parent);
    ~jeuMenu();

private:
    Ui::jeuMenuClass ui;
    QWidget* parent;
    choixParcoursMenu* cpm;
private slots:
    void pushbackButton();
    void openMenuChoixParcours();
};

