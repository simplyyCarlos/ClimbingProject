#pragma once
#include "ui_Pong.h"
#include "dbmanager.h"
#include "scoresPongMenu.h"
/**
 * @brief Window of the main menu of the Pong game
*/
class PongMenu : public QWidget
{
	Q_OBJECT
public:
    /**
     * @brief Contructor of the class 
     * @param _parent window that create this window
    */
    PongMenu(QWidget* _parent);
    /**
     * @brief Destructor of the class 
    */
    ~PongMenu();

private:
    Ui::Pong_Class ui;
    QWidget* parent;
    DbManager* db;
    scoresPongMenu* spm;
private slots:
    /**
    * @brief Action when the button "back" is pressed that go back to the parent window
    */
    void pushbackButton();
    /**
     * @brief Action that open the Score menu of the pong game
    */
    void openScoresPong();
};

