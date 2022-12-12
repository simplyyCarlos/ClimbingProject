#pragma once
#include "ui_Pong.h"
class PongMenu : public QWidget
{
	Q_OBJECT
public:
    PongMenu(QWidget* _parent);
    ~PongMenu();

private:
    Ui::Pong_Class ui;
    QWidget* parent;
private slots:
    void pushbackButton();
};

