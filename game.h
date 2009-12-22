#ifndef GAME_H_
#define GAME_H_

#include <list>
#include <map>

#include "actor.h"
#include "model3D.h"

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
    void addActeur(string type = TYPE_DEFAULT_MESH, float posx = POSX_DEFAULT_VAISSEAU, float posy = POSY_DEFAULT_VAISSEAU, float posz = POSZ_DEFAULT_VAISSEAU); // parameters to complet.
    void addModel(string type = TYPE_DEFAULT_MESH); // creation of model (preload)


private:
    map<string,Model3D> models; // dictionnary of name->Model3d
    list<Actor> enemies;  // enemies, list because lots of movement
    Actor player; // gamer
    // and other later
    //background
    //bous/malus
};

#endif
