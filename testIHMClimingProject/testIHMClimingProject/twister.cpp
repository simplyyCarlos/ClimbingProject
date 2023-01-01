#include "twister.h"

#define rayonCercle 30.0f

Twister::Twister(QWidget* _parent, Data* _dt)
{
	ui.setupUi(this);
	parent = _parent;
	dt = _dt;
	detect = false;
	tabMain = nullptr;

	QRect screen;

	if (qGuiApp->screens().size() > 1) {
		screen = qGuiApp->screens()[1]->geometry();
		largeur = screen.width();
		hauteur = screen.height();
		this->move(QPoint(screen.x(), screen.y()));
		this->resize(largeur, hauteur);
	}
	else {
		screen = qGuiApp->screens()[0]->geometry();
		largeur = screen.width();
		hauteur = screen.height();
		this->move(QPoint(screen.x(), screen.y()));
		this->resize(largeur, hauteur);
	}
	prise = dt->getPrise();
	srand(time(NULL));
	ui.setupUi(this);

	update();
}

Twister::~Twister()
{
}

void Twister::paintEvent(QPaintEvent*) {
	QPainter painter(this);

	QBrush tmpBrush(Qt::SolidPattern);
	tmpBrush.setColor(QColor(6, 129, 253));
	QPen tmpPen;
	tmpPen.setColor(Qt::black);
	tmpPen.setWidth(1);
	painter.setPen(tmpPen);
	painter.setBrush(tmpBrush);

	QPointF* pos;
	for (QPointF* pos : prise) {
		painter.drawEllipse(pos->x() - rayonCercle / 2, pos->y() - rayonCercle / 2, rayonCercle, rayonCercle);
	}

	tmpBrush.setColor(QColor(245, 20, 20));
	painter.setBrush(tmpBrush);

	for (QPointF* pos : listObjectif) {
		painter.drawEllipse(pos->x() - rayonCercle / 2, pos->y() - rayonCercle / 2, rayonCercle, rayonCercle);
	}

	tmpBrush.setColor(QColor(20, 245, 20));
	painter.setBrush(tmpBrush);

	for (QPointF* pos : listTouche) {
		painter.drawEllipse(pos->x() - rayonCercle / 2, pos->y() - rayonCercle / 2, rayonCercle, rayonCercle);
	}
	QPolygonF* poly = new QPolygonF(), *poly2 = new QPolygonF();
	if (tabMain != nullptr) {
		for (size_t i = 0; i < 8; i++)
		{
			if (i % 2 == 0) {
				poly->append(QPointF(tabMain[i * 2], tabMain[i * 2 + 1]));
			}
			else {
				poly2->append(QPointF(tabMain[i * 2], tabMain[i * 2 + 1]));
			}
			
		}
		caliPosMain(poly, poly2);
		painter.drawPolygon(*poly);
		painter.drawPolygon(*poly2);
	}
	

}

void Twister::lancerJeu() {


	windows_shared_memory shmem(open_or_create, "positionMain", read_write, sizeof(float[16]));
	mapped_region region(shmem, read_write);
	tabMain = static_cast<float*>(region.get_address());

	std::thread detectMain;
	std::thread jeu(&Twister::algorithmeJeu, this);
	if (!detect) {
		detectMain = std::thread(&Twister::detectionMain, this);
		detect = true;
	}
	
	jeu.join();
	detectMain.detach();

}

void Twister::detectionMain() {
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

void Twister::algorithmeJeu() {
	QPolygonF* poly = new QPolygonF(), * poly2 = new QPolygonF();
	int x = 0, timer = 50, speed = 30;
	while(true) {
		poly->clear();
		poly2->clear();
		for (size_t i = 0; i < 8; i++)
		{
			if (i % 2 == 0) {
				poly->append(QPointF(tabMain[i * 2], tabMain[i * 2 + 1]));
			}
			else {
				poly2->append(QPointF(tabMain[i * 2], tabMain[i * 2 + 1]));
			}

		}
		caliPosMain(poly, poly2);
		for (QPointF* point : listObjectif) {
			if (poly->containsPoint(*point, Qt::OddEvenFill) || poly2->containsPoint(*point, Qt::OddEvenFill)) {
				listTouche.append(point);
				listObjectif.removeOne(point);
			}
		}
		if (x == speed * 100 / timer) {
			x = 0;
			if (!listTouche.isEmpty()) {
				for (QPointF* tmp : listTouche) {
					listTouche.removeOne(tmp);
					prise.append(tmp);
				}	
			}
			if (!prise.isEmpty()) {
				QPointF* tmp = prise.at(rand() % prise.size());
				listObjectif.append(tmp);
				prise.removeOne(tmp);
			}
			
			/*if (listObjectif.size() > 2) {
				break;
			}*/

		}
		x++;
		update();
		Sleep(timer);
	}

}

void Twister::caliPosMain(QPolygonF* poly, QPolygonF* poly2) {
	std::vector<cv::Point2f> input;
	std::vector<cv::Point2f> output;
	for (size_t i = 0; i < 4; i++)
	{
		double x = poly->at(i).x() * 1024;
		double y = poly->at(i).y() * 576;
		input.push_back(cv::Point2f(x, y));
	}
	for (size_t i = 0; i < 4; i++)
	{
		double x = poly2->at(i).x() * 1024;
		double y = poly2->at(i).y() * 576;
		input.push_back(cv::Point2f(x, y));
	}
	perspectiveTransform(input, output, dt->getMatrice());
	poly->clear();
	poly2->clear();
	for (size_t i = 0; i < 4; i++)
	{
		double x = output.at(i).x * largeur / 1920;
		double y = output.at(i).y * hauteur / 1080;
		poly->append(QPointF(x, y));
	}
	for (size_t i = 4; i < 8; i++)
	{
		double x = output.at(i).x * largeur / 1920;
		double y = output.at(i).y * hauteur / 1080;
		poly2->append(QPointF(x, y));
	}
	/*poly->append(poly->at(2));
	poly->removeAt(2);
	poly2->append(poly->at(2));
	poly2->removeAt(2);*/
}


