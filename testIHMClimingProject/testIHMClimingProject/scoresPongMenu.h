#pragma once
#include "ui_scoresPongMenu.h"
#include "dbmanager.h"
#include "observer.h"
#include "scoreUsrPong.h"

class scoresPongMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    scoresPongMenu(QWidget* _parent);
    ~scoresPongMenu();
    void updateModel();
private:
    Ui::scoresPongMenuClass ui;
    QWidget* parent;
    DbManager* db;
    UserConnected* uc;
    scoreUsrPong* sup;
private slots:
    void pushbackButton();
    void openPersoScore();
};
