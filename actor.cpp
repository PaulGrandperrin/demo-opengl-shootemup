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


ActorPlayer::ActorPlayer(int idModel, vect position,vect rotation,vect scale) : ActorPhysique(idModel,position,rotation,scale)
{
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
}