#include "acteur.h"
#include "modelActeur.h"
#include <QApplication>
#include <QtGui>
//#include <QtOpenGL>
#include <QThread>
//#include <math.h>

#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------
//Object
//-------------------------------------------------------------------------------


Acteur::Acteur(ModelActeur* model, float posx, float posy, float posz, float anglex, float angley, float anglez, float size)
{
        
    this->model = model;
    this->anglex=anglex;
    this->angley=angley;
    this->anglez=anglez;
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;
    this->size = size;
//     if (QCoreApplication::arguments().count() > 1) // ????????????????????????????????
//         mesh.load(QCoreApplication::arguments().at(1).toStdString()); // ????????????????????????
//     else
//         mesh.load("meshes/" + type ); // on charge en memoir le demon (objet 3D a afficher dans la vue)

}

Acteur::~Acteur() { }

void Acteur::Deplacement(float x, float y, float z)
{
  qDebug()<< "ma position x : " << posx; 
    this->posx += x;
    this->posy += y;
    this->posz += z;
}

void Acteur::Rotation(float x, float y, float z)
{
    this->anglex += x;
    this->angley += y;
    this->anglez += z;
}

void Acteur::Scale(float s)
{
  this->size += s;
}

void Acteur::Afficher()
{
 //   qDebug()<< "afficher";
    glLoadIdentity( );
    gluLookAt(0,0,5,0,0,0,0,1,0);
    glTranslatef(posx,posy,posz);
    glScalef(size,size,size); // test : rotation du demon
    glRotatef(anglex,1,0,0);
    glRotatef(angley,0,1,0);
    glRotatef(anglez,0,0,1);
//    if (this->model->getMesh() == NULL)
//          qDebug()<< "pas de mesh";
    this->model->getMesh()->render();
//     glBegin(GL_QUADS);					// Start Drawing The Cube
//     glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
//     glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
//     glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
//     glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
//     glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)
//     glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
//     glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
//     glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
//     glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
//     glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
//     glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
//     glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
//     glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
//     glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Front)
//     glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Front)
//     glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
//     glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Back)
//     glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Back)
//     glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Back)
//     glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Back)
//     glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
//     glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
//     glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Left)
//     glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Left)
//     glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Left)
//     glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
//     glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Right)
//     glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
//     glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Right)
//     glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Right)
//     glEnd();						// Done Drawing The Quad
   
}