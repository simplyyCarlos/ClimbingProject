#pragma once
#include "ui_jeuMenu.h"
#include "choixParcoursMenu.h"
#include "dbmanager.h"
#include "PongMenu.h"
#include "twisterMenu.h"

/**
 * @brief Class that contains the game menu with the different possible game to play
*/
class jeuMenu : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of the class
     * @param _parent window that create this class 
     * @param dt data inported
    */
    jeuMenu(QWidget* _parent, Data* dt);
    /**
     * @brief destructor of the class
    */
    ~jeuMenu();

private:
    Ui::jeuMenuClass ui;
    QWidget* parent;
    choixParcoursMenu* cpm;
    PongMenu* pm;
    DbManager* db;
    TwisterMenu* tw;
    Data* dt;
private slots:
    /**
     * @brief Action when the button "back" is pressed that go back to the parent window
    */
    void pushbackButton();
    /**
     * @brief Action that open the window of parcours mode
    */
    void openMenuChoixParcours();
    /**
     * @brief Action that open the Twister game menu
    */
    void openTwister();
    void openReflex();
    /**
     * @brief Action that open the Pong menu
    */
    void openPongMenu();
};

