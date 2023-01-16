#include "testIHMClimingProject.h"
#include <QtWidgets/QApplication>

#include "Parcours.h"
#include "Prises.h"
#include "dialogLogin.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    
    py::scoped_interpreter python;
    py::gil_scoped_release release;
    DbManager* db = db->getInstance();
    UserConnected* uc = uc->getInstance();
    QApplication a(argc, argv);
    testIHMClimingProject w;
    w.show();

    return a.exec();
    
}
