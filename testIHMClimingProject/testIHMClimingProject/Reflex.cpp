#include "Reflex.h"
#include "twisterMenu.h"

#define rayonCercle 80.0f
#define rayonCercleMain 35.0f

Reflex::Reflex(TwisterMenu* _parent)
{
	ui.setupUi(this);
	parent = _parent;
	dt = Data::getInstance();
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
	ui.label_Over->hide();
	srand(time(NULL));
	ui.setupUi(this);

	update();
}


void Reflex::paintEvent(QPaintEvent*) {
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
		QPointF center1((poly->at(1).x() + poly->at(2).x()) / 2, (poly->at(1).y() + poly->at(2).y()) / 2);
		QPointF center2((poly2->at(1).x() + poly2->at(2).x()) / 2, (poly2->at(1).y() + poly2->at(2).y()) / 2);
		/*poly->insert(2, QPointF(2 * center1.x() - poly->at(0).x(), 2 * center1.y() - poly->at(0).y()));
		poly2->insert(2, QPointF(2 * center2.x() - poly2->at(0).x(), 2 * center2.y() - poly2->at(0).y()));*/

		caliPosMain(center1, center2);
		painter.drawEllipse(center1, rayonCercleMain, rayonCercleMain);
		painter.drawEllipse(center2, rayonCercleMain, rayonCercleMain);
	}


}

void Reflex::algorithmeJeu() {
	ui.label_Over->hide();
	continueThread = true;
	QPolygonF* poly = new QPolygonF(), * poly2 = new QPolygonF();
	int x = 0, timer = 50, speed = 30;
	while (continueThread) {
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
		QPointF center1((poly->at(1).x() + poly->at(2).x()) / 2, (poly->at(1).y() + poly->at(2).y()) / 2);
		QPointF center2((poly2->at(1).x() + poly2->at(2).x()) / 2, (poly2->at(1).y() + poly2->at(2).y()) / 2);
		/*poly->insert(2, QPointF(2 * center1.x() - poly->at(0).x(), 2 * center1.y() - poly->at(0).y()));
		poly2->insert(2, QPointF(2 * center2.x() - poly2->at(0).x(), 2 * center2.y() - poly2->at(0).y()));*/

		caliPosMain(center1, center2);

		for (QPointF* point : listObjectif) {
			float dist1 = sqrt(pow(center1.x() - point->x(), 2) + pow(center1.y() - point->y(), 2));
			float dist2 = sqrt(pow(center2.x() - point->x(), 2) + pow(center2.y() - point->y(), 2));
			if (dist1 < rayonCercleMain || dist2 < rayonCercleMain) {
				listTouche.append(point);
				listObjectif.removeOne(point);
				parent->addPoint();
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

			if (listObjectif.size() > 2) {
				ui.label_Over->setStyleSheet("QLabel { color : red; font-size : 60px;}");
				ui.label_Over->setAlignment(Qt::AlignCenter);
				ui.label_Over->show();
				parent->loose();
				break;
			}

		}
		x++;
		update();
		Sleep(timer);
	}
	listObjectif.clear();
	listTouche.clear();
}
