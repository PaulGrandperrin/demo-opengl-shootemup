#ifndef MODEGAME_H_
#define MODEGAME_H_

#include <list>
#include <math.h>

#include "./mode.h"


class ModeGame : public Mode
{
public:
    ~ModeGame();
    ModeGame() {}
    ModeGame(Models* models, Camera* camera,Etat* etatGame, SwitchEtat* switchMode);
    void gameManager(bool stateKeys[],  bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height);

    void getRender(vector<instance>* instances);
    bool isEnd() {
        return end;
    }

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
    Score score;
    Text tScore;
    Health health;
    Text tHealth;
    Text tEnd;

    bool end;
    bool toEnd;

    int timerGenTrajectorySequence; // Correspond à l'intervalle de temps qui sépare l'apparition de 2 ennemis situes sur une trajectoire differente
    list<int> timersGenEnemy; // chaque element de cette liste correspond au timer d'apparition d'un ennemi sur la trajectoire de meme rang que cet
    // element dans la liste des trajectoires (ex : 1er timer de la liste <=> 1ere trajectoire de la liste des trajectoires)
    int timerGenShoot;
    int timerGenShootGros;
    int timerGenEnemy;

};

#endif
