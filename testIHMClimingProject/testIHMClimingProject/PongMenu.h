#pragma once
#include "ui_Pong.h"
#include "dbmanager.h"
#include "scoresPongMenu.h"
class PongMenu : public QWidget
{
	Q_OBJECT
public:
    PongMenu(QWidget* _parent);
    ~PongMenu();

private:
    Ui::Pong_Class ui;
    QWidget* parent;
    DbManager* db;
    scoresPongMenu* spm;
private slots:
    void pushbackButton();
    void openScoresPong();
};

