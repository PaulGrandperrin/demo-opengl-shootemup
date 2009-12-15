#include "acteur.h"
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


Acteur::Acteur(float posx, float posy, float size)
{
    this->anglex=20; // petite mise en forme
    this->angley=0;
    this->posx = posx;
    this->posy = posy;
    this->size = size;
    if (QCoreApplication::arguments().count() > 1) // ????????????????????????????????
        mesh.load(QCoreApplication::arguments().at(1).toStdString()); // ????????????????????????
    else
        mesh.load("meshes/demon.obj"); // on charge en memoir le demon (objet 3D a afficher dans la vue)

}

Acteur::~Acteur() { }

void Acteur::Deplacement(float posx, float posy)
{
    this->posx += posx;
    this->posy += posy;
}

void Acteur::Rotation(float y)
{
    this->angley += y;
}

void Acteur::Afficher()
{
      glLoadIdentity( );
    
    gluLookAt(0,0,5,0,0,0,0,1,0);
        glScalef(size,size,size); // test : rotation du demon
    glTranslatef(posx,posy,0);

    glRotatef(anglex,1,0,0);
    glRotatef(angley,0,7,0);


    this->mesh.render();
}