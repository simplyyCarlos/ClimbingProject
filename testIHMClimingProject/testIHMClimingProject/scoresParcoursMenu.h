#pragma once
#include "ui_scoresParcoursMenu.h"
#include "dbmanager.h"
#include "observer.h"
#include "scoresUsrParcours.h"

class scoresParcoursMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    scoresParcoursMenu(QWidget* _parent);
    ~scoresParcoursMenu();
    void updateModel();
private:
    Ui::scoresParcoursMenuClass ui;
    QWidget* parent;
    DbManager* db;
    UserConnected* uc;
    scoresUsrParcours* sup;
private slots:
    void pushbackButton();
    void openPersoScore();
};

