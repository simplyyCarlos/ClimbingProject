#include "calibrage.h"


Calibrage::Calibrage(QWidget* _parent) {
	parent = _parent;
	view = new View();
	view->setSceneRect(0, 0, 1050 / 2, 570 / 2);
	ui.setupUi(this);
	ui.graphicsView->setScene(view);

	if (!filename.isEmpty())
	{
		QPixmap pixmap(filename);
		pixmap = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
		ui.graphicsView->scene()->addPixmap(pixmap);
	}
	this->setFixedSize(QSize(1050, 686));
}

Calibrage::~Calibrage(){}


