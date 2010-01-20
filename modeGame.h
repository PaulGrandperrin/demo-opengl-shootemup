#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <list>
#include <math.h>

#include "mode.h"


class ModeGame : public Mode
{
public:
    ~ModeGame();
    void init(Models* models,Etat* etatGame);
    void gameManager(bool stateKeys[],  bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height);

    void getRender(vector<instance>* instances);

private:
    void playerManager();
    void firesManager();
    void enemiesManager();
    void collisionManager();

    list<ActorPhysique> enemies; //TODO remplacer en ActorKeyFrame
    list<ActorPhysique> friendFires;
    list<ActorPhysique> enemiesFires;
    ActorPlayer player;
    Score score; // TODO faire une classe score Chiffre
    Text leScore;

    int timerGenShoot;
    int timerGenShootGros;
    int timerGenEnemy;

};

#endif
