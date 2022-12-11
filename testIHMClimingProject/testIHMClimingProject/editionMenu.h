#pragma once
#include "ui_editionMenu.h"
#include "Database.h"
#include "AbstractController.h"
class editionMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    editionMenu(Database* _db, QWidget* _parent);
    ~editionMenu();
    void update();
private:
    Ui::editionMenuClass ui;
    QWidget* parent;
    Database* db;
private slots:
    void pushbackButton();
    void addButton();
    void deleteButton();
};

