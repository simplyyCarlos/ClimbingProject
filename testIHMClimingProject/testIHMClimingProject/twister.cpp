#include "twister.h"

#define rayonCercle 30.0f

Twister::Twister(QWidget* _parent, Data* _dt)
{
	ui.setupUi(this);
	parent = _parent;
	dt = _dt;

	QRect screen;

	if (qGuiApp->screens().size() > 1) {
		screen = qGuiApp->screens()[1]->geometry();
		this->move(QPoint(screen.x(), screen.y()));
		this->resize(screen.width(), screen.height());
	}
	else {
		screen = qGuiApp->screens()[0]->geometry();
		this->move(QPoint(screen.x(), screen.y()));
		this->resize(screen.width(), screen.height());
	}
		
	ui.setupUi(this);
	updateModel();
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
	for (QPointF* pos : dt->getPrise()) {
		painter.drawEllipse(pos->x() - rayonCercle / 2, pos->y() - rayonCercle / 2, rayonCercle, rayonCercle);
	}

	tmpBrush.setColor(QColor(245, 20, 20));
	painter.setBrush(tmpBrush);

}

void Twister::updateModel() {
	update();
}

