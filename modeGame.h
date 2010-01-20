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
    void trajectoriesManager();
    void enemiesManager();
    void collisionManager();

    list<Trajectory> trajectories;
    list<ActorPhysique> friendFires;
    list<ActorPhysique> enemiesFires;
    ActorPlayer player;
    Score score; // TODO faire une classe score Chiffre
    Text leScore;

    int timerGenTrajectorySequence; // Correspond à l'intervalle de temps qui sépare l'apparition de 2 ennemis situes sur une trajectoire differente
    list<int> timersGenEnemy; // chaque element de cette liste correspond au timer d'apparition d'un ennemi sur la trajectoire de meme rang que cet 
			      // element dans la liste des trajectoires (ex : 1er timer de la liste <=> 1ere trajectoire de la liste des trajectoires)
    int timerGenShoot;
    int timerGenShootGros;
    int timerGenEnemy;

};

#endif
