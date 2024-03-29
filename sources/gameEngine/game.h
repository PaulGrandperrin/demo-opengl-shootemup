#ifndef GAME_H_
#define GAME_H_

#include <list>
#include <math.h>

#include "./objects/camera.h"
//#include "graphicEngine.h" // Charge dans models.h
#include "./models.h"
#include "./modePause.h"
#include "./modeMenu.h"
#include "./modeGame.h"
#include "./modeAbout.h"
#include "./modeOption.h"
#include "../utilities.h"



class Game
{
public:
    ~Game();
    Game();
    void update(bool stateKeys[],  bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height);
    void resize(int width,int heigth);
    inline bool close() {
        return (etatGame==STOP);
    }
private:

    Etat etatGame; // Etat defini dans function;h -> a deplacer TODO
    SwitchEtat switchMode;
    void render();
    void gameManager();
    void effectManager(bool stateKeys[]);

    // les differents modes du jeu!
    ModeGame mGame;
    ModeMenu mMenu;
    ModePause mPause;
    ModeAbout mAbout;
    ModeOption mOption;
    Fond fond;

    // tout les models qu'il peut exister
    Models models;
    graphicEngine GE;
    SoundEngine SE;
    Camera cam;

    float dTime; // interval de temps pour les trajectoires ...
    float TTime; //Temp total pour le moteur3D
    int shad;
    bool changePostFX;

};


#endif
