#include "acteur.h"
//#include "modelActeur.h"
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


Acteur::Acteur(Model3D* model, float posx, float posy, float posz, float anglex, float angley, float anglez, float size, float vx, float vy, float vz, float ax, float ay, float az, string fname)
{    
    this->model = model;
    this->size = size;
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;
    this->anglex = anglex;
    this->angley = angley;
    this->anglez = anglez;
    this->vx = vx;
    this->vy = vy;
    this->vz = vz;
    this->ax = ax;
    this->ay = ay;
    this->az = az;
    this->f = new ifstream(fname.data());
    if(this->f->fail()) {
      qDebug()<< "Fichier inexistant !"; // a changer en cout <<
      delete this->f;
      f = NULL;
    }
    readKeyState(); // We read a key state in the file
    time.start();
//     if (QCoreApplication::arguments().count() > 1) // ????????????????????????????????
//         mesh.load(QCoreApplication::arguments().at(1).toStdString()); // ????????????????????????
//     else
//         mesh.load("meshes/" + type ); // on charge en memoir le demon (objet 3D a afficher dans la vue)

}

Acteur::~Acteur() {
  if(f != NULL) {
    f->close();
    delete f;
  }
}

void Acteur::Deplacement(float x, float y, float z)
{
 // qDebug()<< "ma position x : " << posx; 
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

void Acteur::setAcceleration(float x, float y, float z) {
  this->ax = x;
  this->ay = y;
  this->az = z;
}

void Acteur::setVelocity(float x, float y, float z) {
  this->vx = x;
  this->vy = y;
  this->vz = z;
}

void Acteur::readKeyState() {
  if(f != NULL && f->peek()!=EOF) {
    if(this->state != NULL)
      delete this->state;
    // We get the key state in the file
    this->state = new t_key_state;
    // Here we will store informations read in the file into the attributes of the pointed structure (type,x,y,z,t)
    // TODO
    // Maybe we will need to make other functions to simplify reading and writing in files
  }
  else
    this->state = NULL;
}

void Acteur::setKeyState(short type, float x, float y, float z, float t) {
  if(this->state != NULL)
      delete this->state;
  this->state = new t_key_state;
  this->state->type = type;
  this->state->x = x;
  this->state->y = y;
  this->state->z = z;
  this->state->t = t;
}

void Acteur::updatePositionVelocityAcceleration() {
  float cur_t = (float)time.elapsed()/1000;
  if(this->state != NULL && this->state->t < cur_t) {
    if(this->state->type == MODIFY_ACC)
      setAcceleration(this->state->x, this->state->y, this->state->z);
    else
      setVelocity(this->state->x, this->state->y, this->state->z);
    // readKeyState(); // We read another key state in the file (impossible for the moment)
  }
  // We modify the position if needed
  if(this->ax || this->vx)
    this->posx = 0.5*this->ax*cur_t*cur_t+this->vx*cur_t+this->posx;
  if(this->ay || this->vy)
    this->posy = 0.5*this->ay*cur_t*cur_t+this->vy*cur_t+this->posy;
  if(this->az || this->vz)
    this->posz = 0.5*this->az*cur_t*cur_t+this->vz*cur_t+this->posz;
  
  // We modify the velocity if needed
  if(this->ax)
    this->vx = this->ax*cur_t+this->vx;
  if(this->ay)
    this->vy = this->ay*cur_t+this->vy;
  if(this->az)
    this->vz = this->az*cur_t+this->vz;
}

void Acteur::Afficher()
{
  
    glLoadIdentity( );
    gluLookAt(0,0,5,0,0,0,0,1,0);
    glTranslatef(posx,posy,posz);
    glScalef(size,size,size); // test : rotation du demon
    glRotatef(anglex,1,0,0);
    glRotatef(angley,0,1,0);
    glRotatef(anglez,0,0,1);
//    if (this->model->getMesh() == NULL)
//          qDebug()<< "pas de mesh";
    this->model->render();
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