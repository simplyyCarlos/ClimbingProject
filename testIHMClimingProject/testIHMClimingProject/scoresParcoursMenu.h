#pragma once
#include "ui_scoresParcoursMenu.h"
#include "dbmanager.h"
#include "observer.h"
class scoresParcoursMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    scoresParcoursMenu(QWidget* _parent);
    ~scoresParcoursMenu();
    void update();
private:
    Ui::scoresParcoursMenuClass ui;
    QWidget* parent;
    DbManager* db;
private slots:
    void pushbackButton();
};

