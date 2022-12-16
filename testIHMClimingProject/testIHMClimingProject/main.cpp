#include "testIHMClimingProject.h"
#include <QtWidgets/QApplication>

#include "Parcours.h"
#include "Prises.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    DbManager* db = db->getInstance();
    QApplication a(argc, argv);
    testIHMClimingProject w;
    w.show();

    return a.exec();
    
}
