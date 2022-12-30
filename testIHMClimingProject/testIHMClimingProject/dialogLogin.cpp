#include "dialogLogin.h"
#include "qmessagebox.h"

dialogLogin::dialogLogin(QWidget* parent) : QDialog(parent) {
	ui.setupUi(this);
	db = db->getInstance();

	connect(ui.pushButton, &QPushButton::pressed, this, &dialogLogin::validerConnexion);
}

dialogLogin::~dialogLogin() {

}

void dialogLogin::validerConnexion() {
	QString log = ui.lineEdit_login->text();
	QString mdp = ui.lineEdit_password->text();
	if (db->getLogin(log, mdp)) {
		QMessageBox::information(this, "Connexion", "Vous etes connecte. Bienvenue " + log, QMessageBox::Ok);
		this->close();
	}
	else {
		QMessageBox::warning(this, "Connexion", "Utilisateurs ou mot de passe incorrects", QMessageBox::Ok);
	}
}
