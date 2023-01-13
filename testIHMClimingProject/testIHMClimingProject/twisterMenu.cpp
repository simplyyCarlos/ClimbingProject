#include "twisterMenu.h"


TwisterMenu::TwisterMenu(QWidget* _parent, Data* _dt)
{
	ui.setupUi(this);
	parent = _parent;
	dt = _dt;
	tw = new Twister(this, dt);
	stm = nullptr;
	QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Jouer->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Scores->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");


	connect(ui.pushButton_Jouer, &QPushButton::pressed, this, &TwisterMenu::openJeu);
	connect(ui.pushButton_Back, &QPushButton::pressed, this, &TwisterMenu::pushbackButton);
	connect(ui.pushButton_Scores, &QPushButton::pressed, this, &TwisterMenu::openScoresTwisterMenu);
}

TwisterMenu::~TwisterMenu()
{
}

void TwisterMenu::openJeu() {
	tw->showFullScreen();
	QApplication::processEvents();
	std::thread jeu(&Twister::lancerJeu,tw);
	jeu.detach();

}

void TwisterMenu::pushbackButton() {
	this->close();
	tw->close();
	parent->show();
}

void TwisterMenu::openScoresTwisterMenu()
{
	if (stm == nullptr) {
		stm = new scoresTwisterMenu(this);
	}
	this->close();
	stm->show();
}
