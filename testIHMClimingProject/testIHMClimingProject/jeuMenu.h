#pragma once
#include "ui_jeuMenu.h"

class jeuMenu : public QWidget
{
    Q_OBJECT

public:
    jeuMenu(QWidget* parent);
    ~jeuMenu();

private:
    Ui::jeuMenuClass ui;
    QWidget* parent;
private slots:
    void pushbackButton();
};

