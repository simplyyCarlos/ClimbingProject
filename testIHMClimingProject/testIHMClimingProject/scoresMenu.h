#pragma once
#include "ui_scoresMenu.h"
#include "Database.h"
#include "observer.h"
class scoresMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    scoresMenu(Database* _db, QWidget* _parent);
    ~scoresMenu();
    void update();
private:
    Ui::scoresMenuClass ui;
    QWidget* parent;
    Database* db;
private slots:
    void pushbackButton();
};

