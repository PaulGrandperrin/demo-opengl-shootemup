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
extern Parameters * parametre;


Game::~Game()
{
    SE.stop("sounds/ocean.wav");
    SE.stop("sounds/blackpearl.wav");
}

Game::Game():SE() // construction des camera, du GE et des autre objets tell que les Mode, mais il seront reconstruit apres de toute maniere
{

    SE.load("sounds/ocean.wav");
    SE.load("sounds/blackpearl.wav");
    SE.load("sounds/Bamboo.wav");
    SE.load("sounds/Bleep.wav");
    etatGame = MENU;
    switchMode = NONE;
    shad=POSTFX_BLUR;
    changePostFX = false;
    // on abesoin du GE pour construire les models
    models = Models(&GE);
    // on initialise les different mode (etat) du jeu
    mMenu = ModeMenu(&models, &cam,&etatGame, &switchMode,&SE);
    mGame = ModeGame(&models, &cam,&etatGame, &switchMode,&SE);
    mPause = ModePause(&models, &cam,&etatGame, &switchMode);
    mAbout = ModeAbout(&models, &cam,&etatGame, &switchMode);
    mOption = ModeOption(&models, &cam,&etatGame, &switchMode);
    vect pFond={0,-3,0}, rFond= {0,0,0}, sFond={1.6,1.6,1.6}, vFond={0,0,2.5};
    fond = Fond(models.getMNuages(), models.getMSol(), pFond, rFond, sFond, vFond);


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
    TTime+=dTime;// Pour le moteur 3D !

    if (etatGame==MENU) {
        if (mGame.isEnd()) { // si on retourne au menu et que c'est la fin, on reinitialise
            mGame = ModeGame(&models, &cam,&etatGame, &switchMode,&SE);
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
        mOption.optionManager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
    }
    else if (etatGame==ABOUT) {
        mAbout.aboutManager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
    }
    effectManager(stateKeys);

    if (stateKeys[parametre->getCtrl()] && (stateKeys[parametre->getQuit()] || stateKeys[parametre->getQuitSecond()])) {
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
    else if (etatGame==ABOUT) {
        mAbout.getRender(&instances,&instances2D);
    }
    else if (etatGame==OPTION) {
        mOption.getRender(&instances,&instances2D);
    }

    camera came2D={0,30,0,0,0,0,0,0,-1};//TODO si y'en a plus besoin, faut le virer >> biensure que si yen a besoin !
    camera came = {(-sin(cam.getLongitude())*cos(cam.getLatitude())*cam.getZoom()) + cam.getCenterX(), (sin(cam.getLatitude())*cam.getZoom())/* + camera.getCenterZ()*/, cos(cam.getLongitude())*cos(cam.getLatitude())*cam.getZoom() + cam.getCenterZ(), cam.getCenterX(), 0 , cam.getCenterZ(),0,1,0};

    lightVec light = {0.5,0.5,0.5,{0.12,0.12,0.1,0.2},{0.4,0.4,0.25,0.2},{0.4,0.4,0.2,0.1}};

    GE.render(instances, came, instances2D, came2D , light, shad ,TTime);
}

void Game::effectManager(bool stateKeys[]) {
    if (stateKeys[parametre->getPause()] && !changePostFX) {
        changePostFX = true;
    }
    if (!stateKeys[parametre->getPause()] && changePostFX) {
        if (!shad)
            shad=1;
        else
            shad*=2;
        changePostFX = false;
    }
    shad%=32;

    if (switchMode == TOGAME || switchMode == TOPAUSE || mGame.isEnd()) {
        shad = POSTFX_NOTHING;
    }
    if (switchMode == TOMENU) {
        shad = POSTFX_BLUR;
    }

    // le player a ete touché, on brouille la camera, pendant TEMP_BROUILLAGE_CAM_PLAYER_HEARTH
    if (mGame.getplayerHeart() == TEMP_BROUILLAGE_CAM_PLAYER_HEARTH || mGame.getplayerHeart() == TEMP_BROUILLAGE_CAM_PLAYER_HEARTH_LONG) {
        mGame.changePlayerHeart(-1);
        shad = POSTFX_WATER;
    }
    if ((mGame.getplayerHeart() == TEMP_BROUILLAGE_CAM_PLAYER_HEARTH_MISSILE) && (shad != POSTFX_WATER)) // toucher par un enemi
    {
        mGame.changePlayerHeart(-1);
        shad = POSTFX_BLUR;
    }
    else if (mGame.getplayerHeart() > 1) {
        mGame.changePlayerHeart(-1);
    }
    else if (mGame.getplayerHeart() == 1) {
        mGame.changePlayerHeart(-1);
        shad = POSTFX_NOTHING;
    }
}
