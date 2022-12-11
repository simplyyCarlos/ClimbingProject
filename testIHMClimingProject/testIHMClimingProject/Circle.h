#pragma once
#include <qpoint.h>
#include <qstring.h>
#include <QGraphicsItem>


class Circle
{
	private:
		QString color;
		QPointF pos;
		double rayon;
		int id;
		static int numero;

	public:
		Circle(QString, QPointF, double);
		QPointF* getPos() { return new QPointF(pos); }
		void setPos(double x, double y) { pos = QPointF(x, y); }

		QGraphicsItem* getGraphicsItem() const;
};

