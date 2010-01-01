#ifndef GAME_H_
#define GAME_H_

#include <list>
#include <vector>
#include <math.h>

#include "actor.h"
#include "camera.h"
#include "graphicEngine.h"
#include "parameters.h"
#include "enemy.h"
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
    void trajectoriesManager();
    void enemiesManager();
    void collisionManager();
    void gameManager();
    void pauseManager();


    vector<EnemyInfo> enemiesInfos;
    list<Trajectory> trajectories;
    list<ActorPhysique> friendFires;
    list<ActorPhysique> enemiesFires;
    ActorPlayer player;

    int timerGenShoot;
    int timerGenTrajectorySequence; // Correspond à l'intervalle de temps qui sépare l'apparition de 2 ennemis situes sur une trajectoire differente
    list<int> timersGenEnemy; // chaque element de cette liste correspond au timer d'apparition d'un ennemi sur la trajectoire de meme rang que cet 
			      // element dans la liste des trajectoires (ex : 1er timer de la liste <=> 1ere trajectoire de la liste des trajectoires)
    // int timerGenEnemy; // NOTE fait parti des attributs des trajectoires
    int timerGenShootGros;
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
    float dTime;
    bool stop;
    int widthView,heightView;

    bool pause;
    bool passagePause; //permet une bonne transition entre pause-!pause.
    bool resetCam; // savoir si on est en train de reinitialiser la camera ou pas.
    

};

#endif
