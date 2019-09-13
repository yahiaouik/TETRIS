#include "cube.h"
#include "cube.h"
#include <Windows.h>
#include <GL/glu.h>
#include <QColor>
#include <iostream>

using namespace std;

Cube::Cube()
{

}

Cube::~Cube()
{

}

void Cube::drawCube(int z, int x,int color) const{
    glPushMatrix();
    // Couleur de l'objet
    GLfloat color_light[] = {0.0f, 1.0f, 1.0f, 1.0f};
    GLfloat color_lighta[] = {1.0f, 1.0f, 0.0f, 1.0f};
    GLfloat color_light3[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat color_light4[] = {0.0f, 1.0f, 0.0f, 1.0f};
    GLfloat color_light5[] = {1.0f, 0.0f, 1.0f, 1.0f};
    GLfloat color_light6[] = {1.0f, 0.4f, 0.04f, 1.0f};
    GLfloat color_light7[] = {0.0f, 0.0f, 1.0f, 1.0f};
    switch (color) {
    case 1:
        glColor3ub(0,255,255);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_light);

        break;
    case 2:
        glColor3ub(255,255,0);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_lighta);
        break;
    case 3:
        glColor3ub(255,0,0);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_light3);
        break;
    case 4:
        glColor3ub(0,255,0);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_light4);
        break;
    case 5:
        glColor3ub(255,0,255);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_light5);
        break;
    case 6:
        glColor3ub(237, 127, 16);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_light6);
        break;
    case 7:
        glColor3ub(0,0,255);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_light7);
        break;
    }
    //glMaterialfv()

    // Affichage des cubes

    glBegin(GL_QUADS);
    // Face 1
    glVertex3f((x+1)*-10.0f,10.0f,(z+1)*-10.0f);
    glVertex3f((x+1)*-10.0f,0.0f,(z+1)*-10.0f);
    glVertex3f((x)*-10.0f,0.0f,(z+1)*-10.0f);
    glVertex3f((x)*-10.0f,10.0f,(z+1)*-10.0f);
    // Face 2
    glVertex3f((x)*-10.0f,10.0f,(z)*-10.0f);
    glVertex3f((x)*-10.0f,10.0f,(z+1)*-10.0f);
    glVertex3f((x)*-10.0f,0.0f,(z+1)*-10.0f);
    glVertex3f((x)*-10.0f,0.0f,z*-10.0f);
    // Face 3
    glVertex3f((x)*-10.0f,0.0f,z*-10.0f);
    glVertex3f((x+1)*-10.0f,0.0f,z*-10.0f);
    glVertex3f((x+1)*-10.0f,0.0f,(z+1)*-10.0f);
    glVertex3f((x)*-10.0f,0.0f,(z+1)*-10.0f);
    // Face 4
    glVertex3f((x)*-10.0f,0.0f,(z+1)*-10.0f);
    glVertex3f((x)*-10.0f,10.0f,(z+1)*-10.0f);
    glVertex3f((x+1)*-10.0f,10.0f,(z+1)*-10.0f);
    glVertex3f((x+1)*-10.0f,0.0f,(z+1)*-10.0f);
    // Face 5
    glVertex3f((x+1)*-10.0f,0.0f,(z+1)*-10.0f);
    glVertex3f((x+1)*-10.0f,10.0f,(z+1)*-10.0f);
    glVertex3f((x+1)*-10.0f,10.0f,z*-10.0f);
    glVertex3f((x+1)*-10.0f,0.0f,z*-10.0f);
    // Face 6
    glVertex3f((x+1)*-10.0f,10.0f,z*-10.0f);
    glVertex3f((x+1)*-10.0f,10.0f,(z+1)*-10.0f);
    glVertex3f((x)*-10.0f,10.0f,(z+1)*-10.0f);
    glVertex3f((x)*-10.0f,10.0f,z*-10.0f);
    glEnd();


    glPopMatrix();

}
