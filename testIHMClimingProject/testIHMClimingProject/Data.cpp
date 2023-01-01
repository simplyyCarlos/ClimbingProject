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

void Data::calibragePrise(double _largeur, double _hauteur) {
	double largeur = 1024;
	double hauteur = 576;
	std::vector<cv::Point2f> input;
	std::vector<cv::Point2f> output;
	for (QPointF* prise : listPrise) {
		double x = prise->x() / largeur;
		double y = prise->y() / hauteur;
		x = x * 1024;
		y = y * 576;
		input.push_back(cv::Point2f(x, y));
	}
	if (input.size() > 0) {
		perspectiveTransform(input, output, matCali);
	}
	listPrise.clear();
	for (cv::Point2f point : output) {
		double x = point.x * _largeur / 1920;
		double y = point.y * _hauteur / 1080;
		listPrise.append(new QPointF(x, y));
	}

}

void Data::setMatrice(double tab[9]) {
	double mat[9];
	for (size_t i = 0; i < 9; i++)
	{
		mat[i] = tab[i];
	}
	matCali = cv::Mat(3, 3, CV_64FC1, &mat);
}