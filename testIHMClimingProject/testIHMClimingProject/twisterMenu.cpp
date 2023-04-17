#include "twisterMenu.h"
#include "qmessagebox.h"

TwisterMenu::TwisterMenu(QWidget* _parent)
{
	ui.setupUi(this);
	uc = uc->getInstance();
	parent = _parent;
	tw = new Twister(this);
	rf = new Reflex(this);
	db = DbManager::getInstance();
	stm = nullptr;
	bTwister = true;
	QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

	ui.pushButton_Back->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Jouer->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 25px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.pushButton_Scores->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");
	ui.label_score->setStyleSheet("QLabel { color : white; font-size : 50px;}");
	ui.label_number->setStyleSheet("QLabel { color : white; font-size : 50px;}");
	ui.label_score->hide();
	ui.label_number->hide();

	connect(ui.pushButton_Jouer, &QPushButton::pressed, this, &TwisterMenu::openJeu);
	connect(ui.pushButton_Back, &QPushButton::pressed, this, &TwisterMenu::pushbackButton);
	connect(ui.pushButton_Scores, &QPushButton::pressed, this, &TwisterMenu::openScoresTwisterMenu);

	score = 0;
}

TwisterMenu::~TwisterMenu()
{
	delete tw, rf;
}

void TwisterMenu::openJeu() {
	if (uc->getName() == "") {
		QMessageBox::warning(this, "Connexion", "Vous devez vous connecte !", QMessageBox::Ok);
	}
	else {
		tw->showFullScreen();
		ui.label_score->show();
		ui.label_number->show();
		ui.pushButton_Jouer->hide();
		QApplication::processEvents();
		std::thread* jeu;
		if (bTwister) {
			jeu = new std::thread(&Twister::lancerJeu, tw);
		}
		else {
			jeu = new std::thread(&Reflex::lancerJeu, rf);
		}
		jeu->detach();
	}
}

void TwisterMenu::pushbackButton() {
	tw->setContinue();
	loose();
	this->close();
	tw->close();
	parent->show();
}

void TwisterMenu::addPoint() {
	score++;
	ui.label_number->setText(QString::number(score));
}

void TwisterMenu::loose() {
	(ControllerAddScore().control(score,"Twister"));
	score = 0;
	ui.label_number->setText(QString::number(score));
	ui.label_number->hide();
	ui.label_score->hide();
	ui.pushButton_Jouer->show();
}


void TwisterMenu::openScoresTwisterMenu()
{
	if (stm == nullptr) {
		stm = new scoresTwisterMenu(this);
	}
	this->close();
	stm->show();
}

void TwisterMenu::setBTwister(bool b) {
	bTwister = b;
	if (b) {
		ui.label_Titre->setText("Twister");
	}
	else {
		ui.label_Titre->setText("Reflex");
	}
	
}
