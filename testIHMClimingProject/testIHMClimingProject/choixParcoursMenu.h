#pragma once
#include "ui_choixParcoursMenu.h"
#include "observer.h"
#include "dbmanager.h"
#include "AbstractController.h"
#include "scoresParcoursMenu.h"
#include "UserConnected.h"
/**
 * @brief Window list all the parcours and the actions possible with it 
*/
class choixParcoursMenu : public QWidget, public Observer
{
    Q_OBJECT

public:
    /**
     * @brief constructor of the class that create the window
     * @param _parent window that create this window
    */
    choixParcoursMenu(QWidget* _parent);
    /**
     * @brief Destructor of the class
    */
    ~choixParcoursMenu();
    /**
     * @brief Method that update the view when there is change in the model inherit from Observer class
    */
    void updateModel();
private:
    Ui::choixParcoursMenuClass ui;
    QWidget* parent;
    
    DbManager* db;
    UserConnected* uc;
    scoresParcoursMenu* spm;
private slots:
    /**
     * @brief Action when the button "back" is pressed that go back to the parent window 
    */
    void pushbackButton();
    /**
     * @brief Action when "add" button is pressed it will add a parcours to the list
    */
    void addButton();
    /**
     * @brief Action when "Delete" button is pressed, it will delete the selected parcours in the list 
    */
    void deleteButton();
    /**
     * @brief Action when "Score" button is pressed, it will open the score window of the parcours mode
    */
    void openScoreParcoursMenu();
    /**
     * @brief Action when "Edition" is pressed, it will open the edition menu
    */
    void openEditionMenu();
};