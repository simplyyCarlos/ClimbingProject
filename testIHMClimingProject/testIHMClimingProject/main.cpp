#include "testIHMClimingProject.h"
#include <QtWidgets/QApplication>

#include "dialogLogin.h"
#include <iostream>

using namespace std;

/**
 * @brief main function
 * @param argc stores number of command-line arguments passed by the user
 * @param argv array of character pointers listing all the arguments
 * @return the execution of the window 
*/
int main(int argc, char *argv[])
{
    
    py::scoped_interpreter python;
    py::gil_scoped_release release;
    UserConnected* uc = uc ->getInstance();
    QApplication a(argc, argv);
    DbManager* db = db->getInstance();
    testIHMClimingProject w;
    w.show();

    return a.exec();
    
}
