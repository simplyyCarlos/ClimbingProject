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

void Data::calibragePrise(double _largeur, double _hauteur) {
	double largeur = 960 * 0.86f;
	double hauteur = 720 * 0.86f;
	std::vector<cv::Point2f> input;
	std::vector<cv::Point2f> output;
	for (QPointF* prise : listPrise) {
		double x = prise->x() / largeur;
		double y = prise->y() / hauteur;
		x = x * 1024;
		y = y * 576;
		input.push_back(cv::Point2f(x, y));
		/*double z = 1;
		x = matCali(0,0)* x + matCali(0, 1) * y + matCali(0, 2);
		y = matCali(1, 0) * x + matCali(1, 1) * y + matCali(1, 2);
		z = matCali(2, 0) * x + matCali(2, 1) * y + matCali(2, 2);
		x = x / z;
		y = y / z;

		*prise = QPointF(x, y);*/
	}
	perspectiveTransform(input, output, matCali);
	listPrise.clear();
	for (cv::Point2f point : output) {
		double x = point.x * _largeur / 1920;
		double y = point.y * _hauteur / 1080;
		listPrise.append(new QPointF(x, y));
	}
	listPrise.append(new QPointF(0, 0));
	listPrise.append(new QPointF(_largeur, _hauteur));

}

void Data::setMatrice(double tab[9]) {
	double mat[9];
	for (size_t i = 0; i < 9; i++)
	{
		mat[i] = tab[i];
	}
	matCali = cv::Mat(3, 3, CV_64FC1, &mat);
}