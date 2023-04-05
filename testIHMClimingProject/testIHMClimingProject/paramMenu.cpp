#include "paramMenu.h"
paramMenu::paramMenu(QWidget* _parent)
	: parent(_parent)
{
	ui.setupUi(this);

	ca = nullptr;

	QPixmap bkgnd(":/testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	this->setFixedSize(QSize(650, 400));


	ui.pushButton_Calibrage->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Wait->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");

	connect(ui.pushButton_Back, &QPushButton::pressed, this, &paramMenu::pushbackButton);
	connect(ui.pushButton_Calibrage, &QPushButton::pressed, this, &paramMenu::pushCalibre);
}

paramMenu::~paramMenu()
{
	delete ca;
}

void paramMenu::pushCalibre()
{
	if (ca == nullptr) {
		ca = new Calibrage(this);
	}
	this->close();
	ca->show();
	QApplication::processEvents();
	ca->calibrage();
}

void paramMenu::pushbackButton() {
	this->close();
	parent->show();
}