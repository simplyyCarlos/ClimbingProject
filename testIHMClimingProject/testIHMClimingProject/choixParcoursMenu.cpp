#include "choixParcoursMenu.h"

choixParcoursMenu::choixParcoursMenu(QWidget* _parent, Database* _db)
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

	ui.pushButton_Valider->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(81,207,85); font-size : 20px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");
	ui.tableWidget_Parcours->setStyleSheet("QTableWidget { background : rgb(203,203,203) }");

	update();

	connect(ui.pushButton_Back, SIGNAL(clicked()), this, SLOT(pushbackButton()));
}

choixParcoursMenu::~choixParcoursMenu()
{
}

void choixParcoursMenu::update()
{
	ui.tableWidget_Parcours->clear();
	string tmp = "SELECT * FROM Parcours;";
	const char* query = tmp.c_str();
	db->setSql(query);
	db->callRc();
	db->testQuery();
	int row = 0;
	int col = 0;
	ui.tableWidget_Parcours->insertRow(ui.tableWidget_Parcours->rowCount());

	for (auto index : db->getResult()) {
		QTableWidgetItem* child = new QTableWidgetItem(index);
		ui.tableWidget_Parcours->setItem(row, col, child);
		col++;
		if (col % 4 == 0 && col != 0) {
			row++;
			ui.tableWidget_Parcours->insertRow(ui.tableWidget_Parcours->rowCount());
			col = 0;
		}
	}
	db->clearResult();
}

void choixParcoursMenu::pushbackButton() {
	this->close();
	parent->show();
}