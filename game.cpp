#include "game.h"
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
    
    camera.init();
    GE.init();

    models.chargerModels(&GE);

    // on initialise les different mode (etat) du jeu
    menu.init(&models,&etatGame);
    gamePlay.init(&models,&etatGame);
    pause.init(&models, &camera,&etatGame);

    srand( time(NULL) ); // un peu de random ne fait pas de mal (function.h, random())
}

void Game::resize(int width,int heigth)
{
    GE.resize(width,heigth);
}

void Game::update(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height) // NOTE peut etre passer un pointeur sur kb et mouse !
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
	    menu.menuManager(stateKeys, stateButtons, deltaMouse, deltaWheel, time, width, height); // gere le menu, les options graphiques, et les autres trucs
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
        else if (passagePause && ((!stateKeys[K_PAUSE]) && (camera.camOK()))) {
            passagePause = false;
            etatGame = PAUSE; // seulement une fois que la transition est fini, on change l'etat.
        }
        else if (!passagePause && stateKeys[K_PAUSE]) {
            passagePause = true;
        }
        else {
	    gamePlay.gameManager(stateKeys, stateButtons, deltaMouse, deltaWheel, time, width, height);
	}
    }

    else if (etatGame==PAUSE) {
        if (passagePause && (!camera.camOK())) {
            camera.resetSmart();
        }
        else if (passagePause && ((!stateKeys[K_PAUSE]) && (camera.camOK()))) {
            passagePause =false;
            etatGame = GAME;
        }
        else if (!passagePause && stateKeys[K_PAUSE]) {
            passagePause = true;
        }
        else {
	    pause.pauseManager(stateKeys, stateButtons, deltaMouse, deltaWheel, time, width, height);
	}
    }

    if (stateKeys[K_CTRL] && (stateKeys[K_QUIT] || stateKeys[K_QUIT_SECOND])) {
        etatGame=STOP;
    }

    render(); // a la fin on affiche tout
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
    GE.render(instances, {(-sin(camera.getLongitude())*cos(camera.getLatitude())*camera.getZoom()) + camera.getCenterX(), (sin(camera.getLatitude())*camera.getZoom())/* + camera.getCenterZ()*/, cos(camera.getLongitude())*cos(camera.getLatitude())*camera.getZoom() + camera.getCenterZ(), camera.getCenterX(), 0 , camera.getCenterZ(),0,1,0} , {0.5,0.5,0.5,{0.05,0.05,0.05,1},{0.4,0.4,0.3,1},{0.9,0.8,0.8,1}},dTime);
}
