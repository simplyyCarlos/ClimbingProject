#pragma once
#include "ui_scoresTwisterMenu.h"
#include "dbmanager.h"
#include "observer.h"
#include "scoresUsrTwister.h"
/**
 * @brief Window of the score menue for the Twister game
*/
class scoresTwisterMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of the class
     * @param _parent window that create this window
    */
    scoresTwisterMenu(QWidget* _parent);
    /**
     * @brief Desctructor of the class
    */
    ~scoresTwisterMenu();
    /**
     * @brief Method that update the view when there is change in the model inherit from Observer class
    */
    void updateModel();
private:
    Ui::ScoresTwisterMenuClass ui;
    QWidget* parent;
    DbManager* db;
    UserConnected* uc;
    scoresUsrTwister* sup;
private slots:
    /**
    * @brief Action when the button "back" is pressed that go back to the parent window
    */
    void pushbackButton();
    /**
     * @brief open the Score window for the user connected for the Twister mode
    */
    void openPersoScore();
};
