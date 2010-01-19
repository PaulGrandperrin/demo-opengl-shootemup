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
  this->itemSelected=0;
}

void ModeMenu::init(Models* models, Etat* etatGame)
{
    Mode::init(models, etatGame);
    
    pPlay={0,2,-3};
    rPlay={0,0,0};
    sPlay={2.5,2.5,1};
    textPlay = Text("bbbbbb", pPlay, rPlay, sPlay, 1.5, models->getMChiffres(),models->getMLettersa(), CENTER); // test du text, pour l'instant "abcde"
    
    pQuit={0,2,0};
    rQuit= {0,0,0};
    sQuit={2,2,0.5};
    textQuit = Text("aaabaaa", pQuit, rQuit, sQuit, 1, models->getMChiffres(),models->getMLettersa(), CENTER); // test du text, pour l'instant "aaaaaaa"
    
}


void ModeMenu::menuManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height)
{
    Mode::Manager(stateKeys, stateButtons, deltaMouse, deltaWheel, time, width, height);
    
    if(stateKeys[K_UP] || stateKeys[K_DOWN]) {
      cout << "UP ou Down : ";
      if(itemSelected==0) {
	//on agrandit le text Quit et on reduit le Play
	sPlay={2,2,0.5};
	sQuit={2.5,2.5,1};
	itemSelected=1;
      }
      else {
	//on agrandit le texte Play et on reduit le Quit
	sPlay={2.5,2.5,1};
	sQuit={2,2,0.5};
	itemSelected=0;
      }
      cout << itemSelected << endl;
    }
    
    if(stateKeys[K_ENTER]) {
      cout << "Enter" << endl;
      if(itemSelected==0)
	  *etatGame=GAME;
      else if(itemSelected==1)
	  *etatGame=STOP;
    }
}


void ModeMenu::getRender(vector<instance>* instances) {
    vector<Actor> text;
    vector<Actor>::iterator itA;

    text = textQuit.getText();
    for (itA=text.begin(); itA!=text.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
    text = textPlay.getText();
    for (itA=text.begin(); itA!=text.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
}

//comment supprimer les warning
//comment faire pour que sa ne change pas 2000 mille fois quand on appuye une fois
//comment resize le text ?? si on pouvait me donner plus d'explication sur le render

//++creer un tableau ou un truc comme sa pour gérer les K_UP...