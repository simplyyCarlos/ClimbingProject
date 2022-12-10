#include "Circle.h"
#include <qpen.h>

int Circle::numero = 0;


Circle::Circle(QString _color, QPointF _pos, double _rayon) : color(_color), pos(_pos), rayon(_rayon)
{
	id = numero++;
}


QGraphicsItem* Circle::getGraphicsItem() const
{
	QBrush tmpBrush(Qt::SolidPattern);
	tmpBrush.setColor(QColor(6, 129, 253));

	QPen tmpPen;
	tmpPen.setColor(Qt::black);
	tmpPen.setWidth(1);

	QGraphicsEllipseItem* item = new QGraphicsEllipseItem(pos.x() - rayon / 2, pos.y() - rayon / 2, rayon, rayon);
	item->setData(0, id);
	item->setBrush(tmpBrush);
	item->setPen(tmpPen);
	return item;
}