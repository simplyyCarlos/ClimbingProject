#include "testIHMClimingProject.h"
#include <QtWidgets/QApplication>

#include "Parcours.h"
#include "Prises.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testIHMClimingProject w;
    w.show();
    return a.exec();
}
