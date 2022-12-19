#include "PongMenu.h"

PongMenu::PongMenu(QWidget* _parent)
	: parent(_parent)
{
	ui.setupUi(this);

	db = db->getInstance();
	spm = nullptr;

	QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	this->setFixedSize(QSize(650, 400));



	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 60px;}");
	ui.pushButton_Play->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 30px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Scores->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");

	connect(ui.pushButton_Back, &QPushButton::pressed, this, &PongMenu::pushbackButton);
	connect(ui.pushButton_Scores, &QPushButton::pressed, this, &PongMenu::openScoresPong);
}

PongMenu::~PongMenu()
{
}

void PongMenu::openScoresPong()
{
	if (spm == nullptr) {
		spm = new scoresPongMenu(this);
	}
	this->close();
	spm->show();
}

void PongMenu::pushbackButton() {
	this->close();
	parent->show();
}