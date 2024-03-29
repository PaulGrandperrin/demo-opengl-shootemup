#include "./mode.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <sstream>

/* le plan de jeu ce fait sur xz */

//     Y--------X
//     |
//     |
//     |
//     Z

// for trace during test , to kept
#include <iostream>
using namespace std;



Mode::Mode(Models* models, Camera* camera, Etat* etatGame, SwitchEtat* switchMode, SoundEngine* SE)
{
    this->switchMode = switchMode;
    this->etatGame = etatGame;
    this->models = models;
    this->camera = camera;
    this->SE=SE;
}


void Mode::Manager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    this->stateKeys=stateKeys;
    this->stateButtons=stateButtons;
    this->coordMouse=coordMouse;
    this->deltaWheel=deltaWheel;
    this->dTime=time;
    this->widthView=width;
    this->heightView=height;
    this->width=NB_UNITY_WIDTH;
    this->height=NB_UNITY_HEIGHT;
}
