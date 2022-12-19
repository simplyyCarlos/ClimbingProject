#include "scoresPongMenu.h"
scoresPongMenu::scoresPongMenu(QWidget* _parent) : parent(_parent)
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

	update();

	connect(ui.pushButton_Back, &QPushButton::pressed, this, &scoresPongMenu::pushbackButton);
}

scoresPongMenu::~scoresPongMenu()
{

}

void scoresPongMenu::update()
{
	QVector<QVector<QString>> data = *db->getScoresParcours();
	int row = 0;
	int col = 0;
	int i = 0;
	for (auto index : data) {
		QTableWidgetItem* child = new QTableWidgetItem(index.at(i));
		ui.tableWidget_Parcours->setItem(row, col, child);
		col++;
		if (col % 4 == 0 && col != 0) {
			row++;
			ui.tableWidget_Parcours->insertRow(ui.tableWidget_Parcours->rowCount());
			col = 0;
		}
		i++;
	}
}

void scoresPongMenu::pushbackButton() {
	this->close();
	parent->show();
}
