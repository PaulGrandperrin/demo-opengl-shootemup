#ifndef ACTOR_H_
#define ACTOR_H_

#include <fstream>
#include <string>
using namespace std;

#include "../../parameters.h"
#include "../../utilities.h"
#include <list>

class Actor
{
public:
    Actor() {};
    Actor(int idModel, vect position,vect rotation,vect scale);

    void update(float) {} //NOTE ca bouge pas donc ya rien a faire

    //renvoie les donnees directement exploitable par le moteur 3D
    inline instance getInstance() {
        instance i={position.x,position.y,position.z,rotation.x,rotation.y,rotation.z,scale.x,scale.y,scale.z,idModel};
        return i;
    }

    inline int getIdModel() {
        return idModel;
    }

    inline vect getRotation() {
        return rotation;
    }

    inline vect getScale() {
        return scale;
    }

    inline vect getPosition() {
        return position;
    }
    inline void translate(vect t) {
        position.x+=t.x;
        position.y+=t.y;
        position.z+=t.z;
    }
    inline void rotate(vect r) {
        rotation.x+=r.x;
        rotation.y+=r.y;
        rotation.z+=r.z;
    }
    inline void scal(vect s) {
        scale.x+=s.x;
        scale.y+=s.y;
        scale.z+=s.z;
    }

    inline void setTranslation(vect t) {
        position.x=t.x;
        position.y=t.y;
        position.z=t.z;
    }
    inline void setRotation(vect r) {
        rotation.x=r.x;
        rotation.y=r.y;
        rotation.z=r.z;
    }
    inline void setScale(vect s) {
        scale.x=s.x;
        scale.y=s.y;
        scale.z=s.z;
    }

    inline bool isCenter() {
        return ((position.x==0) && (position.z==0) && (position.y==0));
    }

    void toCenter();

protected:
    vect position;
    vect rotation;
    vect scale;
    int idModel;
    bool resetPosition; // si on a à reinitialise la camera (Smart), il ne faut evaluer les step..s qu'une seule fois (constant)
    int nbfoisResetPosition; // le nombre de fois a faire resetCamSmart pour arriver proche de 0
    float stepCenterX, stepCenterY, stepCenterZ; // pour resetCamSmart, le changement a chaque etape
};


class ActorPhysique: public Actor
{
public:
    ActorPhysique() {}
    ActorPhysique(int idModel, vect position,vect rotation,vect scale, float mask = 0.4);
    void update(float time);
    bool sortieEcran(float width, float height);

    inline void setVelocity(vect v) {
        velocity=v;
    }
    inline void setAcceleration(vect a) {
        acceleration=a;
    }
    inline vect getVelocity() {
        return velocity;
    }
    inline vect getAcceleration() {
        return acceleration;
    }
    inline float getMask() {
        return mask;
    }
    bool colision(ActorPhysique* act);

protected:
    vect velocity;
    vect acceleration;
    float mask;
};

class ActorMissile: public ActorPhysique
{
public:
    ActorMissile() {}
    ActorMissile(int idModel, vect position,vect rotation,vect scale, int damage = 50, float mask = 0.4);
    void update(float time);
    inline int getDamage() {
        return damage;
    }
    bool colisionFires(list<ActorMissile>* fires); // pour la bomb, entre autres !
    void setCoefVel(float coef) {
        this->coefVel = coef;
    }

protected:
    int damage;
    float coefVel;
};

class ActorPlayer: public ActorPhysique
{
public:
    ActorPlayer() {}
    ActorPlayer(int idModel, vect position,vect rotation,vect scale, int health, float mask);
    void update(float time);
    void colisionBord(float width, float height);
    inline bool isMort() {
        return health <= 0;
    }
    inline int getHealth() {
        return health;
    }
    inline void setHealth(int hel) {
        health +=hel ;
    }
    inline void initHealth(int hel) {
        health =hel ;
    }
    bool colisionFires(list<ActorMissile>* fires);
private:
    int health;
};

class Trajectory;

class ActorEnemy : public ActorPhysique {
public:
    ActorEnemy() {};
    ActorEnemy(int idModel, vect position,vect rotation,vect scale,Trajectory * traj,int health, int damages, int score, float mask_radius);
    void update(float time);
    inline bool isMort() {
        return health <= 0;
    }
    inline Trajectory * getTraj() {
        return traj;
    }
    inline int getHealth() {
        return health;
    }
    inline void setHealth(int hel) {
        health +=hel ;
    }
    inline void initHealth(int hel) {
        health =hel ;
    }
    inline int getDamages() {
        return damages;
    }
    inline int getScore() {
      return score;
    }
    inline float getMaskRadius() {
      return mask_radius;
    }
    inline int getTimerFire() {
        return timerfire;
    }
    inline void resetTimerFire() {
        timerfire=random(30,80);
    }
    void colisionFires(list<ActorMissile>* fires);

private:
    Trajectory * traj;
    float timeElapsed;
    int nextKeyStateRank;
    int health;
    int damages;
    int score;
    float mask_radius;
    int timerfire;
};
#endif
