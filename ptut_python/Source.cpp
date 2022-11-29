// TestPtut.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
//

#define PY_SSIZE_T_CLEAN
#include <iostream>
#include<opencv2/opencv.hpp>
#include <Python.h>
#include <string>
using namespace std;
using namespace cv;



int webcamLiveVideo() {
    //Open the default video camera
    VideoCapture cap(0);

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video camera" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

    string window_name = "My Camera Feed";
    namedWindow(window_name); //create a window called "My Camera Feed"

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video 

        //Breaking the while loop if the frames cannot be captured
        if (bSuccess == false)
        {
            cout << "Video camera is disconnected" << endl;
            cin.get(); //Wait for any key press
            break;
        }

        //show the frame in the created window
        imshow(window_name, frame);

        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop 
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stopping the video" << endl;
            break;
        }
    }
    return 0;
}

int playVideo(String vidUrl) {
    //open the video file for reading
    VideoCapture cap(vidUrl);

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video file" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    //Uncomment the following line if you want to start the video in the middle
    //cap.set(CAP_PROP_POS_MSEC, 300); 

    //get the frames rate of the video
    double fps = cap.get(CAP_PROP_FPS);
    cout << "Frames per seconds : " << fps << endl;

    String window_name = "My First Video";

    namedWindow(window_name, WINDOW_NORMAL); //create a window

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video 

        //Breaking the while loop at the end of the video
        if (bSuccess == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        //show the frame in the created window
        imshow(window_name, frame);

        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stopping the video" << endl;
            break;
        }
    }
    return 0;
}

int displayImage(String imgUrl)
{
    // Lecture de l'image
    Mat image = imread(imgUrl, IMREAD_UNCHANGED);
    // Gestion d'erreur
    cout << "Loading input image: " << imgUrl << endl;
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    String wdowName = "Climber";
    namedWindow(wdowName);
    //Affichage de l'image dans notre fen�tre
    imshow(wdowName, image);
    // imshow() doit toujours �tre suivi de waitKey(int) pour laisser le temps � Opencv d'afficher l'image dans la fen�tre
    waitKey(0);
    //Destruction de la fen�tre par utilisation de son name wdowName et d�salloue toute la m�moire qui y �tait associ�e.
    //Pas tr�s utile dans ce programme car � la fin d'�x�cution de notre programme .cpp toutes les fen�tres sont ferm�es automatiquement.
    destroyWindow(wdowName);

    return 0;
}

void launchMediapipe(const char* pyFileName,wchar_t* program = Py_DecodeLocale("python_instance", NULL)) {
    if (program == NULL) {
        cout << "wchar_t error\n";
    }
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

int main() {

    launchMediapipe("ptut.py");

    return 0;

}