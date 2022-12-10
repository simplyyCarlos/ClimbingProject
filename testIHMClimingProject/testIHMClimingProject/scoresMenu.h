#pragma once
#include "ui_scoresMenu.h"
class scoresMenu : public QWidget
{
    Q_OBJECT

public:
    scoresMenu(QWidget* _parent);
    ~scoresMenu();

private:
    Ui::scoresMenuClass ui;
    QWidget* parent;
private slots:
    void pushbackButton();
};

