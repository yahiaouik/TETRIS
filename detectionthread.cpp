#include "detectionthread.h"
#include <QThread>
#include <Qtimer>
#include <iostream>
using namespace std;
using namespace cv;

DetectionThread::DetectionThread(): QThread ()
{

}

DetectionThread::~DetectionThread(){

}

void DetectionThread::run(){

    webCam_=new VideoCapture(0);
    webCam_->set(CV_CAP_PROP_FRAME_WIDTH,600);
    webCam_->set(CV_CAP_PROP_FRAME_HEIGHT,150);

    while (true) {
        if (_run)
            this->take_picture();
        msleep(50);
    }

}

void DetectionThread::runDetection(bool val) {
    mutex.lock();
    _run=val;
    mutex.unlock();
}

void DetectionThread::take_picture(){

    int value=0;
            Mat image,image_gray;
            vector<Rect> faces;
            if (webCam_->read(image)) {   // Capture a frame
                // Flip to get a mirror effect
                flip(image,image,1);
                // Invert Blue and Red color channels
                cvtColor(image,image,CV_BGR2RGB);
                // Convert to gray
                cvtColor(image,image_gray,COLOR_BGR2GRAY);

                CascadeClassifier face_cascade;
                if( !face_cascade.load( "../YAHIAOUI_JEAN_TDA/fist_v3.xml" ) )
                {
                    cerr<<"Error loading haarcascade"<<endl;
                    //return -1;
                }
                        face_cascade.detectMultiScale( image_gray, faces, 1.05, 6, 0|CV_HAAR_SCALE_IMAGE, Size(35, 35) );
                        if (faces.size()>0)
                        {

                            // Draw green rectangle
                            for (int i=0;i<(int)faces.size();i++){
                                rectangle(image,faces[i],Scalar(0,255,0),2);

                            }
                        }

                        // Convert to Qt image
                        QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
                        // Display on label
                       emit sendImage(QPixmap::fromImage(img));



           if (faces.size()==2)
            {
                if ((faces[0].x-faces[1].x)>250)
                {
                    if(faces[0].y<(faces[1].y-50)){
                        value=1; // mouvement à gauche

                    }
                    if((faces[0].y-50)>faces[1].y){
                        value=2;// mouvement à droite

                    }

                }
                else if ((faces[0].x-faces[1].x)<-250) {
                    if(faces[0].y<(faces[1].y-50)){
                        value=2;

                    }
                    if((faces[0].y-50)>faces[1].y){
                        value=1;

                    }
                }
                else {
                    value=-1; //rotation de la pièce
                }


       }
    }
    emit sendData(value);
}

void DetectionThread::delete_mythread(){
    this->exit(0);
    this->wait();
    deleteLater();
}

