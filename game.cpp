#include "game.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>

/* le plan de jeu ce fait sur xz */

//     Y--------X
//     |
//     |
//     |
//     Z

// for trace during test , to kept
#include <iostream>
using namespace std;

Game::~Game()
{
    cout << endl; //a cause du compteur de missile, avant de quitter, il faut un seut de ligne
}

void Game::init()
{
    stop=false;
    pause=false;
    passagePause = false;
    resetCam=false;

    camera.init();
    GE.init();

    // Chargement des infos des ennemis
    // NOTE j'ai (normalement) fait en sorte qu'on n'ait pas à modifier le code si on rajoute un ennemi dans le fichier d'ennemis
    // TODO gerer plusieurs niveaux (2 fichiers par niveau : un "enem_lvl_<n°_du_niveau>.data" et un "traj_lvl_<n°_du_niveau>.data"
    // dans le dossier levels
    EnemyInfosFile eFile("levels/enem_lvl_default.data");
    string s;
    int h, idM;
    while(!eFile.isEnded()) {
	eFile.read(s);
	eFile.read(h);
	idM = GE.loadModel("meshes/"+s+".obj","textures/"+s+".png");
	enemiesInfos.push_back({idM,h});
	cout << "Enemy infos : (idModel = " << idM << ", Health = " << h << ") ... Loaded" << endl;
    }
	
    // Chargement des trajectoires
    TrajectoryFile tFile("levels/traj_lvl_default.data");
    if(!tFile.isEnded())
      tFile.read(trajectories); // On charge les trajectoires dans trajectories
      
      
    srand( time(NULL) ); // un peu de random ne fait pas de mal (function.h, random())

    // Chargement du modele du joueur et de son boulet
    Mplayer=GE.loadModel("meshes/player.obj","textures/player.png");
    Mboulet=GE.loadModel("meshes/boulet.obj","textures/boulet.png");

    player = ActorPlayer(Mplayer, {0,0,0}, {0,-90,0}, {1,1,1}, 2, 10/3);

    // timerGenEnemy=INTERVALE_TEMP_ENEMY; // NOTE cf game.h
    timerGenTrajectorySequence = INTERVALE_TEMP_TRAJECTORY_SEQUENCE;
    timerGenShoot = INTERVALE_TEMP_SHOOT;
    
    // On initialise les timers de generation d'ennemi à TIMER_OFF pour dire qu'ils sont désactivés au début
    for(int i=0; i<trajectories.size(); i++)
        timersGenEnemy.push_back(TIMER_OFF);
    timerGenShootGros=INTERVALE_TEMP_SHOOT_GROS;
}

void Game::resize(int width,int heigth)
{
    GE.resize(width,heigth);
}

void Game::update(bool stateKeys[], bool stateButtons[], QPoint deltaMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    this->stateKeys=stateKeys;
    this->stateButtons=stateButtons;
    this->deltaMouse=deltaMouse;
    this->deltaWheel=deltaWheel;
    this->dTime=time;
    this->widthView=width;
    this->heightView=height;
    this->width=NB_UNITY_WIDTH;
    this->height=NB_UNITY_HEIGHT;

    //NOTE c'est pas forcément la forme définitive mais ca correspond plus a ce que l'on avais dit.
    //NOTE C'est le fond qui bougera pour donner l'impression d'avancer
    if (!pause)
    { 
        playerManager();
        firesManager();
	trajectoriesManager();
        enemiesManager();
        //bonusManager();
        //decorManager();
        collisionManager(); //vérifie les collisions et detruie le vaisseau/missile/bonus si nécéssaire
    }
    gameManager(); // gere le menu, les options graphiques, et les autres trucs
    if (pause)
        pauseManager();

    //Pour le fun
    cout << (char)0x0D << friendFires.size() +  enemiesFires.size()<<" missile(s) " << flush;

    render();
}

// fin de l'interface, debut des méthodes privés

void Game::render()
{
    vector<instance> instances;
    instances.push_back(player.getInstance());

    list<Trajectory>::iterator it_traj;
    for(it_traj = trajectories.begin(); it_traj != trajectories.end(); it_traj++)
    {
      list<Enemy>::iterator it_enn;
      for(it_enn=it_traj->getEnemies().begin(); it_enn != it_traj->getEnemies().end(); it_enn++)
      {
	  instances.push_back(it_enn->getInstance());
      }
    }
    
    list<ActorPhysique>::iterator itAP;
    for (itAP=enemiesFires.begin(); itAP!= enemiesFires.end(); itAP++) {
        instances.push_back(itAP->getInstance());
    }
    for (itAP=friendFires.begin(); itAP!= friendFires.end(); itAP++) {
        instances.push_back(itAP->getInstance());
    }
        GE.render(instances, {-sin(camera.getLongitude())*cos(camera.getLatitude())*camera.getZoom(), sin(camera.getLatitude())*camera.getZoom(), cos(camera.getLongitude())*cos(camera.getLatitude())*camera.getZoom(), camera.getCenterX(), camera.getCenterZ(), 0,0,1,0} , {0.5,0.5,0.5,{0.05,0.05,0.05,1},{0.4,0.4,0.3,1},{0.9,0.8,0.8,1}},dTime);
}

/*
*NOTE j'ai fait une version un peu compliqué du déplacement du joueur pour montrer les possibilités de
* ActorPhysique. Cette simulation est physiquement correcte mais ne correpond pas du tout à ce qu'il y'a d'abitude
* dans les jeux. Cependant, je trouve le concept interressant, ça oblige le joueur à mieux anticiper ses
* trajectoires.
*/
void Game::playerManager()
{
    //player.setAcceleration( {0,0,0});
    if (stateKeys[K_LEFT]) // -x
        player.setAcceleration( {player.getAcceleration().x-5,player.getAcceleration().y,player.getAcceleration().z});
    if (stateKeys[K_RIGHT]) // +x
        player.setAcceleration( {player.getAcceleration().x+5,player.getAcceleration().y,player.getAcceleration().z});
    if (stateKeys[K_UP]) // +y
        player.setAcceleration( {player.getAcceleration().x,player.getAcceleration().y,player.getAcceleration().z-8});
    if (stateKeys[K_DOWN]) // -y
        player.setAcceleration( {player.getAcceleration().x,player.getAcceleration().y,player.getAcceleration().z+8});

    player.update(dTime);
    player.colisionBord(width,height); // donner une leger rotation au vaisseau 
    // TODO ameliorer definition des bords
    
    if ((((stateKeys[K_TIR]) || (stateButtons[B_LEFT])) and timerGenShoot<=0))
    {
        ActorPhysique fire;
        fire=ActorPhysique(Mboulet, {player.getPosition().x,player.getPosition().y,player.getPosition().z}, {0,0,0}, {0.05,0.05,0.05});
        fire.setVelocity( {player.getVelocity().x+random(-0.5,0.5),player.getVelocity().y,player.getVelocity().z-random(15,18)});
        fire.setAcceleration( {0,0,0});
        friendFires.push_back(fire);

        timerGenShoot=INTERVALE_TEMP_SHOOT;
    }
    if ((((stateKeys[K_TIR_SECOND]) || (stateButtons[B_RIGHT])) and timerGenShootGros<=0))
    {
	ActorPhysique fire;
	for (float f =-0.8;f<=0.8;f+=0.2)
	{
	  if (random(0,1) < 0.9) {
	    fire=ActorPhysique(Mboulet, {player.getPosition().x+0.3,player.getPosition().y,player.getPosition().z+f}, {0,0,0}, {0.05,0.05,0.05});
	    fire.setVelocity( {player.getVelocity().x+random(15,18),player.getVelocity().y,/*player.getVelocity().z+*/random(-0.5,0.5)});
	    friendFires.push_back(fire);
	  }
	  if (random(0,1) < 0.9) {
	    fire=ActorPhysique(Mboulet, {player.getPosition().x-0.3,player.getPosition().y,player.getPosition().z+f}, {0,0,0}, {0.05,0.05,0.05});
	    fire.setVelocity( {player.getVelocity().x-random(15,18),player.getVelocity().y,/*player.getVelocity().z+*/random(-0.5,0.5)});
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

void Game::firesManager()
{
    list<ActorPhysique>::iterator it;

    for (it=friendFires.begin(); it!=friendFires.end(); it++) {
        it->update(dTime);
    }
    for (it=enemiesFires.begin(); it!=enemiesFires.end(); it++) {
        it->update(dTime);
    }
}

void Game::trajectoriesManager() {
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

void Game::enemiesManager()
{
    list<Trajectory>::iterator it_traj = trajectories.begin();
    list<int>::iterator it_gene = timersGenEnemy.begin();
    for(int i = 0; i<timersGenEnemy.size(); i++)
    {
      // On met a jour la position de chacun des ennemis presents sur la trajectoire
      list<Enemy>::iterator it_enn;
      for(it_enn = it_traj->getEnemies().begin(); it_enn < it_traj->getEnemies().end(); it_enn++)
	it_enn->update(dTime);
      if(it_traj->getRecordNumbers().size() && *it_gene <=0)
      {
	int rec_num = *(it_traj->getRecordNumbers().begin());
	Enemy e(enemiesInfos[rec_num].idModel,it_traj->getInitialPosition(),{0,0,0},{1,1,1},it_traj,enemiesInfos[rec_num].health);
	it_traj->addEnemy(e);
	it_traj->removeFirstRecordNumber(); // On enleve le numero d'enregistrement pour dire qu'on a bien cree l'ennemi
	*it_gene = it_traj->getInterval();
      }
      else
	*it_gene = *it_gene - 1;
      it_traj++;
      it_gene++;
    }
}

void Game::collisionManager()
{
    //pour l'instant ne sert a virer les objets sortant du cadre
    // si on rentre en collision avec la bordure exterieur on efface l'object

    list<Trajectory>::iterator it_traj;
    for(it_traj = trajectories.begin(); it_traj != trajectories.end(); it_traj++)
    {
      list<Enemy>::iterator it_enn;
      it_enn = it_traj->getEnemies().begin();
      while(it_enn != it_traj->getEnemies().end())
      {
	if (it_enn->sortieEcran(width+5,height+5))
	  it_enn = it_traj->getEnemies().erase(it_enn); // On efface l'element et on pointe sur le suivant (donc pas besoin de faire un it_enn++)
	else
	  it_enn++;
      }
    }
/* ---------------------Sauvegarde de l'ancienne version---------------------------
    
    //HACK c'est la chose la plus moche que j'ai jamais faite, mais pour l'instant, j'arrive pas a faire mieux
    //NOTE Pourquoi (paul) as tu mis une bouche while autour du for ? je comprend vraiment pas !
    //NOTE C'est pas si horrible (sans le while) tu parcour toute les enemi (et fires) en verifiant s'il sont hors jeu our pas !
    //NOTE (romain) En fait il me semble que sans le while tu dois pouvoir supprimer qu'un seul ennemi a la fois parce que tu break au
    // premier ennemi supprime
//     while (ite!=enemies.end())
//     {
    list<ActorPhysique>::iterator itAP;
    for (itAP=enemies.begin(); itAP!=enemies.end() ; itAP++) {
        if (itAP-> sortieEcran(width+5,height+5))
        {
            enemies.erase(itAP);
            break;
        }
    }
//     }
-------------------------------------------------------------------------------*/

    list<ActorPhysique>::iterator itf;
    itf=friendFires.begin();
    while (itf!=friendFires.end())
    {
        if (itf->sortieEcran(width+5,height+5))
	  itf = friendFires.erase(itf);
	else
	  itf++;
    }
/* ---------------------Sauvegarde de l'ancienne version---------------------------
//     while (itf!=fires.end())
//     {
    for (itAP=friendFires.begin(); itAP!=friendFires.end() ; itAP++)
    {
        if (itAP-> sortieEcran(width+5,height+5))
        {
            friendFires.erase(itAP);
            break;
        }
    }
//     }
-------------------------------------------------------------------------------*/

    // TODO ameliorer definition des bords
    //verification des bords verticaux ensuite des bords horizontaux. (evite de sortir sur les coins.)
    if (player.getPosition().x<-width)
    for (itAP=enemiesFires.begin(); itAP!=enemiesFires.end() ; itAP++)
    {
        if (itAP-> sortieEcran(width+5,height+5))
        {
            enemiesFires.erase(itAP);
            break;
        }
    }
}

void Game::gameManager()
{
    // si on saure de pause, on reset la camera de facon douce, elegante jusqu'a ce que la camera ai sa position initial.
    if (passagePause && (!camera.camOK()) && pause) {
        camera.resetSmart();
    }
    // Si on est en transition et que la touche pause est relaché, alors fini transition
    if (passagePause && ((!stateKeys[K_PAUSE]) && (camera.camOK()))) {
        passagePause = false;
        pause= (!pause); // seulement une fois que la transition est fini, on change l'etat.
       // TODO leger pause avant de reprendre le jeu (sleep ne marche pas ici ni ailleur dans game).
    }
    // Si on est pas en transition et que touche pause est appuyé, alors on passe en transition (et en pause ou !pause)
    if (!passagePause && stateKeys[K_PAUSE]) {
        passagePause = true;
    }
    //Si on appuie sur echap, on passe pas par la case menu, on quitte direct
    if (stateKeys[K_QUIT])
        stop=true;
}

// Lors du zoom ou des translation, c'est la camera qui bouge, lors des rotation, c'est la scene.
//NOTE Toute les valeur ici sont prisent "au hasard" (0.05,0.02 ...) peut etre trouver des relation avec des nombre representant quelques choses pour nous !?
//TODO lors du changement de centre afficher un plan xy (avec alpha) et un curseur ce "baladant" dessus de facons a bien indiquer le centre.
void Game::pauseManager() // TODO acceleration
{
    if (resetCam) {
        camera.resetSmart();
        if (camera.camOK())
            resetCam=false;
    }
    else if (stateKeys[K_CTRL]) {
        if (stateKeys[K_UP]) {
            camera.setZoom(-0.05);
        }
        else if (stateKeys[K_DOWN]) {
            camera.setZoom(0.05);
        }
        else if ((stateKeys[K_LEFT]) && (stateKeys[K_RIGHT])) {
            resetCam=true;
            camera.resetSmart();
            if (camera.camOK())
                resetCam=false;
        }
    }

    else if (stateKeys[K_SHIFT]) {
        if (stateKeys[K_UP]) {
            camera.setCenterZ(-0.05); // axe Z ver le "bas"
        }
        else if  (stateKeys[K_DOWN]) {
            camera.setCenterZ(0.05);
        }
        if (stateKeys[K_LEFT]) {
            camera.setCenterX(-0.05);
        }
        else if (stateKeys[K_RIGHT]) {
            camera.setCenterX(0.05);
        }
        if ((deltaWheel != 0)) {
            camera.setZoom(-deltaWheel/(float)240);
        }
    }

    else {
        //>=2 ou <= -2 pour la sensibiliter -> en 20ms, la souris a parcouru plus de 2 ou moin de -2 pixels (Delta).
        if ((stateButtons[B_LEFT]) && ((deltaMouse.y() >= 2 || deltaMouse.y() <= -2))) {
            camera.setCenterZ(-deltaMouse.y()*0.02);
        }
        if ((stateButtons[B_LEFT]) && ((deltaMouse.x() >= 2 || deltaMouse.x() <= -2))) {
            camera.setCenterX(deltaMouse.x()*0.02);
        }
        if ((stateButtons[B_MIDLE]) && ((deltaMouse.y() >= 2 || deltaMouse.y() <= -2))) {
            camera.setLatitude(0.01*deltaMouse.y());
        }
        if ((stateButtons[B_MIDLE]) && ((deltaMouse.x() >= 2 || deltaMouse.x() <= -2))) {
            camera.setLongitude(0.01*deltaMouse.x());
        }
        if ((deltaWheel != 0)) {
            camera.setZoom(-deltaWheel/(float)60);
        }
        if (stateKeys[K_UP])
            camera.setLatitude(0.02);
        if (stateKeys[K_DOWN])
            camera.setLatitude(-0.02);
        if (stateKeys[K_LEFT])
            camera.setLongitude(0.02);
        if (stateKeys[K_RIGHT])
            camera.setLongitude(-0.02);
    }
}
