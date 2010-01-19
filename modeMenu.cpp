#include "modeMenu.h"
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

ModeMenu::~ModeMenu()
{
}

void ModeMenu::init(Models* models, Etat* etatGame)
{
    Mode::init(models, etatGame);
    textMenu = Text("aaaaaa", {0,2,0}, {0,0,0}, {2,2,.5}, 1, models->getMChiffres(),models->getMLettersa()); // test du text, pour l'instant "aaaaaaa"

}


void ModeMenu::menuManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height)
{
    Mode::Manager(stateKeys, stateButtons, deltaMouse, deltaWheel, time, width, height);

}


void ModeMenu::getRender(vector<instance>* instances) {
    vector<Actor> text;
    vector<Actor>::iterator itA;

    text = textMenu.getText();
    for (itA=text.begin(); itA!=text.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
}

