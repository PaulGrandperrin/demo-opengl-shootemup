#ifndef ACTOR_H_
#define ACTOR_H_

#include <QTime>
#include <fstream>

#include "parameters.h"
#include "model3D.h"


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
    Actor(Model3D* model = NULL, float size = TAILLE_DEFAULT_VAISSEAU , t_position pos = stDefPosition, t_rotation rot  = stDefRotation, t_velocity vel  = stDefVelocity, t_accel accel  = stDefAccel, string fname=TRAJECTORY_DEFAULT_FILE_NAME);
    ~Actor();
    void translate(float x, float y, float z); // Modify the position coordinates by adding x,y,z respectively to the x,y,z location coordinates
    void rotation(float x, float y, float z); // Modify the angle coordinates by adding x,y,z respectively to the x,y,z angle coordinates
    void scale(float s);  // Modify the size by adding s to the current size value
    void setAcceleration(float x, float y, float z); // Set new x,y,z acceleration coordinates
    void setVelocity(float x, float y, float z); // Set new x,y,z velocity coordinates
    void readKeyState(); // Read a new key state in the file and store it into the state attribute => TODO
    void setKeyState(short type, float x, float y, float z, float t); // Set a new key state (May be useless when the keys will be
    // read in the file)
    void updatePositionVelocityAcceleration(); // Update (or not) velocity, acceleration and position attributes (used to have a complex trajectory)
    void display();
    
    inline t_position getPosition() { return pos; }
    inline t_rotation getRotation() { return rot; }
    inline t_velocity getVelocity() { return vel; }
    inline t_accel getAccel() { return accel; }
    void move();

private:
    Model3D* model;  // 3D object here, but will be replaced by more complete Objects
    float size; // Size of the object
    t_position pos; // X,Y,Z coordinates of the position of the object
    t_rotation rot; // X,Y,Z coordinates of the angle of the object
    t_velocity vel; // X,Y,Z coordinates of the velocity vector
    t_accel accel; // X,Y,Z coordinates of the acceleration vector
    QTime time; // We need it to determine new coordinates
    ifstream * f; // Pointer to a trajectory file (may be NULL if an object doesn't need to have a complex trajectory)
    t_key_state * state; // Pointer to the read informations about changes in the trajectory (may be NULL if an object doesn't need to have a complex trajectory)
};
#endif
