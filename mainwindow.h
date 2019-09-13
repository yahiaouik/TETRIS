#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include "opencv2/opencv.hpp"
#include <QMainWindow>
#include "game.h"
#include "detectionthread.h"
#include <QTime>
#include <QMutex>

//using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow               // Main Window Class
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);     // Constructor
    void keyPressEvent(QKeyEvent * event);              // Key Press Event for Keys Inputs
    ~MainWindow();                                      // Destructor

private:
    Ui::MainWindow *ui;                                 // UI
    QTimer *timer_update;                               // Display Update Timer
    DetectionThread *detectionThread;                   // Detection Thread (OpenCV Part)


    bool pause=false;                                   // Is the game in pause ?

    chrono::steady_clock::time_point start;             // Start time
    chrono::steady_clock sc;                            // Clock
    double timeBeforePause=0;                           // Time before the last pause

public slots:
    void update_display();                              // Update Main Window Display  autor : Alexis
    void setImage (QPixmap image);                      // Set the image        IN: Image to display  autor : Kenza

private slots:
    void on_new_game_clicked();                         // On NewGame Click autor : Kenza
    void on_pushButton_clicked();                       // On Pause Click autor : Kenza
};

#endif // MAINWINDOW_H
