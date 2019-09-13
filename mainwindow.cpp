#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include<QWidget>
#include <QTimer>
#include "game.h"
#include <QKeyEvent>
#include<QString>
#include<QThread>
#include "scene.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    start = sc.now();

    timer_update = new QTimer(this);
    connect(timer_update, SIGNAL(timeout()), this, SLOT(update_display()));
    timer_update->start(100);

    detectionThread=new DetectionThread();
    connect(detectionThread,SIGNAL(sendData(int)),ui->scene,SLOT(move_piece(int)));
    connect(detectionThread,SIGNAL(sendImage(QPixmap)),this,SLOT(setImage(QPixmap)));
    detectionThread->start();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if (!pause) {
        switch(event->key())
        {
        case Qt::Key_D :
            ui->scene->getGame()->turn_piece_right();
            break;
        case Qt::Key_Q:
            ui->scene->getGame()->turn_piece_left();
            break;
        case Qt::Key_S:
            ui->scene->getGame()->rotate_piece();
            break;
        }
    }
}

void MainWindow::update_display(){
    if(ui->scene->getGame()->end_game()){
        ui->niveau->setText("Perdu !!!");
        timer_update->stop();
    }else {
        ui->score->setText("Points :"+QString::number(ui->scene->getGame()->get_point()));
        ui->niveau->setText("Level :"+QString::number(ui->scene->getGame()->calcul_level()));
        auto now = sc.now();
        auto time_span = static_cast<chrono::duration<double>>(now - start);
        int seconds = ((int)(time_span.count()+timeBeforePause))%60;
        int minutes = ((int)(time_span.count()+timeBeforePause))/60;
        string _seconds, _minutes;
        if (seconds<10)
            _seconds="0";
        _seconds+=to_string(seconds);
        if (minutes<10)
            _minutes="0";
        _minutes+=to_string(minutes);
        ui->time->setText(QString::fromStdString(_minutes + ":" + _seconds));;
        ui->scene->updateGL();
    }

}

void MainWindow::on_new_game_clicked()
{
    ui->scene->NewGame();
    ui->scene->set_pointeur(ui->scene->getGame()->get_grille());
    timer_update->start(100);
    start = sc.now();
    timeBeforePause=0;
    ui->scene->runPieceFall(true);

}

void MainWindow::on_pushButton_clicked()
{
    pause= !pause;

    if(pause){
        timeBeforePause += static_cast<chrono::duration<double>>(sc.now() - start).count();
        timer_update->stop();
        ui->scene->runPieceFall(false);
        detectionThread->runDetection(false);

    }
    else {
        start=sc.now();
        timer_update->start(100);
        ui->scene->runPieceFall(true);
        detectionThread->runDetection(true);
    }
}

void MainWindow::setImage(QPixmap image) {
    ui->image->setPixmap(image);
}
