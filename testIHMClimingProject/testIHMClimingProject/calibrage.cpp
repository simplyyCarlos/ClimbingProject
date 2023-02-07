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

Calibrage::~Calibrage(){
	delete cb, view, dt;
}

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

	t.join();

	if (qGuiApp->screens().size() > 1) {
		auto screen = qGuiApp->screens()[1]->geometry();
		dt->calibragePrise(screen.width(), screen.height());
	}
	else {
		auto screen = qGuiApp->screens()[0]->geometry();
		dt->calibragePrise(screen.width(), screen.height());
	}
	
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
	/*py::gil_scoped_acquire acquire;
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
	py::gil_scoped_release release;*/
	VideoCapture cap(0);
	double height = 1080 / 2;
	double width = 1920/2;
	cap.set(CAP_PROP_FRAME_HEIGHT, height);
	cap.set(CAP_PROP_FRAME_WIDTH , width);
	if (cap.isOpened() == false) {
		cout << "Impossible d'ouvrir le flux vidéo de la caméra\n";
		cin.get();
		exit(EXIT_FAILURE);
	}
	String window_name = "My capture frame";
		
	namedWindow(window_name);
	
		
	while (1) {
		Mat frame;
		bool bSuccess = cap.read(frame);
		if (bSuccess == false) {
			cout << "Video camera is disconnect\n";
			cin.get();
			return;
		}

		imshow(window_name, frame);
		if (waitKey(10) == 27) {
			Mat saved_img; 
			cap.read(saved_img);
			imwrite("savedImage.jpg", saved_img);
			cout << "Esc key pressed by user. Stopping the video" << endl;

			break;
		}

	}
	cap.release();
	return;
	
}

void Calibrage::getMatrice(){
	/*py::gil_scoped_acquire acquire;
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
	py::gil_scoped_release release;*/
	try
	{
		Mat img = imread("./img/charucoboard.jpeg", IMREAD_GRAYSCALE);
		VideoCapture cap(0);
		cap.set(CAP_PROP_FRAME_WIDTH, 1024);
		cap.set(CAP_PROP_FRAME_HEIGHT, 576);
		Ptr<SIFT> sift = SIFT::create();
		vector<KeyPoint> kp_image;
		Mat desc_image;
		sift->detectAndCompute(img, noArray(), kp_image, desc_image);
		FlannBasedMatcher flann;
		bool charucoboardDetected = false;
		while (charucoboardDetected == false)
		{
			try
			{
				Mat frame;
				cap >> frame;
				Mat grayframe;
				cvtColor(frame, grayframe, COLOR_BGR2GRAY);
				vector<KeyPoint> kp_grayframe;
				Mat desc_grayframe;
				sift->detectAndCompute(grayframe, noArray(), kp_grayframe, desc_grayframe);
				vector<vector<DMatch>> matches;
				flann.knnMatch(desc_image, desc_grayframe, matches, 2);
				vector<DMatch> good_points;
				for (int i = 0; i < matches.size(); i++)
				{
					if (matches[i][0].distance < 0.7 * matches[i][1].distance)
					{
						good_points.push_back(matches[i][0]);
					}
				}
				Mat query_pts = Mat(good_points.size(), 1, CV_32FC2);
				Mat train_pts = Mat(good_points.size(), 1, CV_32FC2);
				for (int i = 0; i < good_points.size(); i++)
				{
					query_pts.at<Vec2f>(i) = kp_image[good_points[i].queryIdx].pt;
					train_pts.at<Vec2f>(i) = kp_grayframe[good_points[i].trainIdx].pt;
				}
				Mat mask;
				Mat matrix = findHomography(query_pts, train_pts, RANSAC, 5.0, mask);
				Mat matrixRet;
				invert(matrix, matrixRet);
				charucoboardDetected = true;
				dt->setMatrice(matrixRet);
			}
			catch (...)
			{
				continue;
			}
		}

	}
	catch (...)
	{
		;
	}
}

