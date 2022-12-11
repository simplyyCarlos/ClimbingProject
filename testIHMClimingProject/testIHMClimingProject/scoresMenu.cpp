#include "scoresMenu.h"

scoresMenu::scoresMenu(Database* _db, QWidget* _parent) : parent(_parent)
{
	ui.setupUi(this);

	db = _db;

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

	connect(ui.pushButton_Back, SIGNAL(clicked()), this, SLOT(pushbackButton()));
}

scoresMenu::~scoresMenu()
{

}

void scoresMenu::update()
{
	ui.tableWidget_Parcours->clear();
	string tmp = "SELECT j.pseudo,h.score ,p.Nom,h.date_jeu FROM Historique h,Joueurs j,Parcours p WHERE h.id_Joueur = j.id_Joueur and h.id_Parcours = p.id_Parcours ORDER BY h.score DESC;";
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

void scoresMenu::pushbackButton() {
	this->close();
	parent->show();
}
