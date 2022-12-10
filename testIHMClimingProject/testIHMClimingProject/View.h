#pragma once
#include "Circle.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <qvector.h>


class View : public QGraphicsScene
{
	Q_OBJECT

private:
	QPointF mousePos;
	QVector<Circle> circleList;
	QVector<QGraphicsItem*> itemList;

public:
	View();
	void updateModel();

protected:
	void drawForeground(QPainter*, const QRect&);

public slots:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
};
