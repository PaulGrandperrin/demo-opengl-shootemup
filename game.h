#ifndef GAME_H_
#define GAME_H_

#include <list>
#include <math.h>

#include "actor.h"
#include "graphicEngine.h"
#include "parameters.h"

struct gluLookAt
{
  float eyex,eyey,eyez;
  float centerx,centery,centerz;
  float upx,upy,upz;
};

class Game
{
public:
    ~Game();
    void init();
    void update(bool stateKeys[],float time);
    void resize(int width,int heigth);
    inline bool close() {
        return stop;
    }
    inline void resetCam() {
      	GE.initAngle();
        cam.eyez=ZOOM_DEFAULT;
	cam.centerx = 0;
	cam.centery = 0;
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

    int Mplayer,Mboulet;

    graphicEngine GE;
    camera cam;

    bool* stateKeys;
    float time;
    bool stop;

    bool pause;
    bool passagePause; //permet une bonne transition entre pause-!pause
    
};

#endif
