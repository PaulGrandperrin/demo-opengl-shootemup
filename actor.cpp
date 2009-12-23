#include "actor.h"

#include <QApplication>
#include <QThread>

// for trace during test , to kept
#include <iostream>
using namespace std;



Actor::Actor(Model3D* model, float size , t_position pos, t_rotation rot, t_velocity vel, t_accel accel, string fname)
{
    this->model = model;
    this->size = size;
    this->pos = pos;
    this->rot = rot;
    this->vel = vel;
    this->accel = accel;
    this->f = new ifstream(fname.data());
    if (this->f->fail()) {
        cout << "Fichier inexistant !" <<endl;
        delete this->f;
        f = NULL;
    }
    readKeyState(); // We read a key state in the file
    time.start();

}

Actor::~Actor() {
    if (f != NULL) {
        f->close();
        delete f;
    }
}

void Actor::move()
{
    pos.x = pos.x + vel.x/100;
    pos.y = pos.y + vel.y/100;
    pos.z = pos.z + vel.z/100;
}

void Actor::translate(float x, float y, float z)
{
    this->pos.x += x;
    this->pos.y += y;
    this->pos.z += z;
}

void Actor::rotation(float x, float y, float z)
{
    this->rot.x += x;
    this->rot.y += y;
    this->rot.z += z;
}

void Actor::scale(float s)
{
    this->size += s;
}

void Actor::setAcceleration(float x, float y, float z) {
    this->accel.x = x;
    this->accel.y = y;
    this->accel.z = z;
}

void Actor::setVelocity(float x, float y, float z) {
    this->vel.x = x;
    this->vel.y = y;
    this->vel.z = z;
}

void Actor::readKeyState() {
    if (f != NULL && f->peek()!=EOF) {
        if (this->state != NULL)
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

void Actor::setKeyState(short type, float x, float y, float z, float t) {
    if (this->state != NULL)
        delete this->state;
    this->state = new t_key_state;
    this->state->type = type;
    this->state->x = x;
    this->state->y = y;
    this->state->z = z;
    this->state->t = t;
}

void Actor::updatePositionVelocityAcceleration() {
    float cur_t = (float)time.elapsed()/1000;
    if (this->state != NULL && this->state->t < cur_t) {
        if (this->state->type == MODIFY_ACC)
            setAcceleration(this->state->x, this->state->y, this->state->z);
        else
            setVelocity(this->state->x, this->state->y, this->state->z);
        // readKeyState(); // We read another key state in the file (impossible for the moment)
    }
    // We modify the position if needed
    if (this->accel.x || this->vel.x)
        this->pos.x = 0.5*this->accel.x*cur_t*cur_t+this->vel.x*cur_t+this->pos.x;
    if (this->accel.y || this->vel.y)
        this->pos.y = 0.5*this->accel.y*cur_t*cur_t+this->vel.y*cur_t+this->pos.y;
    if (this->accel.z || this->vel.z)
        this->pos.z = 0.5*this->accel.z*cur_t*cur_t+this->vel.z*cur_t+this->pos.z;

    // We modify the velocity if needed
    if (this->accel.x)
        this->vel.x = this->accel.x*cur_t+this->vel.x;
    if (this->accel.y)
        this->vel.y = this->accel.y*cur_t+this->vel.y;
    if (this->accel.z)
        this->vel.z = this->accel.z*cur_t+this->vel.z;
}

void Actor::display()
{

    glLoadIdentity( );
    gluLookAt(0,0,5,0,0,0,0,1,0);
    glTranslatef(pos.x,pos.y,pos.z);
    glScalef(size,size,size);
    glRotatef(rot.x,1,0,0);
    glRotatef(rot.y,0,1,0);
    glRotatef(rot.z,0,0,1);
    this->model->render();

}
