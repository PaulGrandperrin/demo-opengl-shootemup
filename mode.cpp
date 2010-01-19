#include "mode.h"
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



void Mode::init(Models* models, Etat* etatGame)
{

    this->etatGame = etatGame;
    this->models = models;
}


void Mode::Manager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    this->stateKeys=stateKeys;
    this->stateButtons=stateButtons;
    this->deltaMouse=deltaMouse;
    this->deltaWheel=deltaWheel;
    this->dTime=time;
    this->widthView=width;
    this->heightView=height;
    this->width=NB_UNITY_WIDTH;
    this->height=NB_UNITY_HEIGHT;
}


void Mode::getRender(vector<instance>* instances) {

    // on recupere toute les instances a afficher

}

