#pragma once
#include "ui_scoresTwisterMenu.h"
#include "dbmanager.h"
#include "observer.h"
#include "scoresUsrTwister.h"

class scoresTwisterMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    scoresTwisterMenu(QWidget* _parent);
    ~scoresTwisterMenu();
    void updateModel();
private:
    Ui::ScoresTwisterMenuClass ui;
    QWidget* parent;
    DbManager* db;
    UserConnected* uc;
    scoresUsrTwister* sup;
private slots:
    void pushbackButton();
    void openPersoScore();
};
