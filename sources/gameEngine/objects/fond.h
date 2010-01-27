#ifndef FOND_H_
#define FOND_H_

#include <fstream>
#include <string>
using namespace std;

#include "../../parameters.h"
#include "../../utilities.h"
#include "./actor.h"

#include <vector>
#include <QGLWidget>
#include <QString>
#include <QFont>
#include <QGLWidget>
#include <iostream>


class Fond
{
public:
    Fond() {};
    Fond( vector<int> MPlans, int MSol, vect position,vect rotation,vect scale, vect vel);


    inline vector<Actor> getNuages() {
        return nuages;
    }
    inline vector<Actor> getSols() {
        return sols;
    }
    inline vect getPosition() {
        return position;
    }
    void update(float time);

    inline void setVelocity(vect v) {
        velocity=v;
    }
    inline vect getVelocity() {
        return velocity;
    }

protected:
    vect position;
    vect rotation;
    vect scale;
    vect velocity;
    vector<Actor> nuages;
    vector<Actor> sols;
};
#endif
