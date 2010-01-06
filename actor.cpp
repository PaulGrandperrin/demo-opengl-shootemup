#include "actor.h"

// for trace during test , to kept
#include <iostream>
using namespace std;

//---------------------------------------------------------------
// Actor
//---------------------------------------------------------------

Actor::Actor(int idModel, vect position,vect rotation,vect scale)
{
    this->position=position;
    this->rotation=rotation;
    this->scale=scale;
    this->idModel=idModel;
}

//---------------------------------------------------------------
// ActorPhysiqye
//---------------------------------------------------------------

ActorPhysique::ActorPhysique(int idModel, vect position,vect rotation,vect scale) : Actor(idModel,position,rotation,scale)
{
    this->velocity={0,0,0};
    this->acceleration={0,0,0};
}

void ActorPhysique::update(float time) // pas de deleration, gestion simple;
{
    velocity.x+=time*acceleration.x/1000;
    velocity.y+=time*acceleration.y/1000;
    velocity.z+=time*acceleration.z/1000;
    
    position.x+=time*velocity.x/1000;
    position.y+=time*velocity.y/1000;
    position.z+=time*velocity.z/1000;
    
    // pas de frotement
}

bool ActorPhysique::sortieEcran(float width, float height)
{
    return  ((position.x<=-width) || (position.x>=width) || (position.z<=-height) || (position.z>=height));
}

//---------------------------------------------------------------
// ActorPlayer
//---------------------------------------------------------------


ActorPlayer::ActorPlayer(int idModel, vect position,vect rotation,vect scale, float decX, float decZ) : ActorPhysique(idModel,position,rotation,scale)
{
  decelerationX = decX;
  decelerationZ = decZ;
}

void ActorPlayer::colisionBord(float width, float height)
{
    //verification des bords verticaux ensuite des bords horizontaux. (evite de sortir sur les coins.)
    if (position.x<-width) {
        velocity = {-velocity.x*0.2,velocity.y,velocity.z};
//         acceleration = {-acceleration.x*0.2,0,0};
        position = {-width,position.y,position.z};
    }
    else if (position.x>width) {
        velocity = {-velocity.x*0.2,velocity.y,velocity.z};
//         acceleration = {-acceleration.x*0.2,0,0};
        position = {width,position.y,position.z};
    }

    if (position.z<-height) {
        velocity = {velocity.x,velocity.y,-velocity.z*0.2};
//         acceleration = {0,0,-acceleration.z*0.2};
        position = {position.x,position.y,-height};
    }
    else if (position.z>height) {
        velocity = {velocity.x,velocity.y,-velocity.z*0.2};
//         acceleration = {0,0,-acceleration.z*0.2};
        position = {position.x,position.y,height};
    }
}

void ActorPlayer::update(float time)
{
    velocity.x+=time*acceleration.x/1000;
    velocity.y+=time*acceleration.y/1000;
    velocity.z+=time*acceleration.z/1000;
    position.x+=time*velocity.x/1000;
    position.y+=time*velocity.y/1000;
    position.z+=time*velocity.z/1000;
    
    velocity.x*=0.97; // fortement plus grand car surface ++
    velocity.y*=0.98;
    velocity.z*=0.98;
/*    if (velocity.x > 4)
        velocity.x = 4;
    if (velocity.x < -4)
        velocity.x = -4;
    if (velocity.z > 8)
        velocity.z = 8;
    if (velocity.z < -8)
        velocity.z = -8;

// Pour les tests
//     cout << "velX = " << velocity.x << endl;
//     cout << "velZ = " << velocity.z << endl;
    
    if ((velocity.x > 0) && (acceleration.x != 0)) { // > 0
        if (acceleration.x < 0) {
            acceleration.x +=decelerationX;    // TODO factoriser
            if (acceleration.x > 0) {
                acceleration.x =0;
            }
        }
        else {
            acceleration.x -=decelerationX;
        }
        velocity.x+=time*acceleration.x/1000;
    }
    else if ((velocity.x < 0) && (acceleration.x != 0)) {
        if (acceleration.x < 0) {
            acceleration.x +=decelerationX;
        }
        else {
            acceleration.x -= decelerationX;
            if (acceleration.x < 0) {
                acceleration.x =0;
            }
        }
        velocity.x+=time*acceleration.x/1000;
    }
    else if ((velocity.x != 0) && (acceleration.x == 0)) {
        if (velocity.x < 0) {
            velocity.x+=time*decelerationX/1000;
            if (velocity.x > 0) {
                velocity.x =0;
            }
        }
        else {
            velocity.x-=time*decelerationX/1000;
            if (velocity.x < 0) {
                velocity.x =0;
            }
        }
    }
    else {
        velocity.x+=time*acceleration.x/1000;
    }

    velocity.y+=time*acceleration.y/1000;

    if ((velocity.z > 0) && (acceleration.z != 0)) { // > 0
        if (acceleration.z < 0) {
            acceleration.z +=decelerationZ;    // TODO factoriser
            if (acceleration.z > 0) {
                acceleration.z =0;
            }
        }
        else {
            acceleration.z -=decelerationZ;
        }
        velocity.z+=time*acceleration.z/1000;
    }
    else if ((velocity.z < 0) && (acceleration.z != 0)) {
        if (acceleration.z < 0) {
            acceleration.z +=decelerationZ;
        }
        else {
            acceleration.z -= decelerationZ;
            if (acceleration.z < 0) {
                acceleration.z =0;
            }
        }
        velocity.z+=time*acceleration.z/1000;
    }
    else if ((velocity.z != 0) && (acceleration.z == 0)) {
        if (velocity.z < 0) {
            velocity.z+=time*decelerationZ/1000;
            if (velocity.z > 0) {
                velocity.z =0;
            }
        }
        else {
            velocity.z-=time*decelerationZ/1000;
            if (velocity.z < 0) {
                velocity.z =0;
            }
        }
    }
    else {
        velocity.z+=time*acceleration.z/1000;
    }*/


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
