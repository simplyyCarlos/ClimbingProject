#include "calibrage.h"


Calibrage::Calibrage(QWidget* _parent, Data* _dt) {
	parent = _parent;
	cb = new Charucoboard();
	dt = _dt;
	view = new View();
	view->setSceneRect(0, 0, 950, 532);
	ui.setupUi(this);
	ui.graphicsView->setScene(view);
	ui.graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

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
	cb->showFullScreen();

	t = new std::thread(&Calibrage::getMatrice, this);
}

void Calibrage::saveCalibration() {
	ui.label_consigne->close();
	ui.graphicsView->close();
	ui.label_attente_2->show();

	dt->setPrise(view->getCircle());
	dt->calibragePrise();

	t->join();
	dt->setCalibrate(true);
	this->close();
	parent->show();
	cb->close();
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

void Calibrage::getMatrice(){
	return;
}