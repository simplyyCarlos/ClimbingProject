#pragma once
#include "ui_scoresPongMenu.h"
#include "Database.h"
#include "observer.h"
class scoresPongMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    scoresPongMenu(Database* _db, QWidget* _parent);
    ~scoresPongMenu();
    void update();
private:
    Ui::scoresPongMenuClass ui;
    QWidget* parent;
    Database* db;
private slots:
    void pushbackButton();
};
