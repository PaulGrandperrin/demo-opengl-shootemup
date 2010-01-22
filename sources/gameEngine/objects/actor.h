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
    
protected:
    vect position;
    vect rotation;
    vect scale;
    int idModel;
};


class ActorPhysique: public Actor
{
public:
    ActorPhysique() {}
    ActorPhysique(int idModel, vect position,vect rotation,vect scale, int health = 1, float mask = 0.3);
    void update(float time);
    inline bool isMort() { return health <= 0; }
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
    inline int getHealth() { return health; }
    inline void setHealth(int hel) { health +=hel ; }
    inline void initHealth(int hel) { health =hel ; }
    
protected:
    vect velocity;
    vect acceleration;
    float mask;
    int health;

};

class ActorPlayer: public ActorPhysique
{
public:
    ActorPlayer() {}
    ActorPlayer(int idModel, vect position,vect rotation,vect scale, int health, float mask);
    void update(float time);
    void colisionBord(float width, float height);
};

class Trajectory;

class ActorEnemy : public ActorPhysique {
  public:
    ActorEnemy() {};
    ActorEnemy(int idModel, vect position,vect rotation,vect scale,Trajectory * traj,int health);
    void update(float time);
    inline Trajectory * getTraj() { return traj; }
    void colisionPlayer(ActorPlayer* player);
    void colisionFires(list<ActorPhysique>* fires);
    
  private:
    Trajectory * traj;
    float timeElapsed;
    int nextKeyStateRank;
};
#endif