#include "dialogCreation.h"
#include "qmessagebox.h"


dialogCreation::dialogCreation(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
	db = db->getInstance();
	uc = uc->getInstance();
	connect(ui.pushButton, &QPushButton::pressed, this, &dialogCreation::validerCreation);
}

dialogCreation::~dialogCreation() {
}

void dialogCreation::validerCreation() {
	QString log = ui.lineEdit_login->text();
	QString mdp = ui.lineEdit_password->text();
	QString cMdp = ui.lineEdit_check->text();
	if (mdp != cMdp) {
		QMessageBox::warning(this, "Creation", "Veuillez rentrer les memes mot de passe dans les deux champs !", QMessageBox::Ok);
		return;
	}
	if (db->pseudoExists(log)) {
		QMessageBox::warning(this, "Creation", "Cette urilisateur existe déja !!", QMessageBox::Ok);
		return;
	}
	QMessageBox::information(this, "Creation", "Votre utilisateur a bien ete cree. Bienvenue " + log, QMessageBox::Ok);
	db->addJoueur(log, mdp);
	uc->setName(log);
	this->close();
}