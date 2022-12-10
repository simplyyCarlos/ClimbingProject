#include "calibrage.h"


Calibrage::Calibrage(QWidget* _parent, Data* _dt) {
	parent = _parent;
	dt = _dt;
	view = new View();
	view->setSceneRect(0, 0, 1050 / 2, 570 / 2);
	ui.setupUi(this);
	ui.graphicsView->setScene(view);

	QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

	this->setFixedSize(QSize(1050, 686));

	connect(ui.pushButton_Continuer, SIGNAL(clicked()), this, SLOT(saveCalibration()));

	ui.pushButton_Continuer->setStyleSheet(":hover{background-color : grey;} QPushButton { background-color: rgb(209,102,102); font-size : 15px; color : white; border-width: 1px; border-style: solid; border-color: white; border-radius : 5px;}");
	ui.label_Titre->setStyleSheet("QLabel { color : white; font-size : 50px;}");
	ui.label_consigne->setStyleSheet("QLabel { color : white; font-size : 20px;}");
	ui.label_attente->setStyleSheet("QLabel { color : white; font-size : 30px;}");
	ui.label_attente_2->setStyleSheet("QLabel { color : white; font-size : 30px;}");

	ui.label_attente_2->close();
	ui.label_consigne->close();
	ui.graphicsView->close();
}

Calibrage::~Calibrage(){}

void Calibrage::calibrage() {

	std::thread get_image(&Calibrage::getImage, this);
	get_image.join();
	if (!filename.isEmpty())
	{
		QImage image(filename);
		image = image.scaled(ui.graphicsView->size(), Qt::IgnoreAspectRatio);
		ui.graphicsView->scene()->setBackgroundBrush(image);
		
	}

	ui.label_attente->close();
	ui.label_consigne->show();
	ui.graphicsView->show();

	t = new std::thread(&Data::getCalibrate, dt);
}

void Calibrage::saveCalibration() {
	ui.label_consigne->close();
	ui.graphicsView->close();
	ui.label_attente_2->show();
	for (Circle* circle : view->getCircle()) {
		dt->addPrise(circle->getPos());
	}
	t->join();
	this->close();
	parent->show();
}

void Calibrage::getImage() {
	const char* pyFileName = "image_capture.py";
	wchar_t* program = Py_DecodeLocale("python_instance", NULL);

	FILE* f;
	errno_t err;
	err = fopen_s(&f, pyFileName, "r");
	Py_SetProgramName(program);
	Py_Initialize();
	PyRun_SimpleFile(f, pyFileName);
	if (Py_FinalizeEx() < 0) {
		return;
	}
	PyMem_RawFree(program);
}