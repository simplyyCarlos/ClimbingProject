#include "testIHMClimingProject.h"
#include <QtWidgets/QApplication>

#include "Parcours.h"
#include "Prises.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Database db = new Database("climbingProject.db");
    QApplication a(argc, argv);
    testIHMClimingProject w(&db);
    w.show();

    return a.exec();
    
}
