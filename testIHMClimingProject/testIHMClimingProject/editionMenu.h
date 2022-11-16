#pragma once
#include "ui_editionMenu.h"
class editionMenu : public QWidget
{
    Q_OBJECT

public:
    editionMenu(QWidget* parent);
    ~editionMenu();

private:
    Ui::editionMenuClass ui;
    QWidget* parent;
private slots:
    void pushbackButton();
};

