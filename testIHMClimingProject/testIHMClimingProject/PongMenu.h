#pragma once
#include "ui_Pong.h"
#include "Database.h"
#include "scoresPongMenu.h"
class PongMenu : public QWidget
{
	Q_OBJECT
public:
    PongMenu(Database* _db,QWidget* _parent);
    ~PongMenu();

private:
    Ui::Pong_Class ui;
    QWidget* parent;
    Database* db;
    scoresPongMenu* spm;
private slots:
    void pushbackButton();
    void openScoresPong();
};

