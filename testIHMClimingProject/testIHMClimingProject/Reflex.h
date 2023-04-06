#pragma once
#include "ui_twister.h"
#include "Data.h"
#include "Jeu.h"

class TwisterMenu;

class Reflex : public Jeu
{
private:

	QVector<QPointF*> listObjectif, listTouche, prise;

	void paintEvent(QPaintEvent*) override;
	void algorithmeJeu() override;

public:
	Reflex(TwisterMenu*);

};


