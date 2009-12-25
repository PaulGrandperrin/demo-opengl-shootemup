#include "actor.h"

// for trace during test , to kept
#include <iostream>
using namespace std;


Actor::Actor(int idModel, vect position,vect rotation,vect scale)
{
	this->position=position;
	this->rotation=rotation;
	this->scale=scale;
	this->idModel=idModel;
}

ActorPhysique::ActorPhysique(int idModel, vect position,vect rotation,vect scale)
{
	this->position=position;
	this->rotation=rotation;
	this->scale=scale;
	this->idModel=idModel;
	this->velocity={0,0,0};
	this->acceleration={0,0,0};
}

void ActorPhysique::update(float time)
{
	velocity.x+=time*acceleration.x/1000;
	velocity.y+=time*acceleration.y/1000;
	velocity.z+=time*acceleration.z/1000;
	
	position.x+=time*velocity.x/1000;
	position.y+=time*velocity.y/1000;
	position.z+=time*velocity.z/1000;
}


// ---------------------Sauvegarde de l'ancienne version---------------------------

/*
Actor::Actor(int model, float size , t_position pos, t_rotation rot, t_velocity vel, t_accel accel)//, string fname)
{
	timeElapsed=0;
    this->model = model;
    this->size = size;
    this->pos = pos;
    this->rot = rot;
    this->vel = vel;
    this->accel = accel;
    //this->f = new ifstream(fname.data());
    //if (this->f->fail()) {
        //cout << "Fichier inexistant !" <<endl;
        //delete this->f;
        f = NULL;
    //}
    //readKeyState(); // We read a key state in the file

}

Actor::~Actor() {
    if (f != NULL) {
        f->close();
        delete f;
    }
}

void Actor::translate(float x, float y, float z)
{
    this->pos.x += x;
    this->pos.y += y;
    this->pos.z += z;
}

void Actor::rotate(float x, float y, float z)
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

void Actor::updatePositionVelocityAcceleration(float time)
{
	cout << "1"<<endl;
	timeElapsed+=time;
    if (this->state != NULL && this->state->t < timeElapsed) {
        if (this->state->type == MODIFY_ACC)
            setAcceleration(this->state->x, this->state->y, this->state->z);
        else
            setVelocity(this->state->x, this->state->y, this->state->z);
        // readKeyState(); // We read another key state in the file (impossible for the moment)
    }
    // We modify the position if needed
    if (this->accel.x || this->vel.x)
        this->pos.x = 0.5*this->accel.x*timeElapsed*timeElapsed+this->vel.x*timeElapsed+this->pos.x;
    if (this->accel.y || this->vel.y)
        this->pos.y = 0.5*this->accel.y*timeElapsed*timeElapsed+this->vel.y*timeElapsed+this->pos.y;
    if (this->accel.z || this->vel.z)
        this->pos.z = 0.5*this->accel.z*timeElapsed*timeElapsed+this->vel.z*timeElapsed+this->pos.z;

    // We modify the velocity if needed
    if (this->accel.x)
        this->vel.x = this->accel.x*timeElapsed+this->vel.x;
    if (this->accel.y)
        this->vel.y = this->accel.y*timeElapsed+this->vel.y;
    if (this->accel.z)
        this->vel.z = this->accel.z*timeElapsed+this->vel.z;
}
*/
