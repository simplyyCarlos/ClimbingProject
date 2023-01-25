#include "scoresUsrTwister.h"

scoresUsrTwister::scoresUsrTwister(QWidget* _parent) : parent(_parent)
{
	ui.setupUi(this);

	db = db->getInstance();

	QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	this->setFixedSize(QSize(650, 400));

	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.tableWidget_Parcours->setStyleSheet("QTableWidget { background : rgb(203,203,203) }");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");

	updateModel();

	connect(ui.pushButton_Back, &QPushButton::pressed, this, &scoresUsrTwister::pushbackButton);
}

scoresUsrTwister::~scoresUsrTwister()
{
}

void scoresUsrTwister::updateModel()
{
	ui.tableWidget_Parcours->clear();
	QVector<QVector<QString>> data = *db->getUsrScoresTwister();
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

void scoresUsrTwister::pushbackButton() {
	this->close();
	parent->show();
}