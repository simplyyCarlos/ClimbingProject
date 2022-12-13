#pragma once
#include "ui_scoresMenu.h"
#include "Database.h"
#include "observer.h"
class scoresParcoursMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    scoresParcoursMenu(Database* _db, QWidget* _parent);
    ~scoresParcoursMenu();
    void update();
private:
    Ui::scoresParcoursMenuClass ui;
    QWidget* parent;
    Database* db;
private slots:
    void pushbackButton();
};

