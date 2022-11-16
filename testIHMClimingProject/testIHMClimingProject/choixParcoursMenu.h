#pragma once
#include "ui_choixParcoursMenu.h"
class choixParcoursMenu : public QWidget
{
    Q_OBJECT

public:
    choixParcoursMenu(QWidget* _parent);
    ~choixParcoursMenu();

private:
    Ui::choixParcoursMenuClass ui;
    QWidget* parent;
private slots:
    void pushbackButton();
};