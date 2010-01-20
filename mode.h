#ifndef MODE_H_
#define MODE_H_

#include <list>
#include <math.h>

#include "actor.h"
#include "models.h"
#include "parameters.h"
#include "function.h"
#include "text.h"
#include "camera.h"


class Mode
{
public:
    virtual void init(Models* models,Etat* etatGame);
    virtual void Manager(bool stateKeys[],  bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height);
    virtual void getRender(vector<instance>* instances);

protected:
    Etat* etatGame;
    Models* models;


    bool* stateKeys;
    bool* stateButtons;
    Point coordMouse;
    int deltaWheel;

    float dTime;
    int widthView,heightView; // pixel
    float width, height; // correspond au nombre d'uniter "opengl" sur la larger et la hauteur

};

#endif
