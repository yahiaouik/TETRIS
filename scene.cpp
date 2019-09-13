#include "scene.h"
#include "mainwindow.h"
#include "game.h"
#include "cube.h"
#include <QApplication>
#include <QDesktopWidget>
#include <GL/glu.h>
#include <QTimer>

 Scene::Scene(QWidget * parent) : QGLWidget(parent)
{
   timer_fall = new QTimer();
   this->game= new Game(timer_fall);
   this->set_pointeur((this->game->get_grille()));


   connect(timer_fall, SIGNAL(timeout()),this, SLOT(fall_piece()));
   timer_fall->start(800);


}

void Scene::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.0,0.0,0.0,1.0);
    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);
    // Reglage de la lumiere
    GLfloat Light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, Light);

    GLfloat positionLight[] = {-60,10,-500, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, positionLight);


    // Activation de la lumiere
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void Scene::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);

}

void Scene::paintGL()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     // Definition de la matrice modelview
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     //Positionnement de la caméra
     gluLookAt(-60,110,-220,//Position cam
               -60,-100,-30,//Point qu'on regarde
               0,0,1);//Vecteur utilisé pour la vue

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70,(double)4/3,1,1000);


    //Gestion du buffer
   if(buffer){
        glEnable(GL_DEPTH_TEST);
    }
    else if (!buffer) {
        glDisable(GL_DEPTH_TEST);
    }

    // Affichage des bordures de la grille
    glLineWidth(1);
    glColor3f(1.0f,1.0f,1.0f);
    GLfloat color_li[] = {1.0f,1.0f,1.0f,1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_li);

    // Affichage des cases
    for(int i=0;i<21;i++){
        glBegin(GL_LINES);
        glVertex3f(-110.0f,0.0f,-10*i);
        glVertex3f(-10.0f,0.0f,-10*i);
        glEnd();
    }
    for(int i=1;i<12;i++){
        glBegin(GL_LINES);
        glVertex3f(-10*i,0.0f,-200.0f);
        glVertex3f(-10*i,0.0f,0.0f);
        glEnd();
    }

    get_coord(pointeur);

}

void Scene::get_coord(Game::cube_logique (*pointeur)[12]){
    Cube *new_cube=new Cube();
    for(int i=1;i<20;i++){
        for(int j=1;j<11;j++){
           if(pointeur[i][j].valeur>0){
                new_cube->drawCube(i,j,pointeur[i][j].couleur);

            }
        }
    }

    delete new_cube;
};

void Scene::NewGame() {
    delete game;
    game = new Game(this->timer_fall);
}

void Scene::move_piece(int data) {
    if (data==-1) {
        this->game->rotate_piece();
    }
    else if (data==1) {
       this->game->turn_piece_left();
    }
    else if (data==2) {
        this->game->turn_piece_right();
    }
}

void Scene::runPieceFall(bool val) {
    (val)?timer_fall->start(game->setSpeed(game->calcul_level())):timer_fall->stop();
}


