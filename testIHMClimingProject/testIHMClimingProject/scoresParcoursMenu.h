#pragma once
#include "ui_scoresParcoursMenu.h"
#include "dbmanager.h"
#include "observer.h"
#include "scoresUsrParcours.h"
/**
 * @brief Window of the score menue for the parcours game
*/
class scoresParcoursMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of the class
     * @param _parent window that create this window
    */
    scoresParcoursMenu(QWidget* _parent);
    /**
     * @brief Desctructor of the class
    */
    ~scoresParcoursMenu();
    /**
     * @brief Method that update the view when there is change in the model inherit from Observer class
    */
    void updateModel();
private:
    Ui::scoresParcoursMenuClass ui;
    QWidget* parent;
    DbManager* db;
    UserConnected* uc;
    scoresUsrParcours* sup;
private slots:
    /**
    * @brief Action when the button "back" is pressed that go back to the parent window
    */
    void pushbackButton();
    /**
     * @brief open the Score window for the user connected for the parcours mode
    */
    void openPersoScore();
};

