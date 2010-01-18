#ifndef MODEPAUSE_H_
#define MODEPAUSE_H_

#include <list>
#include <math.h>

#include "actor.h"
#include "models.h"
#include "parameters.h"
#include "function.h"
#include "camera.h"
#include "text.h"

#include <QPoint>



class ModePause
{
public:
    ~ModePause();
    void init(Models* models, Camera* camera,Etat* etatGame);
    void pauseManager(bool stateKeys[],  bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height);

    void getRender(vector<instance>* instances);

private:

    Etat* etatGame;
    Models* models;
    Camera* camera;

    Actor cursorPause; // facilite la navigation !


    bool* stateKeys;
    bool* stateButtons;
    Point deltaMouse;
    int deltaWheel;

    float dTime;
    int widthView,heightView; // nombre de pixel
    float width, height; // correspond au nombre d'uniter "opengl" sur la larger et la hauteur

    bool resetCam; // savoir si on est en train de reinitialiser la camera ou pas.


};

#endif
