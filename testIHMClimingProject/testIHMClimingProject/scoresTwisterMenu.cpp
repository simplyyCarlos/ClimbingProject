#include "scoresTwisterMenu.h"
#include "qmessagebox.h"

scoresTwisterMenu::scoresTwisterMenu(QWidget* _parent) : parent(_parent)
{
	ui.setupUi(this);

	db = db->getInstance();
	uc = uc->getInstance();
	sup = nullptr;

	QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	this->setFixedSize(QSize(650, 400));

	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Perso->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.tableWidget_Parcours->setStyleSheet("QTableWidget { background : rgb(203,203,203) }");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");

	updateModel();

	connect(ui.pushButton_Back, &QPushButton::pressed, this, &scoresTwisterMenu::pushbackButton);
	connect(ui.pushButton_Perso, &QPushButton::pressed, this, &scoresTwisterMenu::openPersoScore);
}

scoresTwisterMenu::~scoresTwisterMenu()
{
}

void scoresTwisterMenu::updateModel()
{
	ui.tableWidget_Parcours->clear();
	QVector<QVector<QString>> data = *db->getScoresTwister();
	int row = 0;
	int col = 0;
	for (auto index : data) {
		ui.tableWidget_Parcours->insertRow(ui.tableWidget_Parcours->rowCount());
		for (auto _index : index) {
			QTableWidgetItem* child = new QTableWidgetItem();
			child->setText(_index);
			ui.tableWidget_Parcours->setItem(row, col, child);
			col++;
		}
		row++;
		col = 0;
	}
}

void scoresTwisterMenu::openPersoScore()
{
	if (uc->getName() == "") {
		QMessageBox::warning(this, "Connexion", "Vous devez vous connecte !", QMessageBox::Ok);
	}
	else {
		if (sup == nullptr) {
			sup = new scoresUsrTwister(this);
			db->addObserver(sup);
		}
		this->close();
		sup->show();
	}
}

void scoresTwisterMenu::pushbackButton() {
	this->close();
	parent->show();
}