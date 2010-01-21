#include "modeGame.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <sstream>

/* le plan de jeu ce fait sur xz */

//     Y--------X
//     |
//     |
//     |
//     Z

// for trace during test , to kept
#include <iostream>
using namespace std;




ModeGame::~ModeGame()
{
    cout << endl; //a cause du compteur de missile, avant de quitter, il faut un seut de ligne
}

void ModeGame::init(Models* models, Etat* etatGame)
{
    Mode::init(models, etatGame);
    int intHealth = HEALTH_PLAYER;
    vect pPlayer={0,0,0}, rPlayer= {0,-90,0}, sPlayer={1,1,1};
    player = ActorPlayer(models->getMplayer(), pPlayer, rPlayer, sPlayer, intHealth ,0.4);
    
    vect pScore={-12.5,0,-11}, rScore= {0,0,0}, sScore={1,1,0.5};
    score = Score(models->getMChiffres(), 0, pScore, rScore, sScore, 0.6, LEFT); // test des chiffres
    
    vect pLeScore={-12.5,0,-12}, rLeScore= {0,0,0}, sLeScore={0.8,0.8,0.5};
    tScore = Text(models->getMChiffres(),models->getMLettersM(), "Score", pLeScore, rLeScore, sLeScore, 0.6, LEFT); // test du text, pour l'instant "abcde"

    vect pVie={12.5,0,-11}, rVie= {0,0,0}, sVie={1,1,0.5};
    health = Health(models->getMChiffres(), intHealth , pVie, rVie, sVie, 0.6, RIGHT); // test des chiffres
    
    vect pLaVie={12.5,0,-12}, rLaVie= {0,0,0}, sLaVie={0.8,0.8,0.5};
    tHealth = Text(models->getMChiffres(),models->getMLettersM(), "Health", pLaVie, rLaVie, sLaVie, 0.6, RIGHT); // test du text, pour l'instant "abcde"
    
    timerGenEnemy=INTERVALE_TEMP_ENEMY;
    timerGenShoot=INTERVALE_TEMP_SHOOT;
    timerGenShootGros=INTERVALE_TEMP_SHOOT_GROS;
    timerGenTrajectorySequence = INTERVALE_TEMP_TRAJECTORY_SEQUENCE;
    
    // Chargement des trajectoires
    TrajectoryFile tFile("levels/traj_lvl_default.data");
    if(!tFile.isEnded()) {
      tFile.read(trajectories); // On charge les trajectoires dans trajectories
    } else {
      cout << "Trajectory file not found !" << endl;
      exit(0);
    }
      
    // On initialise les timers de generation d'ennemi à TIMER_OFF pour dire qu'ils sont désactivés au début
    int traj_list_size = trajectories.size();
    for(int i=0; i<traj_list_size; i++)
        timersGenEnemy.push_back(TIMER_OFF);
}


void ModeGame::gameManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    Mode::Manager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);

    playerManager();
    firesManager();
    trajectoriesManager();
    enemiesManager();
    //bonusManager();
    //decorManager();
    collisionManager(); //vérifie les collisions et detruie le vaisseau/missile/bonus si nécéssaire


    //Pour le fun
    cout << (char)0x0D << friendFires.size() +  enemiesFires.size()<<" missile(s) " << flush;

}


void ModeGame::getRender(vector<instance>* instances) {

    // on recupere toute les instances a afficher
    vector<Actor> text;
    vector<Actor>::iterator itA;
    list<ActorPhysique>::iterator itAP;

    instances->push_back(player.getInstance());
    list<Trajectory>::iterator it_traj;
    //NOTE La boucle qui suit semble ne pas fonctionner !!!
    for(it_traj = trajectories.begin(); it_traj != trajectories.end(); it_traj++)
    {
      list<ActorEnemy>::iterator it_enn;
      list<ActorEnemy> enemies = it_traj->getEnemies();
      for(it_enn=enemies.begin(); it_enn != enemies.end(); it_enn++)
      {
	  instances->push_back(it_enn->getInstance());
      }
    }
    for (itAP=enemiesFires.begin(); itAP!= enemiesFires.end(); itAP++) {
        instances->push_back(itAP->getInstance());
    }
    for (itAP=friendFires.begin(); itAP!= friendFires.end(); itAP++) {
        instances->push_back(itAP->getInstance());
    }

    if (*etatGame == GAME) {
        // on affiche le score ..., et autre info
        text = score.getText();
        for (itA=text.begin(); itA!=text.end(); itA++) {
            instances->push_back(itA->getInstance());
        }
        text = tScore.getText();
        for (itA=text.begin(); itA!=text.end(); itA++) {
            instances->push_back(itA->getInstance());
        }
	text = health.getText();
        for (itA=text.begin(); itA!=text.end(); itA++) {
            instances->push_back(itA->getInstance());
        }
        text = tHealth.getText();
        for (itA=text.begin(); itA!=text.end(); itA++) {
            instances->push_back(itA->getInstance());
        }
    }
}
/*
*NOTE j'ai fait une version un peu compliqué du déplacement du joueur pour montrer les possibilités de
* ActorPhysique. Cette simulation est physiquement correcte mais ne correpond pas du tout à ce qu'il y'a d'abitude
* dans les jeux. Cependant, je trouve le concept interressant, ça oblige le joueur à mieux anticiper ses
* trajectoires.
*/
void ModeGame::playerManager()
{
//     player.setAcceleration( {0,0,0});
    vect accl={0,0,0};
    if (stateKeys[K_LEFT]) // -x
	accl.x-=10;
        player.setAcceleration( accl );
    if (stateKeys[K_RIGHT]) // +x
	accl.x+=10;
        player.setAcceleration( accl);
    if (stateKeys[K_UP]) // +y
	accl.z-=20;
        player.setAcceleration( accl);
    if (stateKeys[K_DOWN]) // -y
      	accl.z+=20;
        player.setAcceleration( accl);

    player.update(dTime);
    // TODO ameliorer definition des bords

    vect p={player.getPosition().x,player.getPosition().y,player.getPosition().z}, r={0,0,0}, s={0.1,0.1,0.1};
    vect pLeft={player.getPosition().x-0.3,player.getPosition().y,player.getPosition().z};
    vect pRight={player.getPosition().x+0.3,player.getPosition().y,player.getPosition().z};
    vect vel={player.getVelocity().x/3,player.getVelocity().y/3,player.getVelocity().z/3};
    
    if ((((stateKeys[K_TIR]) || (stateButtons[B_LEFT])) and timerGenShoot<=0))
    {
        ActorPhysique fire;
	vel.x += random(-0.5,0.5);
	vel.z -= random(15,18);
        fire=ActorPhysique(models->getMboulet(), p, r, s);
        fire.setVelocity( vel );
        friendFires.push_back(fire);

        timerGenShoot=INTERVALE_TEMP_SHOOT;
    }
    if ((((stateKeys[K_TIR_SECOND]) || (stateButtons[B_RIGHT])) and timerGenShootGros<=0))
    {
        ActorPhysique fire;
        for (float f =-0.8;f<=0.8;f+=0.2)
        {
            if (random(0,1) < 0.9) {
		vel.x = 0; vel.z = 0;
// 	        pRight.x=player.getPosition().x+0.3;
		pRight.z=player.getPosition().z+f;
		vel.x += random(15,18);
		vel.z += random(-0.5,0.5);
                fire=ActorPhysique(models->getMboulet(), pRight, r, s);
                fire.setVelocity( vel);
                friendFires.push_back(fire);
            }
            if (random(0,1) < 0.9) {
		vel.x = 0; vel.z = 0;
// 	        pLeft.x=player.getPosition().x+0.3;
		pLeft.z=player.getPosition().z+f;
		vel.x -= random(15,18);
		vel.z += random(-0.5,0.5);
                fire=ActorPhysique(models->getMboulet(),pLeft, r, s);
                fire.setVelocity( vel);
                friendFires.push_back(fire);
            }
        }
        timerGenShootGros=INTERVALE_TEMP_SHOOT_GROS;
    }
    else {
        timerGenShoot--;
        timerGenShootGros--;
    }
}

void ModeGame::firesManager()
{
    list<ActorPhysique>::iterator it;

    for (it=friendFires.begin(); it!=friendFires.end(); it++) {
        it->update(dTime);
    }
    for (it=enemiesFires.begin(); it!=enemiesFires.end(); it++) {
        it->update(dTime);
    }
}


void ModeGame::trajectoriesManager() {
  bool timerGenEnemyStarted = FALSE;
  bool timerOffMet = FALSE; // Booleen pour savoir s'il est toujours utile de faire une decrementation du timer (s'il reste des sequences à demarrer)
  list<Trajectory>::iterator it_traj = trajectories.begin();
  list<int>::iterator it_gene = timersGenEnemy.begin();
  // On parcourt les trajectoires pour supprimer celles qui n'ont plus d'ennemis, et pour démarrer la génération des ennemis de chaque trajectoire
  // de facon ordonnée (ex : on démarre la première trajectoire, puis au prochain top, on en démarre une autre...)
  while(it_traj != trajectories.end())
  {
    // Si tous les ennemis ont ete generes et qu'il n'en reste plus, alors on supprime la trajectoire et son timer
    if(it_traj->getRecordNumbers().size() == 0 && it_traj->getEnemies().size() == 0) {
      it_traj = trajectories.erase(it_traj);
      it_gene = timersGenEnemy.erase(it_gene);
    }
    else {
      if(*it_gene == TIMER_OFF)
      {
	if(timerGenTrajectorySequence <= 0) {
	  *it_gene = it_traj->getInterval(); // On demarre le timer d'ennemis de cette trajectoire en quelque sorte
	  timerGenTrajectorySequence = INTERVALE_TEMP_TRAJECTORY_SEQUENCE;
	  timerGenEnemyStarted = TRUE;
	}
	timerOffMet = TRUE;
      }
      it_traj++;
      it_gene++;
    }
  }
  if(timerOffMet && timerGenTrajectorySequence > 0 && !timerGenEnemyStarted)
    timerGenTrajectorySequence--;
}

void ModeGame::enemiesManager()
{
    list<Trajectory>::iterator it_traj = trajectories.begin();
    list<int>::iterator it_gene = timersGenEnemy.begin();
    for(int i = 0; i<(int)timersGenEnemy.size(); i++)
    {
      // On met a jour la position de chacun des ennemis presents sur la trajectoire
      list<ActorEnemy>::iterator it_enn;
      list<ActorEnemy> enemies = it_traj->getEnemies();
      for(it_enn = enemies.begin(); it_enn != enemies.end(); it_enn++) {
	it_enn->update(dTime);
      }
      it_traj->setEnemies(enemies);
      if(it_traj->getRecordNumbers().size() && *it_gene <=0)
      {
	int rec_num = *(it_traj->getRecordNumbers().begin());
	ActorEnemy e(models->getEnemiesInfos()[rec_num].idModel,it_traj->getInitialPosition(),{0,0,0},{1,1,1},&(*it_traj),models->getEnemiesInfos()[rec_num].health);
	it_traj->addEnemy(e);
	it_traj->removeFirstRecordNumber(); // On enleve le numero d'enregistrement pour dire qu'on a bien cree l'ennemi
	*it_gene = it_traj->getInterval();
      }
      else
	*it_gene = *it_gene - 1;
      it_traj++;
      it_gene++;
    }
    if (timersGenEnemy.empty()) {
	cout << " Fini " << endl;
	*etatGame = MENU;
    }
}

void ModeGame::collisionManager()
{
    //pour l'instant ne sert a virer les objets sortant du cadre
    // si on rentre en collision avec la bordure exterieur on efface l'object
    player.colisionBord(width,height); // donner une leger rotation au vaisseau

    list<Trajectory>::iterator it_traj;
    for(it_traj = trajectories.begin(); it_traj != trajectories.end(); it_traj++)
    {
      list<ActorEnemy> enemies = it_traj->getEnemies();
      list<ActorEnemy>::iterator it_enn;
      it_enn = enemies.begin();
      while(it_enn != enemies.end())
      {
	if (it_enn->sortieEcran(width+5,height+5)) {
	  it_enn = enemies.erase(it_enn); // On efface l'element et on pointe sur le suivant (donc pas besoin de faire un it_enn++)
	}else {
	  it_enn->colisionPlayer(&player);
	  it_enn->colisionFires(&friendFires);
	  if (it_enn->isMort()) {
	    it_enn = enemies.erase(it_enn); // On efface l'element et on pointe sur le suivant (donc pas besoin de faire un it_enn++)
	    score.setScore(models->getMChiffres(),10);
	  }
	  else
	    it_enn++;
	}
      }
      it_traj->setEnemies(enemies);
    }
    list<ActorPhysique>::iterator itAP;
    itAP = friendFires.begin();
    while(itAP!=friendFires.end())
    {
        if (itAP-> sortieEcran(width+5,height+5))
          itAP = friendFires.erase(itAP);
	else
	  itAP++;
    }
    itAP=enemiesFires.begin();
    while(itAP!=enemiesFires.end())
    {
        if (itAP-> sortieEcran(width+5,height+5))
          itAP = enemiesFires.erase(itAP);
        else
	  itAP++;
    }
    
    if (player.isMort()) {
	cout << " Player  Mort " << endl;
	*etatGame = MENU;
    }
    health.setHealth(models->getMChiffres(), player.getHealth());
}
