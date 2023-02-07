#include "View.h"
#include <iostream>
using namespace std;


#define DIAMETRE_CERCLE 25.0


View::View() : QGraphicsScene() {

}


void View::drawForeground(QPainter* painter, const QRect& rect)
{
}


void View::updateModel()
{
	itemList.clear();
	clear();
	for (Circle* cercle : circleList)
	{
		QGraphicsItem* item = cercle->getGraphicsItem();
		item->setAcceptDrops(true);
		itemList.append(item);
		addItem(item);
	}

	update();
}


void View::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	cout << "Mouse clicked" << endl;

	QString couleur = "Blue";
	QPointF mousePos = mouseEvent->scenePos();

	if (mouseEvent->button() == Qt::LeftButton)
	{
		Circle* cercle = new Circle(couleur, QPointF(mousePos.x(), mousePos.y()), DIAMETRE_CERCLE);
		circleList.append(cercle);
	}
	else if (mouseEvent->button() == Qt::RightButton)
	{
		cout << "Right !" << endl;
		mousePos = mouseEvent->scenePos();
		QVector<QGraphicsItem*> items = this->items(mousePos);

		if (items.size() > 0)
		{
			for (int i = 0; i < itemList.size(); i++)
			{
				if (itemList[i] == items[0])
				{
					circleList.remove(i);
					break;
				}
			}
		}
		else
		{
			return;
		}
	}
	updateModel();
}