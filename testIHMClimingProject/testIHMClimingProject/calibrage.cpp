#include "calibrage.h"


Calibrage::Calibrage(QWidget* _parent, Data* _dt) {
	parent = _parent;
	cb = new Charucoboard();
	dt = _dt;
	view = new View();
	view->setSceneRect(0, 0, 832, 624);
	ui.setupUi(this);
	ui.graphicsView->setScene(view);
	ui.graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	QPixmap bkgnd("../testIHMClimingProject/img/background_sae.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

	this->setFixedSize(QSize(1050, 776));

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

Calibrage::Calibrage(Calibrage* cal) {
	dt = cal->dt;
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

	t = std::thread(&Calibrage::getMatrice, this);
}


void Calibrage::saveCalibration() {
	ui.label_consigne->close();
	ui.graphicsView->close();
	ui.label_attente_2->show();

	for (Circle* circle : view->getCircle()) {
		dt->addPrise(circle->getPos());
	}

	if (qGuiApp->screens().size() > 1) {
		auto screen = qGuiApp->screens()[1]->geometry();
		dt->calibragePrise(screen.width(), screen.height());
	}
	else {
		auto screen = qGuiApp->screens()[0]->geometry();
		dt->calibragePrise(screen.width(), screen.height());
	}
	

	t.join();
	dt->setCalibrate(true);
	this->close();
	parent->show();
	cb->close();
}

//void Calibrage::set_matrix(py::array_t<double> mat)
//{
//	for (auto i : mat)
//	{
//		cout << i << endl;
//	}
//}

void Calibrage::getImage() {
	py::gil_scoped_acquire acquire;
	try
	{
		auto screenshot = py::module::import("image_capture");
		auto main_screenshot = screenshot.attr("main");
		main_screenshot();
	}
	catch (const std::exception&)
	{
		
		return;
	}
	py::gil_scoped_release release;
}

void Calibrage::getMatrice(){
	py::gil_scoped_acquire acquire;
	try
	{
		windows_shared_memory shmem(create_only, "shm", read_write, sizeof(double[9]));
		mapped_region region(shmem, read_write);
		double* tab = static_cast<double*>(region.get_address());

		auto matrix = py::module::import("testCalibrage");
		auto main_matrix = matrix.attr("main");
		main_matrix();

		dt->setMatrice(tab);
	}
	catch (const std::exception&)
	{
		windows_shared_memory shmem(create_only, "shm", read_write, sizeof(double[9]));
		mapped_region region(shmem, read_write);
		double* tab = static_cast<double*>(region.get_address());
		dt->setMatrice(tab);
		return;
	}
	py::gil_scoped_release release;
}

