#pragma once
#include "ui_paramMenu.h"
#include "calibrage.h"
#include "Data.h"
class paramMenu : public QWidget
{
    Q_OBJECT

public:
    paramMenu(QWidget* _parent);
    ~paramMenu();
private:
    Ui::paramMenu ui;
    QWidget* parent;
    Calibrage* ca;
    Data* dt;
private slots:
    void pushbackButton();
    void pushCalibre();
};
