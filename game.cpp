#include "game.h"
#include "function.h"
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

void Game::init()
{
    etatGame = MENU;
    passagePause = false;
    passageMenu = false;

    cam.init();
    GE.init();

    models.chargerModels(&GE);

    // on initialise les different mode (etat) du jeu
    menu.init(&models,&etatGame);
    gamePlay.init(&models,&etatGame);
    pause.init(&models, &cam,&etatGame);

    srand( time(NULL) ); // un peu de random ne fait pas de mal (function.h, random())
    
    //oldMouse.x=0.0;
    //oldMouse.y=0.0;
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
        if (!passageMenu && stateKeys[K_MENU]) {
            passageMenu = true;
        }
        else if (passageMenu && !stateKeys[K_MENU]) {
            passageMenu = false;
            etatGame = GAME; // seulement une fois que la transition est fini, on change l'etat.
        }
        else {
            menu.menuManager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height); // gere le menu, les options graphiques, et les autres trucs
        }
    }

    else if (etatGame==GAME) {
        if (passageMenu && (!stateKeys[K_MENU])) {
            passageMenu = false;
            etatGame = MENU; // seulement une fois que la transition est fini, on change l'etat.
        }
        else if (!passageMenu && stateKeys[K_MENU]) {
            passageMenu = true;
        }
        else if (passagePause && ((!stateKeys[K_PAUSE]) && (cam.camOK()))) {
            passagePause = false;
            etatGame = PAUSE; // seulement une fois que la transition est fini, on change l'etat.
        }
        else if (!passagePause && stateKeys[K_PAUSE]) {
            passagePause = true;
        }
        else {
            gamePlay.gameManager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
        }
    }

    else if (etatGame==PAUSE) {
        if (passagePause && (!cam.camOK())) {
            cam.resetSmart();
        }
        else if (passagePause && ((!stateKeys[K_PAUSE]) && (cam.camOK()))) {
            passagePause =false;
            etatGame = GAME;
        }
        else if (!passagePause && stateKeys[K_PAUSE]) {
            passagePause = true;
        }
        else {
	  //le menu est la seule exception au lieu d'envoyer les coordonnées de la souris on envoie un delta
            pause.pauseManager(stateKeys, stateButtons, {coordMouse.x-oldMouse.x,coordMouse.y-oldMouse.y}, deltaWheel, time, width, height);
        }
    }

    if (stateKeys[K_CTRL] && (stateKeys[K_QUIT] || stateKeys[K_QUIT_SECOND])) {
        etatGame=STOP;
    }
    render(); // a la fin on affiche tout
    //a la fin les coordonnée de la souris devienne les ancienne coordonnées
    oldMouse.x=coordMouse.x;
    oldMouse.y=coordMouse.y;
}

// fin de l'interface, debut des méthodes privés

void Game::render()
{
    // on recolte toute les instances afficher!
    vector<instance> instances;


    if (etatGame==MENU) {
        menu.getRender(&instances);
        gamePlay.getRender(&instances); // pour Paul
    }
    else if (etatGame==GAME) {
        gamePlay.getRender(&instances);
    }
    else if (etatGame==PAUSE) {
        gamePlay.getRender(&instances);
        pause.getRender(&instances);
    }
    camera came = {(-sin(cam.getLongitude())*cos(cam.getLatitude())*cam.getZoom()) + cam.getCenterX(), (sin(cam.getLatitude())*cam.getZoom())/* + camera.getCenterZ()*/, cos(cam.getLongitude())*cos(cam.getLatitude())*cam.getZoom() + cam.getCenterZ(), cam.getCenterX(), 0 , cam.getCenterZ(),0,1,0};
    lightVec light = {0.5,0.5,0.5,{0.05,0.05,0.05,1},{0.4,0.4,0.3,1},{0.9,0.8,0.8,1}};
    GE.render(instances, came , light ,dTime);
}
