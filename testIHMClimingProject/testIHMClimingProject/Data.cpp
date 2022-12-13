#include "Data.h"

Data::Data()
{
	calibrate = false;
}

Data::~Data()
{
}

void Data::addPrise(QPointF* prise) {
	listPrise.append(prise);
}

void Data::addObserver(Observer* observer) {
	listObserver.append(observer);
}
void Data::removeObserver(Observer* observer) {
		listObserver.removeOne(observer);
}
void Data::notifyObserver() const {
	for (Observer* obs : listObserver) {
		obs->updateModel();
	}
}

void Data::calibragePrise(double x, double y) {
	double largeur = 947;
	double hauteur = 529;
	for (QPointF* prise : listPrise) {
		*prise = QPointF(prise->x() * x / largeur, prise->y() * y/ hauteur);
	}
}