#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <list>
#include <math.h>

#include "actor.h"
#include "models.h"
#include "parameters.h"
#include "function.h"
#include "text.h"


class GamePlay
{
public:
    ~GamePlay();
    void init(Models* models,Etat* etatGame);
    void gameManager(bool stateKeys[],  bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height);
    
    void getRender(vector<instance>* instances);

private:
    Etat* etatGame;
    void playerManager();
    void firesManager();
    void enemiesManager();
    void collisionManager();
    Models* models;

    list<ActorPhysique> enemies; //TODO remplacer en ActorKeyFrame
    list<ActorPhysique> friendFires;
    list<ActorPhysique> enemiesFires;
    ActorPlayer player;
    Chiffre score; // TODO faire une classe score Chiffre
    Text leScore;
    
    int scoreValeur;
    int timerGenShoot;
    int timerGenShootGros;
    int timerGenEnemy;


    bool* stateKeys;
    bool* stateButtons;
    Point deltaMouse;
    int deltaWheel;
    
    float dTime;
    int widthView,heightView; // pixel
    float width, height; // correspond au nombre d'uniter "opengl" sur la larger et la hauteur 

};

#endif
