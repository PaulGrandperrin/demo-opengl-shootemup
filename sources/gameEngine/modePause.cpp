#include "./modePause.h"
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

ModePause::ModePause(Models* models, Camera* camera,Etat* etatGame, SwitchEtat* switchMode) : Mode(models, camera, etatGame, switchMode)
{
    resetCam=false;
    oldMouse.x = 0;
    oldMouse.y = 0;
    deltaMouse.x = 0;
    deltaMouse.y = 0;
    vect p={0,0,0}, r= {0,-90,0}, s={1,1,1};
    cursorPause = Actor(models->getMCursorPause(), p, r, s);

}


void ModePause::pauseManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    deltaMouse.x = coordMouse.x-oldMouse.x;
    deltaMouse.y = coordMouse.y-oldMouse.y;
    oldMouse.x=coordMouse.x;
    oldMouse.y=coordMouse.y;

    if (*switchMode == TOMENU && (!camera->camOKMenu())) {
        camera->toModeMenuSmart();
    }
    else if (*switchMode == TOMENU && (camera->camOKMenu())) {
        *switchMode = NONE;
        *etatGame = MENU;
    }
    else if (*switchMode == NONE && stateKeys[K_ESC]) {
        *switchMode = TOMENU;
        vect p={0,0,0}, r= {0,-90,0}, s={1,1,1};
        cursorPause = Actor(models->getMCursorPause(), p, r, s);
    }
    else {
        //NOTE:le coordMouse est l'ancien deltaMouse seul le nom change
        Mode::Manager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
        moveCam();
    }



}

void ModePause::moveCam() {

    if (resetCam) {
        camera->toModeMenuSmart();
        if (camera->camOKMenu()) {
            resetCam=false;
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
            vect p={0,0,0}, r= {0,-90,0}, s={1,1,1};
            cursorPause = Actor(models->getMCursorPause(), p, r, s);
            camera->toModeMenuSmart();
            if (camera->camOKMenu())
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
            vect t={0.05,0,0};
            cursorPause.translate( t);
        }
        if ((deltaWheel != 0)) {
            camera->setZoom(-deltaWheel/(float)240);
        }
        if ((stateButtons[B_LEFT]) && ((deltaMouse.y >= 2 || deltaMouse.y <= -2))) {
            camera->setCenterZ(deltaMouse.y*NB_UNITY_HEIGHT/600.0);
//             cursorPause.translate( {0,0,(deltaMouse.y*NB_UNITY_HEIGHT/(float)TAILLE_DEFAULT_Y)});
            vect t={0,0,(deltaMouse.y*NB_UNITY_HEIGHT/600.0)};
            cursorPause.translate( t);
        }
        if ((stateButtons[B_LEFT]) && ((deltaMouse.x >= 2 || deltaMouse.x <= -2))) {
            camera->setCenterX(deltaMouse.x*NB_UNITY_WIDTH/600.0);
//             cursorPause.translate( {(deltaMouse.x*NB_UNITY_WIDTH/(float)TAILLE_DEFAULT_X)});

            vect t={(deltaMouse.x*NB_UNITY_WIDTH/(float)600.0),0,0};
            cursorPause.translate( t);
        }
    }

    else {
        //>=2 ou <= -2 pour la sensibiliter -> en 20ms, la souris a parcouru plus de 2 ou moin de -2 pixels (Delta).
        if ((stateButtons[B_LEFT]) && ((deltaMouse.y >= 2 || deltaMouse.y <= -2))) {
            camera->setCenterZ(deltaMouse.y*NB_UNITY_HEIGHT*5/600.0);
//             cursorPause.translate( {0,0,(deltaMouse.y*NB_UNITY_HEIGHT*5/(float)TAILLE_DEFAULT_Y)});

            vect t={0,0,(deltaMouse.y*NB_UNITY_HEIGHT*5/600.0)};
            cursorPause.translate( t);
        }
        if ((stateButtons[B_LEFT]) && ((deltaMouse.x >= 2 || deltaMouse.x <= -2))) {
            camera->setCenterX(deltaMouse.x*NB_UNITY_WIDTH*5/600.0);
//             cursorPause.translate( {(deltaMouse.x*NB_UNITY_WIDTH*5/(float)TAILLE_DEFAULT_X)});

            vect t={(deltaMouse.x*NB_UNITY_WIDTH*5/600.0),0,0};
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

    // pour ne pas passer sous le fond
//     int y = sin(camera->getLatitude()) * camera->getZoom();
//     if (y < -2) {
//       camera->setLatitude(0.01);
//       camera->setZoom(0.01);
//       cout << "dehors " << endl;
//     }
}


void ModePause::getRender(vector<instance>* instances) {
    instances->push_back(cursorPause.getInstance());

}

