#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QMutex>
#include <QPixmap>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;

//autor : Kenza

class DetectionThread :public QThread   // Thread Class use for the detection
{
    Q_OBJECT
private:
    QMutex mutex;                       // Mutex to manager thread variable
    bool _run=true;                     // Is the detection running ?
    VideoCapture *webCam_;            // Video Capture;

public:
    DetectionThread();                  // Consutructor
    ~DetectionThread();                 // Destructor
    void run();                         // Run function (Thread)
    void take_picture();                // Take picture function (detection)
    void runDetection(bool val);        // Run detection ?  IN : run or not ?

    public slots:
    void delete_mythread();             // Delete thread

    signals :
    void sendData(int data);            // Send data to the game    IN : data to send (int value depending on the action)
    void sendImage(QPixmap image);      // Send picture to the main window  IN : Image to send

};

#endif // MYTHREAD_H
