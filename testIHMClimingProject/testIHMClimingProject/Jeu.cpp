#include "Jeu.h"
#include "twisterMenu.h"

#define rayonCercle 80.0f
#define rayonCercleMain 35.0f


void Jeu::lancerJeu() {

	windows_shared_memory shmem(open_or_create, "positionMain", read_write, sizeof(float[16]));
	mapped_region region(shmem, read_write);
	tabMain = static_cast<float*>(region.get_address());


	std::thread detectMain;
	std::thread jeu(&Jeu::algorithmeJeu, this);
	std::ofstream Continue;
	while (!Continue.is_open()) {
		try
		{
			Continue = std::ofstream("ContinueMediapipe.txt");
		}
		catch (const std::exception&)
		{
			continue;
		}
	}
	Continue << "1";
	Continue.close();

	detectMain = std::thread(&Jeu::detectionMain, this);

	jeu.join();

	while (!Continue.is_open()) {
		try
		{
			Continue = std::ofstream("ContinueMediapipe.txt");
		}
		catch (const std::exception&)
		{
			continue;
		}
	}
	Continue << "0";
	Continue.close();
	detectMain.detach();
	tabMain = nullptr;
}


void Jeu::detectionMain() {
	py::gil_scoped_acquire acquire;
	try
	{
		auto mediapipe = py::module::import("detectionMain");
		auto main_mediapipe = mediapipe.attr("main");
		main_mediapipe();
	}
	catch (const std::exception&)
	{
		return;
	}
	py::gil_scoped_release release;
}


void Jeu::caliPosMain(QPointF& center1, QPointF& center2) {
	std::vector<cv::Point2f> input;
	std::vector<cv::Point2f> output;

	double x = center1.x() * 1024;
	double y = center1.y() * 576;
	input.push_back(cv::Point2f(x, y));
	double x2 = center2.x() * 1024;
	double y2 = center2.y() * 576;
	input.push_back(cv::Point2f(x2, y2));

	perspectiveTransform(input, output, dt->getMatrice());

	double X = output.at(0).x * largeur / 1920;
	double Y = output.at(0).y * hauteur / 1080;
	center1 = QPointF(X, Y);
	double X2 = output.at(1).x * largeur / 1920;
	double Y2 = output.at(1).y * hauteur / 1080;
	center2 = QPointF(X2, Y2);
}


void Jeu::setContinue() {
	continueThread = false;
}

Jeu::~Jeu() {
	delete tabMain;
}
