#include "charucoboard.h"

Charucoboard::Charucoboard()
{
	ui.setupUi(this);

	if (qGuiApp->screens().size() > 1) {
		auto screen = qGuiApp->screens()[1]->geometry();
		this->move(QPoint(screen.x(), screen.y()));
		this->resize(screen.width(), screen.height());
	}
	else {
		auto screen = qGuiApp->screens()[0]->geometry();
		this->move(QPoint(screen.x(), screen.y()));
		this->resize(screen.width(), screen.height());
	}


	QPixmap bkgnd("../testIHMClimingProject/img/charucoboard.jpeg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
}

Charucoboard::~Charucoboard()
{
}