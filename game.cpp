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

    srand( time(NULL) ); // un peu de random ne fait pas de mal (function.h, random())

    //TODO charger le fichier de niveau et les trajectoire ici

    Mplayer=GE.loadModel("meshes/player.obj","textures/player.png");
    Mboulet=GE.loadModel("meshes/boulet.obj","textures/boulet.png");
    MCursorPause=GE.loadModel("meshes/cursorPause.obj","textures/boulet.png");

    player = ActorPlayer(Mplayer, {0,0,0}, {0,-90,0}, {1,1,1}, 2, 10/3);
    
    timerGenEnemy=INTERVALE_TEMP_ENEMY;
    timerGenShoot=INTERVALE_TEMP_SHOOT;
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
    list<ActorPhysique>::iterator itAP;
    instances.push_back(player.getInstance());
    for (itAP=enemies.begin(); itAP!= enemies.end(); itAP++) {
        instances.push_back(itAP->getInstance());
    }
    for (itAP=enemiesFires.begin(); itAP!= enemiesFires.end(); itAP++) {
        instances.push_back(itAP->getInstance());
    }
    for (itAP=friendFires.begin(); itAP!= friendFires.end(); itAP++) {
        instances.push_back(itAP->getInstance());
    }
    if (pause) {
	instances.push_back(cursorPause.getInstance());
    }
    GE.render(instances, {(-sin(camera.getLongitude())*cos(camera.getLatitude())*camera.getZoom()) + camera.getCenterX(), (sin(camera.getLatitude())*camera.getZoom())/* + camera.getCenterZ()*/, cos(camera.getLongitude())*cos(camera.getLatitude())*camera.getZoom() + camera.getCenterZ(), camera.getCenterX(), 0 , camera.getCenterZ(),0,1,0} , {0.5,0.5,0.5,{0.05,0.05,0.05,1},{0.4,0.4,0.3,1},{0.9,0.8,0.8,1}},dTime);
}

/*
*NOTE j'ai fait une version un peu compliqué du déplacement du joueur pour montrer les possibilités de
* ActorPhysique. Cette simulation est physiquement correcte mais ne correpond pas du tout à ce qu'il y'a d'abitude
* dans les jeux. Cependant, je trouve le concept interressant, ça oblige le joueur à mieux anticiper ses
* trajectoires.
*/
void Game::playerManager()
{
    player.setAcceleration( {0,0,0});
    if (stateKeys[K_LEFT]) // -x
        player.setAcceleration( {player.getAcceleration().x-10,player.getAcceleration().y,player.getAcceleration().z});
    if (stateKeys[K_RIGHT]) // +x
        player.setAcceleration( {player.getAcceleration().x+10,player.getAcceleration().y,player.getAcceleration().z});
    if (stateKeys[K_UP]) // +y
        player.setAcceleration( {player.getAcceleration().x,player.getAcceleration().y,player.getAcceleration().z-20});
    if (stateKeys[K_DOWN]) // -y
        player.setAcceleration( {player.getAcceleration().x,player.getAcceleration().y,player.getAcceleration().z+20});

    player.update(dTime);
    // TODO ameliorer definition des bords
    
    if ((((stateKeys[K_TIR]) || (stateButtons[B_LEFT])) and timerGenShoot<=0))
    {
        ActorPhysique fire;
        fire=ActorPhysique(Mboulet, {player.getPosition().x,player.getPosition().y,player.getPosition().z}, {0,0,0}, {0.05,0.05,0.05});
        fire.setVelocity( {player.getVelocity().x/3+random(-0.5,0.5),player.getVelocity().y/3,player.getVelocity().z/3-random(15,18)});
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
	    fire.setVelocity( {player.getVelocity().x/3+random(15,18),player.getVelocity().y/3,player.getVelocity().z/5+random(-0.5,0.5)});
	    friendFires.push_back(fire);
	  }
	  if (random(0,1) < 0.9) {
	    fire=ActorPhysique(Mboulet, {player.getPosition().x-0.3,player.getPosition().y,player.getPosition().z+f}, {0,0,0}, {0.05,0.05,0.05});
	    fire.setVelocity( {player.getVelocity().x/3-random(15,18),player.getVelocity().y/3,player.getVelocity().z/5+random(-0.5,0.5)});
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

void Game::enemiesManager()
{
    list<ActorPhysique>::iterator it;
    for (it=enemies.begin(); it!=enemies.end(); it++) {
        it->update(dTime);
    }
}

void Game::collisionManager()
{
    //pour l'instant ne sert a virer les objets sortant du cadre
    // si on rentre en collision avec la bordure exterieur on efface l'object
    player.colisionBord(width,height); // donner une leger rotation au vaisseau 
    
    list<ActorPhysique>::iterator itAP;
    for (itAP=enemies.begin(); itAP!=enemies.end() ; itAP++) {
        if (itAP-> sortieEcran(width+5,height+5))
        {
            enemies.erase(itAP);
            break;
        }
    }
    for (itAP=friendFires.begin(); itAP!=friendFires.end() ; itAP++)
    {
        if (itAP-> sortieEcran(width+5,height+5))
        {
            friendFires.erase(itAP);
            break;
        }
    }
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
      if (!pause) cursorPause = Actor(MCursorPause, {0,0,0}, {0,0,0}, {1.0,1.0,1.0});
        passagePause = false;
        pause= (!pause); // seulement une fois que la transition est fini, on change l'etat.
       // TODO leger pause avant de reprendre le jeu (sleep ne marche pas ici ni ailleur dans game).
    }
    // Si on est pas en transition et que touche pause est appuyé, alors on passe en transition (et en pause ou !pause)
    if (!passagePause && stateKeys[K_PAUSE]) {
        passagePause = true;
    }
    //Si on appuie sur echap, on passe pas par la case menu, on quitte direct
    if (stateKeys[K_CTRL] && (stateKeys[K_QUIT] || stateKeys[K_QUIT_SECOND]))
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
	    cursorPause.translate({0,0,-0.05});
        }
        else if  (stateKeys[K_DOWN]) {
            camera.setCenterZ(0.05);
	    cursorPause.translate({0,0,0.05});
        }
        if (stateKeys[K_LEFT]) {
            camera.setCenterX(-0.05);
	    cursorPause.translate({-0.05,0,0});
        }
        else if (stateKeys[K_RIGHT]) {
            camera.setCenterX(0.05);
	    cursorPause.translate({0.05,0,0});
        }
        if ((deltaWheel != 0)) {
            camera.setZoom(-deltaWheel/(float)240);
        }
	if ((stateButtons[B_LEFT]) && ((deltaMouse.y() >= 2 || deltaMouse.y() <= -2))) {
            camera.setCenterZ(deltaMouse.y()*NB_UNITY_HEIGHT/(float)TAILLE_DEFAULT_Y);
	    cursorPause.translate({0,0,(deltaMouse.y()*NB_UNITY_HEIGHT/(float)TAILLE_DEFAULT_Y)});
        }
        if ((stateButtons[B_LEFT]) && ((deltaMouse.x() >= 2 || deltaMouse.x() <= -2))) {
            camera.setCenterX(deltaMouse.x()*NB_UNITY_WIDTH/(float)TAILLE_DEFAULT_X);
	    cursorPause.translate({(deltaMouse.x()*NB_UNITY_WIDTH/(float)TAILLE_DEFAULT_X)});
        }
    }

    else {
        //>=2 ou <= -2 pour la sensibiliter -> en 20ms, la souris a parcouru plus de 2 ou moin de -2 pixels (Delta).
        if ((stateButtons[B_LEFT]) && ((deltaMouse.y() >= 2 || deltaMouse.y() <= -2))) {
            camera.setCenterZ(deltaMouse.y()*NB_UNITY_HEIGHT*5/(float)TAILLE_DEFAULT_Y);
	    cursorPause.translate({0,0,(deltaMouse.y()*NB_UNITY_HEIGHT*5/(float)TAILLE_DEFAULT_Y)});
        }
        if ((stateButtons[B_LEFT]) && ((deltaMouse.x() >= 2 || deltaMouse.x() <= -2))) {
            camera.setCenterX(deltaMouse.x()*NB_UNITY_WIDTH*5/(float)TAILLE_DEFAULT_X);
	    cursorPause.translate({(deltaMouse.x()*NB_UNITY_WIDTH*5/(float)TAILLE_DEFAULT_X)});
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
