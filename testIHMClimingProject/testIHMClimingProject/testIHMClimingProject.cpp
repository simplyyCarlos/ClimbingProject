#include "testIHMClimingProject.h"

testIHMClimingProject::testIHMClimingProject(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setFixedSize(QSize(650, 400));

    ui.pushButton_Edition->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
    ui.pushButton_Jouer->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
    ui.pushButton_Connexion->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
    ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");
    connect(ui.pushButton_Connexion, SIGNAL(openConnexion()), this, SLOT(openConnexion()));
}

testIHMClimingProject::~testIHMClimingProject()
{}

void testIHMClimingProject::openConnexion() {

}