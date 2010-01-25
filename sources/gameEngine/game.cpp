#include "./game.h"



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


Game::~Game()
{
}

Game::Game() // construction des camera, du GE et des autre objets tell que les Mode, mais il seront reconstruit apres de toute maniere
{

    etatGame = MENU;
    switchMode = NONE;
    shad=POSTFX_NOTHING;

    // on abesoin du GE pour construire les models
    models = Models(&GE);

    // on initialise les different mode (etat) du jeu
    mMenu = ModeMenu(&models, &cam,&etatGame, &switchMode);
    mGame = ModeGame(&models, &cam,&etatGame, &switchMode);
    mPause = ModePause(&models, &cam,&etatGame, &switchMode);

    vect pFond={0,-3,0}, rFond= {0,0,0}, sFond={2,2,2}, vFond={0,0,2};
    fond = Fond(models.getMNuages(), models.getMSols(), pFond, rFond, sFond, vFond);

    srand( time(NULL) ); // un peu de random ne fait pas de mal (function.h, random())
	TTime=0;
}

void Game::resize(int width,int heigth)
{
    GE.resize(width,heigth);
}

void Game::update(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
{
    // les modes fonctionnent de la meme maniere, on passe les commandes et il gere, pour le rendu c'est Game qui recupere chaque objet du ou des mode a afficher
    //En ce qui concerne la commutation des modes:
    // de modeGame, on peut aller au menu ou en pause
    // de modePause, on ne peut retourner que au game
    // et du menu, on passe en mode game
    this->dTime=time;


    if (etatGame==MENU) {
        if (mGame.isEnd()) { // si on retourne au menu et que c'est la fin, on reinitialise
            mGame = ModeGame(&models, &cam,&etatGame, &switchMode);
        }
        mMenu.menuManager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height); // gere le menu, les options graphiques, et les autres trucs
    }
    else if (etatGame==GAME) {
        fond.update(dTime);
        mGame.gameManager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
    }
    else if (etatGame==PAUSE) {
        mPause.pauseManager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
    }
    else if (etatGame==OPTION) {
        cout << "XXXXXXXXX" << endl;
        etatGame = MENU;
    }
    if (stateKeys[K_PAUSE]) {
      if(!shad)
	      shad=1;
      else
	      shad*=2;
    }
    shad%=32;

    if (stateKeys[K_CTRL] && (stateKeys[K_QUIT] || stateKeys[K_QUIT_SECOND])) {
        etatGame=STOP;
    }
    render(); // a la fin on affiche tout
}

// fin de l'interface, debut des méthodes privés

void Game::render()
{
    // on recolte toute les instances afficher!
    vector<instance> instances2D;
    vector<instance> instances;
    vector<Actor> vActor;
    vector<Actor>::iterator itA;

    vector<instance>::iterator itInst;

    // le fond en premier pour la transparence.
    vActor = fond.getSols();
    for (itA=vActor.begin(); itA!=vActor.end(); itA++) { // sol en premier car c'est le premier niveau
        instances.push_back(itA->getInstance());
    }
    vActor = fond.getNuages();
    for (itA=vActor.begin(); itA!=vActor.end(); itA++) {
        instances.push_back(itA->getInstance());
    }
    if (etatGame==MENU) {
        mMenu.getRender(&instances,&instances2D);
        mGame.getRender(&instances,&instances2D); // pour Paul
    }
    else if (etatGame==GAME) {
        mGame.getRender(&instances,&instances2D);
    }
    else if (etatGame==PAUSE) {
        mGame.getRender(&instances,&instances2D);
        mPause.getRender(&instances,&instances2D);
    }

    //camera came2D={0,30,0,0,0,0,0,0,-1};//TODO si y'en a plus besoin, faut le virer
    camera came = {(-sin(cam.getLongitude())*cos(cam.getLatitude())*cam.getZoom()) + cam.getCenterX(), (sin(cam.getLatitude())*cam.getZoom())/* + camera.getCenterZ()*/, cos(cam.getLongitude())*cos(cam.getLatitude())*cam.getZoom() + cam.getCenterZ(), cam.getCenterX(), 0 , cam.getCenterZ(),0,1,0};

    lightVec light = {0.5,0.5,0.5,{0.05,0.05,0.05,1},{0.4,0.4,0.4,1},{0.8,0.8,0.8,1}};
	
	TTime+=dTime;//TODO faut peut etre le mettre ailleur
    GE.render(instances, came, instances2D, came , light, shad ,TTime);
}
