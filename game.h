#ifndef GAME_H_
#define GAME_H_

#include <list>
#include <math.h>

// #include "actor.h"
#include "camera.h"
//#include "graphicEngine.h" // Charge dans models.h
#include "models.h"
#include "modePause.h"
#include "modeMenu.h"
#include "modeGame.h"
// #include "parameters.h"
 #include "function.h"
// #include "text.h"


class Game
{
public:
    ~Game();
    void init();
    void update(bool stateKeys[],  bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height);
    void resize(int width,int heigth);
    inline bool close() {
        return (etatGame==STOP);
    }
private:

    Etat etatGame; // Etat defini dans function;h -> a deplacer TODO
    void render();
    void gameManager();

    // les differents modes du jeu!
    ModeGame gamePlay;
    ModeMenu menu;
    ModePause pause;

    // tout les models qu'il peut exister
    Models models;
    Point oldMouse;
    graphicEngine GE;
    Camera cam;

    float dTime; // interval de temps pour les trajectoires ...
    bool passageMenu; //permet une bonne transition entre pause-!pause.
    bool passagePause; //permet une bonne transition entre pause-!pause.


};


#endif
