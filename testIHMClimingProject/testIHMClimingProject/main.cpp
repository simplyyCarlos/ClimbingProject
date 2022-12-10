#include "testIHMClimingProject.h"
#include <QtWidgets/QApplication>

#include "Parcours.h"
#include "Prises.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    /*
    Database* db = new Database("climbingProject.db");
    string tmp = "SELECT * FROM Parcours;";
    const char* query = tmp.c_str();
    db->setSql(query);
    db->callRc();
    db->testQuery();
    QMapIterator<QString, QString> i(db->getResult());
    while (i.hasNext()) {
        i.next();
        std::cout << i.key().toStdString() << " " << i.value().toStdString() << std::endl;
    }
    db->closeDb();
    */

    
    Database* db = new Database("climbingProject.db");
    QApplication a(argc, argv);
    testIHMClimingProject w(db);
    w.show();

    delete db;
    return a.exec();
    
}
