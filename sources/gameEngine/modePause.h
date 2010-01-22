#ifndef MODEPAUSE_H_
#define MODEPAUSE_H_

#include <list>
#include <math.h>

#include "./mode.h"



class ModePause : public Mode
{
public:
    ~ModePause();
    void init(Models* models, Camera* camera,Etat* etatGame, SwitchEtat* switchMode);
    void pauseManager(bool stateKeys[],  bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height);
    void moveCam();
    void getRender(vector<instance>* instances);

private:

    Actor cursorPause; // facilite la navigation !

    bool resetCam; // savoir si on est en train de reinitialiser la camera ou pas.


};

#endif
