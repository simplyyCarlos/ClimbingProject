#include "Data.h"

Data::Data()
{
	calibrate = false;
}

Data::~Data()
{
}

void Data::setPrise(QVector<Circle*> prise) {
	listPrise = prise;
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

void Data::calibragePrise() {

}