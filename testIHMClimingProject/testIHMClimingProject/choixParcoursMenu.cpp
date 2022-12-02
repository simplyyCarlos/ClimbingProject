#include "choixParcoursMenu.h"

choixParcoursMenu::choixParcoursMenu(QWidget* _parent)
	: parent(_parent)
{
	ui.setupUi(this);

	QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	this->setFixedSize(QSize(650, 400));

	ui.pushButton_Valider->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(81,207,85); font-size : 20px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");
	ui.tableWidget_Parcours->setStyleSheet("QTableWidget { background : rgb(203,203,203) }");

	ui.tableWidget_Parcours->setRowCount(0);

	connect(ui.pushButton_Back, SIGNAL(clicked()), this, SLOT(pushbackButton()));
}

choixParcoursMenu::~choixParcoursMenu()
{
}

void choixParcoursMenu::pushbackButton() {
	this->close();
	parent->show();
}