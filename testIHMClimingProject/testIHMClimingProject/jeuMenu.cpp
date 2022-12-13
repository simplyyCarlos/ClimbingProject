#include "jeuMenu.h"

jeuMenu::jeuMenu(Database* _db,QWidget* _parent)
	: parent(_parent)
{
	ui.setupUi(this);
	db = _db;
	QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	this->setFixedSize(QSize(650, 400));

	cpm = nullptr,pm = nullptr;

	ui.pushButton_Twistter->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Parcours->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Pong->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Scores->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");
	ui.textBrowser_Parcours->setStyleSheet("QTextBrowser { background-color : rgb(170,105,139);}");
	ui.textBrowser_Pong->setStyleSheet("QTextBrowser { background-color : rgb(170,105,139);}");
	ui.textBrowser_Twistter->setStyleSheet("QTextBrowser { background-color : rgb(170,105,139);}");

	connect(ui.pushButton_Back, &QPushButton::pressed, this, &jeuMenu::pushbackButton);
	connect(ui.pushButton_Parcours, &QPushButton::pressed, this, &jeuMenu::openMenuChoixParcours);
	connect(ui.pushButton_Pong, &QPushButton::pressed, this, &jeuMenu::openPongMenu);
}

jeuMenu::~jeuMenu()
{
}

void jeuMenu::pushbackButton() {
	this->close();
	parent->show();
}

void jeuMenu::openMenuChoixParcours() {
	if (cpm == nullptr) {
		cpm = new choixParcoursMenu(this, db);
		db->addObserver(cpm);
	}
	this->close();
	cpm->show();
}

void jeuMenu::openPongMenu()
{
	if (pm == nullptr) {
		pm = new PongMenu(db,this);
	}
	this->close();
	pm->show();
}
