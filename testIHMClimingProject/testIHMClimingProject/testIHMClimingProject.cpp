#include "testIHMClimingProject.h"

testIHMClimingProject::testIHMClimingProject(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    db = db->getInstance();
    QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setFixedSize(QSize(650, 400));
    jm = nullptr, pm = nullptr;
    log = new dialogLogin(this);

    ui.pushButton_Param->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
    ui.pushButton_Jouer->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
    ui.pushButton_Connexion->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
    ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");
    ui.label_Created->setStyleSheet("QLabel { color : white;}");
    ui.label_Copyright->setStyleSheet("QLabel { color : white;}");

    connect(ui.pushButton_Connexion, &QPushButton::pressed, this, &testIHMClimingProject::openConnexion);
    connect(ui.pushButton_Jouer, &QPushButton::pressed, this, &testIHMClimingProject::openMenuJeu);
    connect(ui.pushButton_Param, &QPushButton::pressed, this, &testIHMClimingProject::openMenuEdition);
}

testIHMClimingProject::~testIHMClimingProject()
{}

void testIHMClimingProject::openConnexion() {
    log->exec();
}

void testIHMClimingProject::openMenuJeu() {
    if (dt->getCalibrate()) {
        if (jm == nullptr) {
            jm = new jeuMenu(db, this, dt);
        }
        this->close();
        jm->show();
    }
    else {
        if (ca == nullptr) {
            ca = new Calibrage(this, dt);
        }
        this->close();
        ca->show();
        QApplication::processEvents();
        ca->calibrage();
    }   
}

void testIHMClimingProject::openMenuEdition() {
    if (pm == nullptr) {
        pm = new paramMenu(this);
    }
    this->close();
    pm->show();
}