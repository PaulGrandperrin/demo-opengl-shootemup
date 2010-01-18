#include "menu.h"
// #include "game.h"
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

Menu::~Menu()
{
}

void Menu::init(Models* models, Etat* etatGame)
{
    this->etatGame = etatGame;
    this->models = models;
    textMenu = Text("aaaaaa", {0,2,0}, {0,0,0}, {2,2,.5}, 1, models->getMChiffres(),models->getMLettersa()); // test du text, pour l'instant "aaaaaaa"

}


void Menu::menuManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height)
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

//     if (!*etatGame==PASSAGEMENU && stateKeys[K_MENU]) {
// 	*etatGame = PASSAGEMENU;
//     }
//     else if (*etatGame==PASSAGEMENU && !stateKeys[K_MENU]) {
// 	// passageMenu = false;
// 	*etatGame = GAME; // seulement une fois que la transition est fini, on change l'etat.
//     }
//     if ((stateKeys[K_MENU]) || (stateButtons[B_LEFT]))
//     {
//         *etatGame=GAME; // TODO prevenir game
//     }
}


void Menu::getRender(vector<instance>* instances) {
    vector<Actor> text;
    vector<Actor>::iterator itA;

    text = textMenu.getText();
    for (itA=text.begin(); itA!=text.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
}

