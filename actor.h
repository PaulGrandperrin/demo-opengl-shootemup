#ifndef ACTOR_H_
#define ACTOR_H_

#include <fstream>
#include <string>
using namespace std;

#include "parameters.h"
#include "instance.h"

struct vect
{
    float x,y,z;
};


class Actor
{
public:
    Actor() {};
    Actor(int idModel, vect position,vect rotation,vect scale);

    void update(float time) {} //NOTE ca bouge pas donc ya rien a faire

    //renvoie les donnees directement exploitable par le moteur 3D
    inline instance getInstance() {
        return {position.x,position.y,position.z,rotation.x,rotation.y,rotation.z,scale.x,scale.y,scale.z,idModel};
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
    ActorPhysique(int idModel, vect position,vect rotation,vect scale);
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

protected:
    vect velocity;
    vect acceleration;
    //masque

};

class ActorPlayer: public ActorPhysique
{
public:
    ActorPlayer() {}
    ActorPlayer(int idModel, vect position,vect rotation,vect scale, float decX, float decZ);
    void update(float time);
    void colisionBord(float width, float height);

protected:
    float decelerationX, decelerationZ;
    //vie
    //score NOTE Un score appartient a un joueur !
};

/* TODO a remplir par Romain

NOTE les trajectoires seront chargées une seule fois de la même maniere que les
models.

class ActorKeyFrame: public Actor
{
	ActorKeyFrame(){}
	ActorKeyFrame(int idModel, vect position,vect rotation,vect scale);
	void update(float time);

	inline setTraject(traject t){this->traj=t;}

	private:
		traject traj;
}
*/

// ---------------------Sauvegarde de l'ancienne version---------------------------

/*
#define MODIFY_ACC 0
#define MODIFY_VEL 1



// Structure to define changes on the trajectory
struct t_key_state {
    short type; // Does it modify the velocity or the acceleration ?
    float x; // X new coordinate (velocity or acceleration)
    float y; // Y new coordinate (velocity or acceleration)
    float z; // Z new coordinate (velocity or acceleration)
    float t; // (relative) time when the modification has to be applied
} ;

// Structure to define position
struct t_position {
    float x; // X new coordinate (velocity or acceleration)
    float y; // Y new coordinate (velocity or acceleration)
    float z; // Z new coordinate (velocity or acceleration)
} ;

// Structure to define rotation
struct t_rotation {
    float x; // X new coordinate (velocity or acceleration)
    float y; // Y new coordinate (velocity or acceleration)
    float z; // Z new coordinate (velocity or acceleration)
} ;

// Structure to define velocity
struct t_velocity {
    float x; // X new coordinate (velocity or acceleration)
    float y; // Y new coordinate (velocity or acceleration)
    float z; // Z new coordinate (velocity or acceleration)
} ;

// Structure to define acceleration
struct t_accel {
    float x; // X new coordinate (velocity or acceleration)
    float y; // Y new coordinate (velocity or acceleration)
    float z; // Z new coordinate (velocity or acceleration)
} ;

static const t_position stDefPosition = STRUCT_POSITION_DEF;
static const t_rotation stDefRotation = STRUCT_ROTATION_DEF;
static const t_velocity stDefVelocity = STRUCT_VELOCITY_DEF;
static const t_accel stDefAccel = STRUCT_ACCEL_DEF;


class Actor {
public:
    Actor(int model = 0, float size = TAILLE_DEFAULT_VAISSEAU , t_position pos = stDefPosition, t_rotation rot  = stDefRotation, t_velocity vel  = stDefVelocity, t_accel accel  = stDefAccel);//, string fname=TRAJECTORY_DEFAULT_FILE_NAME);
    ~Actor();
    void translate(float x, float y, float z); // Modify the position coordinates by adding x,y,z respectively to the x,y,z location coordinates
    void rotate(float x, float y, float z); // Modify the angle coordinates by adding x,y,z respectively to the x,y,z angle coordinates
    void scale(float s);  // Modify the size by adding s to the current size value
    void setAcceleration(float x, float y, float z); // Set new x,y,z acceleration coordinates
    void setVelocity(float x, float y, float z); // Set new x,y,z velocity coordinates
    void readKeyState(); // Read a new key state in the file and store it into the state attribute => TODO
    void setKeyState(short type, float x, float y, float z, float t); // Set a new key state (May be useless when the keys will be
    // read in the file)
    void updatePositionVelocityAcceleration(float time); // Update (or not) velocity, acceleration and position attributes (used to have a complex trajectory)

	inline int getModel(){return model;}
    inline t_position getPosition() { return pos; }
    inline t_rotation getRotation() { return rot; }
    inline t_velocity getVelocity() { return vel; }
    inline t_accel getAccel() { return accel; }

private:
    int model;  // 3D object here, but will be replaced by more complete Objects
    float size; // Size of the object
    t_position pos; // X,Y,Z coordinates of the position of the object
    t_rotation rot; // X,Y,Z coordinates of the angle of the object
    t_velocity vel; // X,Y,Z coordinates of the velocity vector
    t_accel accel; // X,Y,Z coordinates of the acceleration vector
    ifstream * f; // Pointer to a trajectory file (may be NULL if an object doesn't need to have a complex trajectory)
    t_key_state * state; // Pointer to the read informations about changes in the trajectory (may be NULL if an object doesn't need to have a complex trajectory)
	float timeElapsed;
};
*/
#endif
