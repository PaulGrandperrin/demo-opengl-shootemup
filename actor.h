#ifndef ACTOR_H_
#define ACTOR_H_

#include <QTime>
#include <fstream>

#include "parameters.h"
#include "model3D.h"


#define MODIFY_ACC 0
#define MODIFY_VEL 1

// Structure to define changes on the trajectory
typedef struct {
    short type; // Does it modify the velocity or the acceleration ?
    float x; // X new coordinate (velocity or acceleration)
    float y; // Y new coordinate (velocity or acceleration)
    float z; // Z new coordinate (velocity or acceleration)
    float t; // (relative) time when the modification has to be applied
} t_key_state;

class Actor {
public:
    Actor(Model3D* model = NULL, float posx = POSX_DEFAULT_VAISSEAU, float posy = POSY_DEFAULT_VAISSEAU, float posz = POSZ_DEFAULT_VAISSEAU, float anglex = ANGLEX_DEFAULT_VAISSEAU, float angley = ANGLEY_DEFAULT_VAISSEAU, float anglez = ANGLEZ_DEFAULT_VAISSEAU, float size = TAILLE_DEFAULT_VAISSEAU, float vx=VELOCITYX_DEFAULT_VAISSEAU, float vy=VELOCITYY_DEFAULT_VAISSEAU, float vz=VELOCITYZ_DEFAULT_VAISSEAU, float ax=ACCELERATIONX_DEFAULT_VAISSEAU, float ay=ACCELERATIONY_DEFAULT_VAISSEAU, float az=ACCELERATIONZ_DEFAULT_VAISSEAU, string fname=TRAJECTORY_DEFAULT_FILE_NAME);
    ~Actor();
    void move(float x, float y, float z); // Modify the position coordinates by adding x,y,z respectively to the x,y,z location coordinates
    void rotation(float x, float y, float z); // Modify the angle coordinates by adding x,y,z respectively to the x,y,z angle coordinates
    void scale(float s);  // Modify the size by adding s to the current size value
    void setAcceleration(float x, float y, float z); // Set new x,y,z acceleration coordinates
    void setVelocity(float x, float y, float z); // Set new x,y,z velocity coordinates
    void readKeyState(); // Read a new key state in the file and store it into the state attribute => TODO
    void setKeyState(short type, float x, float y, float z, float t); // Set a new key state (May be useless when the keys will be
    // read in the file)
    void updatePositionVelocityAcceleration(); // Update (or not) velocity, acceleration and position attributes (used to have a complex trajectory)
    void display();

private:
    Model3D* model;  // 3D object here, but will be replaced by more complete Objects
    float size; // Size of the object
    float posx, posy, posz; // X,Y,Z coordinates of the position of the object
    float anglex, angley, anglez; // X,Y,Z coordinates of the angle of the object
    float vx, vy, vz; // X,Y,Z coordinates of the velocity vector
    float ax, ay, az; // X,Y,Z coordinates of the acceleration vector
    QTime time; // We need it to determine new coordinates
    ifstream * f; // Pointer to a trajectory file (may be NULL if an object doesn't need to have a complex trajectory)
    t_key_state * state; // Pointer to the read informations about changes in the trajectory (may be NULL if an object doesn't need to have a complex trajectory)
};
#endif
