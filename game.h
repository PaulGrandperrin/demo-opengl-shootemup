#ifndef GAME_H_
#define GAME_H_

#include <list>
#include <math.h>

#include "actor.h"
#include "graphicEngine.h"
#include "parameters.h"

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
    inline void resetCam() {
        longitude=0;
        latitude=0;
        zoom=ZOOM_DEFAULT;
        centerX = 0;
        centerY = 0;
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
    int timerGenEnemy;
    float width, height; // correspond au nombre d'uniter "opengl" sur la larger et la hauteur
    //TODO metre a jour c'est valeur lorsque l'a fenetre est resizé
    //TODO Savoir exaxtement combien d'uniter il y a (hauteur et largeur)

    int Mplayer,Mboulet;

    graphicEngine GE;
    float longitude, latitude, zoom, centerX, centerY; // parametre de la camera

    bool* stateKeys;
    bool* stateButtons;
    QPoint deltaMouse;
    int deltaWheel;
    float time;
    bool stop;
    int widthView,heightView;

    bool pause;
    bool passagePause; //permet une bonne transition entre pause-!pause

};

#endif
