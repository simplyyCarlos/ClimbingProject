#pragma once
#include "ui_choixParcoursMenu.h"
#include "observer.h"
#include "dbmanager.h"
#include "AbstractController.h"
#include "scoresParcoursMenu.h"
#include "UserConnected.h"
class choixParcoursMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    choixParcoursMenu(QWidget* _parent);
    ~choixParcoursMenu();
    void updateModel();
private:
    Ui::choixParcoursMenuClass ui;
    QWidget* parent;
    
    DbManager* db;
    UserConnected* uc;
    scoresParcoursMenu* spm;
private slots:
    void pushbackButton();
    void addButton();
    void deleteButton();
    void openScoreParcoursMenu();
};