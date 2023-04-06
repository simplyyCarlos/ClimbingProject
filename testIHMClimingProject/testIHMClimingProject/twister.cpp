#include "Twister.h"
#include "twisterMenu.h"

#define rayonCercle 80.0f
#define rayonCercleMain 35.0f

Twister::Twister(TwisterMenu* _parent)
{
	ui.setupUi(this);
	parent = _parent;
	dt = Data::getInstance();
	tabMain = nullptr;
	QRect screen;
	handColor[0] = grey;
	handColor[1] = grey;
	continueThread = false;

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

	listColor << 0 << 1 << 2 << 3;

	for (QPointF* point : dt->getPrise()) {
		if (listColor.size() == 0) {
			listColor << 0 << 1 << 2 << 3;
		}
		int color = listColor.takeAt(rand() % listColor.size());
		priseList.append(new Prise(point, color));
	}

	listColor.clear();
	listColor << 0 << 1 << 2 << 3;

	ui.label_Over->hide();
	srand(time(NULL));
	ui.setupUi(this);

	update();
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


	for (Prise* pr : priseList) {
		QPointF* pos = pr->getPrise();
		tmpBrush.setColor(pr->getColor());
		painter.setBrush(tmpBrush);
		painter.drawEllipse(pos->x() - rayonCercle / 2, pos->y() - rayonCercle / 2, rayonCercle, rayonCercle);
	}


	QPolygonF* poly = new QPolygonF(), * poly2 = new QPolygonF();
	if (tabMain != nullptr) {
		for (size_t i = 0; i < 6; i++)
		{
			if (i % 2 == 0) {
				poly->append(QPointF(tabMain[i * 2], tabMain[i * 2 + 1]));
			}
			else {
				poly2->append(QPointF(tabMain[i * 2], tabMain[i * 2 + 1]));
			}

		}
		QPointF point1((poly->at(1).x() + poly->at(2).x()) / 2, (poly->at(1).y() + poly->at(2).y()) / 2);
		QPointF point2((poly2->at(1).x() + poly2->at(2).x()) / 2, (poly2->at(1).y() + poly2->at(2).y()) / 2);
		QPointF center1(2 * point1.x() - poly->at(0).x(), 2 * point1.y() - poly->at(0).y());
		QPointF center2(2 * point2.x() - poly2->at(0).x(), 2 * point2.y() - poly2->at(0).y());

		caliPosMain(center1, center2);
		

		tmpBrush.setColor(handColor[0]);
		painter.setBrush(tmpBrush);
		painter.drawEllipse(center1, rayonCercleMain, rayonCercleMain);
		tmpBrush.setColor(handColor[1]);
		painter.setBrush(tmpBrush);
		painter.drawEllipse(center2, rayonCercleMain, rayonCercleMain);
	}


}


void Twister::algorithmeJeu() {
	ui.label_Over->hide();
	continueThread = true;
	QPolygonF* poly = new QPolygonF(), * poly2 = new QPolygonF();
	int x = 0, timer = 50, speed = 40;
	int size = priseList.size();
	while(continueThread) {
		poly->clear();
		poly2->clear();
		for (size_t i = 0; i < 6; i++)
		{
			if (i % 2 == 0) {
				poly->append(QPointF(tabMain[i * 2], tabMain[i * 2 + 1]));
			}
			else {
				poly2->append(QPointF(tabMain[i * 2], tabMain[i * 2 + 1]));
			}

		}
		QPointF point1((poly->at(1).x() + poly->at(2).x()) / 2, (poly->at(1).y() + poly->at(2).y()) / 2);
		QPointF point2((poly2->at(1).x() + poly2->at(2).x()) / 2, (poly2->at(1).y() + poly2->at(2).y()) / 2);
		QPointF center1(2 * point1.x() - poly->at(0).x(), 2 * point1.y() - poly->at(0).y());
		QPointF center2(2 * point2.x() - poly2->at(0).x(), 2 * point2.y() - poly2->at(0).y());

		caliPosMain(center1, center2);

		if (x == speed * 100 / timer) {
			x = 0;

			for (Prise* prise : priseList) {
				if (prise->getColor() == handColor[0]) {
					QPointF* point = prise->getPrise();
					float dist1 = sqrt(pow(center1.x() - point->x(), 2) + pow(center1.y() - point->y(), 2));
					if (dist1 < rayonCercleMain) {
						handColor[0] = grey;
						parent->addPoint();
					}
				}
				else if (prise->getColor() == handColor[1]) {
					QPointF* point = prise->getPrise();
					float dist2 = sqrt(pow(center2.x() - point->x(), 2) + pow(center2.y() - point->y(), 2));
					if (dist2 < rayonCercleMain) {
						handColor[1] = grey;
						parent->addPoint();
					}
				}
			}

			if (handColor[0] != grey || handColor[1] != grey) {
				ui.label_Over->setStyleSheet("QLabel { color : red; font-size : 60px;}");
				ui.label_Over->setAlignment(Qt::AlignCenter);
				ui.label_Over->show();
				parent->loose();
				break;
			}

			if (!priseList.isEmpty()) {
				handColor[rand() % 2] = randomColor();
			}

		}
		x++;
		update();
		Sleep(timer);
	}
}


QColor Twister::randomColor() {
	int color = rand() % 4;

	switch (color)
	{
	case(0):
		return red;
	case(1):
		return blue;
	case(2):
		return green;
	case(3):
		return yellow;
	default:
		return red;
	}
}



