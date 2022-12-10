#include "testIHMClimingProject.h"

testIHMClimingProject::testIHMClimingProject(Database* _db,QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    db = new Database(_db);
    QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setFixedSize(QSize(650, 400));
    calibrate = false;

    ui.pushButton_Edition->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
    ui.pushButton_Jouer->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
    ui.pushButton_Connexion->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
    ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");
    ui.label_Created->setStyleSheet("QLabel { color : white;}");
    ui.label_Copyright->setStyleSheet("QLabel { color : white;}");

    connect(ui.pushButton_Connexion, SIGNAL(clicked()), this, SLOT(openConnexion()));
    connect(ui.pushButton_Jouer, SIGNAL(clicked()), this, SLOT(openMenuJeu()));
    connect(ui.pushButton_Edition, SIGNAL(clicked()), this, SLOT(openMenuEdition()));
}

testIHMClimingProject::~testIHMClimingProject()
{}

void testIHMClimingProject::openConnexion() {
    dialogLogin log = new dialogLogin(this);
    log.exec();
}

void testIHMClimingProject::openMenuJeu() {
    if (calibrate) {
        jm = new jeuMenu(db, this);
        this->close();
        jm->show();
    }
    else {
        ca = new Calibrage(this);
        this->close();
        ca->show();
    }
    
}

void testIHMClimingProject::openMenuEdition() {
    em = new editionMenu(this);
    this->close();
    em->show();
}