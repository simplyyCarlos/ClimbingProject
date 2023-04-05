#pragma once
#include "ui_paramMenu.h"
#include "calibrage.h"
#include "Data.h"
/**
 * @brief Main menue for all the parameter
*/
class paramMenu : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of the class
     * @param _parent window that create this class 
    */
    paramMenu(QWidget* _parent);
    /**
     * @brief Destructor of the class
    */
    ~paramMenu();
private:
    Ui::paramMenu ui;
    QWidget* parent;
    Calibrage* ca;
private slots:
    /**
     * @brief Action when the button "back" is pressed that go back to the parent window
    */
    void pushbackButton();
    /**
     * @brief 
    */
    void pushCalibre();
};
