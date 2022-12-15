#pragma once
#include "ui_scoresPongMenu.h"
#include "dbmanager.h"
#include "observer.h"
class scoresPongMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    scoresPongMenu(DbManager* _db, QWidget* _parent);
    ~scoresPongMenu();
    void update();
private:
    Ui::scoresPongMenuClass ui;
    QWidget* parent;
    DbManager* db;
private slots:
    void pushbackButton();
};
