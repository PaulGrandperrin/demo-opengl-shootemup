#include "modePause.h"
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

ModePause::~ModePause()
{
}

void ModePause::init(Models* models, Camera* camera,Etat* etatGame)
{
    resetCam=false;
    this->camera = camera;
    Mode::init(models, etatGame);

    vect p={0,0,0}, r= {0,-90,0}, s={1,1,1};
    cursorPause = Actor(models->getMCursorPause(), p, r, s);

}


void ModePause::pauseManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    Mode::Manager(stateKeys, stateButtons, deltaMouse, deltaWheel, time, width, height);

    if (resetCam) {
        camera->resetSmart();
        if (camera->camOK()) {
            resetCam=false;
	    vect p={0,0,0}, r= {0,-90,0}, s={1,1,1};
	    cursorPause = Actor(models->getMCursorPause(), p, r, s);
        }
    }
    else if (stateKeys[K_CTRL]) {
        if (stateKeys[K_UP]) {
            camera->setZoom(-0.05);
        }
        else if (stateKeys[K_DOWN]) {
            camera->setZoom(0.05);
        }
        else if ((stateKeys[K_LEFT]) && (stateKeys[K_RIGHT])) {
            resetCam=true;
            camera->resetSmart();
            if (camera->camOK())
                resetCam=false;
        }
    }

    else if (stateKeys[K_SHIFT]) {
        if (stateKeys[K_UP]) {
            camera->setCenterZ(-0.05); // axe Z ver le "bas"
	    vect t={0,0,-0.05};
            cursorPause.translate(t);
        }
        else if  (stateKeys[K_DOWN]) {
            camera->setCenterZ(0.05);
	    vect t={0,0,0.05};
            cursorPause.translate( t);
        }
        if (stateKeys[K_LEFT]) {
            camera->setCenterX(-0.05);
	    vect t={-0.05,0,0};
            cursorPause.translate( t);
        }
        else if (stateKeys[K_RIGHT]) {
            camera->setCenterX(0.05);
	    vect t={-0.05,0,0};
            cursorPause.translate( t);
        }
        if ((deltaWheel != 0)) {
            camera->setZoom(-deltaWheel/(float)240);
        }
        if ((stateButtons[B_LEFT]) && ((deltaMouse.y >= 2 || deltaMouse.y <= -2))) {
            camera->setCenterZ(deltaMouse.y*NB_UNITY_HEIGHT/(float)TAILLE_DEFAULT_Y);
//             cursorPause.translate( {0,0,(deltaMouse.y*NB_UNITY_HEIGHT/(float)TAILLE_DEFAULT_Y)});
	    vect t={0,0,(deltaMouse.y*NB_UNITY_HEIGHT/(float)TAILLE_DEFAULT_Y)};
            cursorPause.translate( t);
        }
        if ((stateButtons[B_LEFT]) && ((deltaMouse.x >= 2 || deltaMouse.x <= -2))) {
            camera->setCenterX(deltaMouse.x*NB_UNITY_WIDTH/(float)TAILLE_DEFAULT_X);
//             cursorPause.translate( {(deltaMouse.x*NB_UNITY_WIDTH/(float)TAILLE_DEFAULT_X)});
	    
	    vect t={(deltaMouse.x*NB_UNITY_WIDTH/(float)TAILLE_DEFAULT_X),0,0};
            cursorPause.translate( t);
        }
    }

    else {
        //>=2 ou <= -2 pour la sensibiliter -> en 20ms, la souris a parcouru plus de 2 ou moin de -2 pixels (Delta).
        if ((stateButtons[B_LEFT]) && ((deltaMouse.y >= 2 || deltaMouse.y <= -2))) {
            camera->setCenterZ(deltaMouse.y*NB_UNITY_HEIGHT*5/(float)TAILLE_DEFAULT_Y);
//             cursorPause.translate( {0,0,(deltaMouse.y*NB_UNITY_HEIGHT*5/(float)TAILLE_DEFAULT_Y)});
	    
	    vect t={0,0,(deltaMouse.y*NB_UNITY_HEIGHT*5/(float)TAILLE_DEFAULT_Y)};
            cursorPause.translate( t);
        }
        if ((stateButtons[B_LEFT]) && ((deltaMouse.x >= 2 || deltaMouse.x <= -2))) {
            camera->setCenterX(deltaMouse.x*NB_UNITY_WIDTH*5/(float)TAILLE_DEFAULT_X);
//             cursorPause.translate( {(deltaMouse.x*NB_UNITY_WIDTH*5/(float)TAILLE_DEFAULT_X)});
	    
	    vect t={(deltaMouse.x*NB_UNITY_WIDTH*5/(float)TAILLE_DEFAULT_X),0,0};
            cursorPause.translate( t);
        }
        if ((stateButtons[B_MIDLE]) && ((deltaMouse.y >= 2 || deltaMouse.y <= -2))) {
            camera->setLatitude(0.01*deltaMouse.y);
        }
        if ((stateButtons[B_MIDLE]) && ((deltaMouse.x >= 2 || deltaMouse.x <= -2))) {
            camera->setLongitude(0.01*deltaMouse.x);
        }
        if ((deltaWheel != 0)) {
            camera->setZoom(-deltaWheel/(float)60);
        }
        if (stateKeys[K_UP])
            camera->setLatitude(0.02);
        if (stateKeys[K_DOWN])
            camera->setLatitude(-0.02);
        if (stateKeys[K_LEFT])
            camera->setLongitude(0.02);
        if (stateKeys[K_RIGHT])
            camera->setLongitude(-0.02);
    }

}


void ModePause::getRender(vector<instance>* instances) {
    instances->push_back(cursorPause.getInstance());

}

