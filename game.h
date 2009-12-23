#ifndef GAME_H_
#define GAME_H_

#include <list>
#include <map>
//#include <QTime>

#include "actor.h"
#include "model3D.h"
#include "function.h"

class Game  // It's the widget which will contain openGl view
{
public:
    Game(); // creation of player ( background,...) and create model
    ~Game();
    void manager(); // trajectori management, shoot mn, score and life mn, ...
    void display(); // display every actor (ennemis, player, and ...)
    inline list<Actor>* getEnemies() {
        return &enemies;
    }
    inline map<string,Model3D>* getModels() {
        return &models;
    }
    inline Actor* getPlayer() {
        return &player;
    }
    Model3D* getModel(string type);
    void addActor(string type = TYPE_DEFAULT_MESH, float size = TAILLE_DEFAULT_VAISSEAU, float posx = POSX_DEFAULT_VAISSEAU, float posy = POSY_DEFAULT_VAISSEAU, float posz = POSZ_DEFAULT_VAISSEAU, float anglex = ANGLEX_DEFAULT_VAISSEAU, float angley = ANGLEY_DEFAULT_VAISSEAU, float anglez = ANGLEZ_DEFAULT_VAISSEAU, float vx=VELOCITYX_DEFAULT_VAISSEAU, float vy=VELOCITYY_DEFAULT_VAISSEAU, float vz=VELOCITYZ_DEFAULT_VAISSEAU, float ax=ACCELERATIONX_DEFAULT_VAISSEAU, float ay=ACCELERATIONY_DEFAULT_VAISSEAU, float az=ACCELERATIONZ_DEFAULT_VAISSEAU); // parameters to complet.
    
    void addModel(string type = TYPE_DEFAULT_MESH); // creation of model (preload)
    void addTire();
    void addEnemy();


private:
    map<string,Model3D> models; // dictionnary of name->Model3d
    list<Actor> enemies;  // enemies, list because lots of movement
    Actor player; // gamer
    int timerGenShoot;
    int timerGenEnemy;
    // and other later
    //background
    //bous/malus
};

#endif
