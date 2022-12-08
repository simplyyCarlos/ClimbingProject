#pragma once
#include "ui_choixParcoursMenu.h"
#include "observer.h"
#include "Database.h"
class choixParcoursMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    choixParcoursMenu(QWidget* _parent,Database* _db);
    ~choixParcoursMenu();
    void update();
private:
    Ui::choixParcoursMenuClass ui;
    QWidget* parent;
    Database* db;
private slots:
    void pushbackButton();
};