#include "./actor.h"
#include "./trajectory.h"
#include <stdlib.h>
#include <math.h>

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

ActorPhysique::ActorPhysique(int idModel, vect position,vect rotation,vect scale, int health, int damage, float mask) : Actor(idModel,position,rotation,scale)
{
    this->velocity.x=0;
    this->velocity.y=0;
    this->velocity.z=0;

    this->acceleration.x=0;
    this->acceleration.y=0;
    this->acceleration.z=0;

    this->mask=mask;
    this->health = health;
    this->damage = damage;
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


ActorPlayer::ActorPlayer(int idModel, vect position,vect rotation,vect scale, int health, float mask, int damage) : ActorPhysique(idModel,position,rotation,scale,health,damage,mask)
{
  resetPosition = true;
}

void ActorPlayer::colisionBord(float width, float height)
{
    //verification des bords verticaux ensuite des bords horizontaux. (evite de sortir sur les coins.)
    if (position.x<-width) {
        velocity.x=-velocity.x*0.2;
        position.x=-width;
    }
    else if (position.x>width) {
        velocity.x=-velocity.x*0.2;
        position.x=width;
    }

    if (position.z<-height) {
        velocity.z=-velocity.z*0.2;
        position.z=-height;
    }
    else if (position.z>height) {
        velocity.z=-velocity.z*0.2;
        position.z=height;
    }
}

void ActorPlayer::update(float time)
{
  vect r = {0,0,0};
    velocity.x+=time*acceleration.x/1000;
    velocity.y+=time*acceleration.y/1000;
    velocity.z+=time*acceleration.z/1000;
    
    position.x+=time*velocity.x/1000;
    position.y+=time*velocity.y/1000;
    position.z+=time*velocity.z/1000;

    velocity.x*=0.98; // fortement plus grand car surface ++
    velocity.y*=0.99;
    velocity.z*=0.99;
    
}


void ActorPlayer::toCenter()
{
    if (resetPosition) {
        nbfoisResetPosition = TEMP_RESETCAM_SMART_PAUSE;
        stepCenterX = -position.x / nbfoisResetPosition;
	stepCenterY = -position.y / nbfoisResetPosition;
        stepCenterZ = -position.z / nbfoisResetPosition;
        resetPosition = false;
    }

    if (position.x != 0) {
        position.x += stepCenterX;
    }
    if (position.y != 0) {
        position.y += stepCenterY;
    }
    if (position.z != 0) {
        position.z += stepCenterZ;
    }

    nbfoisResetPosition--; // on approche du {0,0,ZOOM_DEFAULT,0,0}

    if (nbfoisResetPosition == 0) { // on est tres proche donc on peut le faire
        position.x = 0;
	position.y = 0;
	position.z = 0;
    }
    if (isCenter()) {
        resetPosition = true; // pour une qutre fois
    }

}

////////////////////////////////////////
// ActorEnemy
////////////////////////////////////////

ActorEnemy::ActorEnemy(int idModel, vect position,vect rotation,vect scale,Trajectory * traj,int health, int damage)
        : ActorPhysique(idModel,position,rotation,scale,damage,health) {
    if (traj != NULL)
        this->traj = traj;
    else {
        cout << "Undefined trajectory !" << endl;
        exit(0);
    }
    timeElapsed = 0;
    nextKeyStateRank = 0;
}

void ActorEnemy::update(float time) {
    // TODO Faire fonctionner le shmilblick : copier les keystates dans un attribut propre a la classe ActorEnemy, puis en enlever un a chaque fois
    // qu'on l'atteint. Une fois cette liste vide, l'actor se comporte comme un actor physique
    timeElapsed += time;
    vector<t_key_state> states = traj->getKeyStates();
    vector<t_key_state>::iterator rit;
    int rank = 0;
    for (rit=states.begin(); rit!=states.end(); rit++)
    {
        if (timeElapsed > rit->t && rank == nextKeyStateRank)
        {
            if (rit->vx != 0 || rit->vy != 0 || rit->vz != 0) {
                vect v={rit->vx,rit->vy,rit->vz};
                setVelocity(v);
            }
            else {
                vect a={rit->ax,rit->ay,rit->az};
                setAcceleration(a);
            }
            nextKeyStateRank++;
        }
        rank++;
    }
    ActorPhysique::update(time);
}

bool ActorEnemy::colisionPlayer(ActorPlayer* player) {
    float dist = 0;
    float distX,distZ;
    distX = getPosition().x - player->getPosition().x;
    distZ = getPosition().z - player->getPosition().z;
    dist = sqrt(distX*distX + distZ*distZ);
    return (player->getMask() + getMask() > dist);
}

void ActorEnemy::colisionFires(list<ActorPhysique>* fires) {
    float dist = 0;
    float distX,distZ;
    list<ActorPhysique>::iterator itAP;
    itAP = fires->begin();
    while (itAP!=fires->end())
    {
        distX = getPosition().x - itAP->getPosition().x;
        distZ = getPosition().z - itAP->getPosition().z;
        dist = sqrt(distX*distX + distZ*distZ);
        if (itAP->getMask() + getMask() > dist) {
            itAP = fires->erase(itAP);
            setHealth(-itAP->getDamage());
        }
        else {
            itAP++;
        }
    }
}
