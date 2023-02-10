#pragma once
#include "ui_scoresPongMenu.h"
#include "dbmanager.h"
#include "observer.h"
#include "scoreUsrPong.h"
/**
 * @brief Window of the score menue for the Pong game
*/
class scoresPongMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of the class
     * @param _parent window that create this window
    */
    scoresPongMenu(QWidget* _parent);
    /**
     * @brief Desctructor of the class
    */
    ~scoresPongMenu();
    /**
     * @brief Method that update the view when there is change in the model inherit from Observer class
    */
    void updateModel();
private:
    Ui::scoresPongMenuClass ui;
    QWidget* parent;
    DbManager* db;
    UserConnected* uc;
    scoreUsrPong* sup;
private slots:
    /**
    * @brief Action when the button "back" is pressed that go back to the parent window
    */
    void pushbackButton();
    /**
     * @brief open the Score window for the user connected for the Pong mode
    */
    void openPersoScore();
};
