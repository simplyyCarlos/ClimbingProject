#include "jeuMenu.h"

jeuMenu::jeuMenu(QWidget* _parent)
	: parent(_parent)
{
	ui.setupUi(this);
	db = db->getInstance();
	QPixmap bkgnd(":/testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	this->setFixedSize(QSize(650, 400));
	tw = nullptr;

	ui.pushButton_Twistter->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Reflex->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");
	ui.textBrowser_Reflex->setStyleSheet("QTextBrowser { background-color : rgb(170,105,139);}");
	ui.textBrowser_Twistter->setStyleSheet("QTextBrowser { background-color : rgb(170,105,139);}");


	connect(ui.pushButton_Twistter, &QPushButton::pressed, this, &jeuMenu::openTwister);
	connect(ui.pushButton_Back, &QPushButton::pressed, this, &jeuMenu::pushbackButton);
	connect(ui.pushButton_Reflex, &QPushButton::pressed, this, &jeuMenu::openReflex);
}

jeuMenu::~jeuMenu()
{
	delete tw;
}

void jeuMenu::pushbackButton() {
	this->close();
	parent->show();
}

void jeuMenu::openTwister() {
	if (tw == nullptr) {
		tw = new TwisterMenu(this);
	}
	this->close();
	tw->setBTwister(true);
	tw->show();
}

void jeuMenu::openReflex() {
	if (tw == nullptr) {
		tw = new TwisterMenu(this);
	}
	this->close();
	tw->setBTwister(false);
	tw->show();
}


