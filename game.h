#ifndef GAME_H_
#define GAME_H_

#include <list>
#include <math.h>

#include "actor.h"
#include "camera.h"
#include "graphicEngine.h"
#include "parameters.h"
#include "function.h"

#include <QPoint>

class Game
{
public:
    ~Game();
    void init();
    void update(bool stateKeys[],  bool stateButtons[], QPoint deltaMouse, int deltaWheel,float time, int width, int height);
    void resize(int width,int heigth);
    inline bool close() {
        return stop;
    }

private:

    void render();
    void playerManager();
    void firesManager();
    void enemiesManager();
    void collisionManager();
    void gameManager();
    void pauseManager();


    list<Actor> enemies; //TODO remplacer en ActorKeyFrame
    list<ActorPhysique> fires;
    ActorPhysique player;

    int timerGenShoot;
    int timerGenShootGros;
    int timerGenEnemy;
    float width, height; // correspond au nombre d'uniter "opengl" sur la larger et la hauteur
    //TODO metre a jour c'est valeur lorsque l'a fenetre est resizé
    //TODO Savoir exaxtement combien d'uniter il y a (hauteur et largeur)

    int Mplayer,Mboulet;

    graphicEngine GE;
    Camera camera;

    bool* stateKeys;
    bool* stateButtons;
    QPoint deltaMouse;
    int deltaWheel;
    float time;
    bool stop;
    int widthView,heightView;

    bool pause;
    bool passagePause; //permet une bonne transition entre pause-!pause.
    bool resetCam; // savoir si on est en train de reinitialiser la camera ou pas.
    

};

#endif
