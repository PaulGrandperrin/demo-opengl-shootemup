#ifndef GAME_H_
#define GAME_H_

#include <list>
#include <map>
//#include <QTime>

#include "actor.h"
#include "graphicEngine.h"
#include "parameters.h"

class Game
{
public:
	~Game();
	void init();
	void update(bool stateKeys[],float time);
	void resize(int width,int heigth);
	bool close(){return stop;}
private:
	
	void render();
	void playerManager();
	void firesManager();
	void enemiesManager();
	void collisionManager();
	void gameManager();

    list<Actor> enemies; //TODO remplacer en ActorKeyFrame
    list<ActorPhysique> fires;
    ActorPhysique player;

    int timerGenShoot;
    int timerGenEnemy;

	int demon,UFO,boulet;

	graphicEngine GE;

	bool* stateKeys;
	float time;
	bool stop;
};

#endif
