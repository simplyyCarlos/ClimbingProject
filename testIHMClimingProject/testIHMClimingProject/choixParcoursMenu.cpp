#include "choixParcoursMenu.h"
#include "qmessagebox.h"

choixParcoursMenu::choixParcoursMenu(QWidget* _parent)
	: parent(_parent)
{
	ui.setupUi(this);

	db = db->getInstance();
	uc = uc->getInstance();
	spm = nullptr;
	QPixmap bkgnd(":/testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	this->setFixedSize(QSize(650, 400));

	ui.pushButton_Add->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(81,207,85); font-size : 20px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Delete->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(235,66,66); font-size : 20px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Valider->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 20px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Edition->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 20px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");
	ui.tableWidget_Parcours->setStyleSheet("QTableWidget { background : rgb(203,203,203) }");
	ui.pushButton_Scores->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");

	updateModel();
	connect(ui.pushButton_Back, &QPushButton::pressed, this, &choixParcoursMenu::pushbackButton);
	connect(ui.pushButton_Add, &QPushButton::pressed, this, &choixParcoursMenu::addButton);
	connect(ui.pushButton_Delete, &QPushButton::pressed, this, &choixParcoursMenu::deleteButton);
	connect(ui.pushButton_Scores, &QPushButton::pressed, this, &choixParcoursMenu::openScoreParcoursMenu);
	connect(ui.pushButton_Edition, &QPushButton::pressed, this, &choixParcoursMenu::openEditionMenu);
}

choixParcoursMenu::~choixParcoursMenu()
{
	delete spm;
}

void choixParcoursMenu::updateModel()
{
	ui.tableWidget_Parcours->clear();
	QVector<QVector<QString>> data = *db->getAllParcours();
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

void choixParcoursMenu::addButton()
{
	if (uc->getName() == "") {
		QMessageBox::warning(this, "Connexion", "Vous devez vous connecte !", QMessageBox::Ok);
	}
}

void choixParcoursMenu::deleteButton()
{
	if (uc->getName() == "") {
		QMessageBox::warning(this, "Connexion", "Vous devez vous connecte !", QMessageBox::Ok);
	}
	if (ui.tableWidget_Parcours->item(ui.tableWidget_Parcours->currentRow(), 0)) {
		QString tmp = ui.tableWidget_Parcours->item(ui.tableWidget_Parcours->currentRow(), 0)->text();
		(ControllerRemoveParcours().control(tmp.toInt()));
	}
}

void choixParcoursMenu::openScoreParcoursMenu()
{
	if (spm == nullptr) {
		spm = new scoresParcoursMenu(this);
	}
	this->close();
	spm->show();
}

void choixParcoursMenu::openEditionMenu()
{
	if (uc->getName() == "") {
		QMessageBox::warning(this, "Connexion", "Vous devez vous connecte !", QMessageBox::Ok);
	}
}

void choixParcoursMenu::pushbackButton() {
	this->close();
	parent->show();
}