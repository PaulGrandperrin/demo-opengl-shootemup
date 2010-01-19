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
   
    pPlay.x=0; pPlay.y=2; pPlay.z=-3;
    rPlay.x=0; rPlay.y=0; rPlay.z=-0;
    sPlay.x=2.5; sPlay.y=2.5; sPlay.z=1;
    textPlay = Text(models->getMChiffres(),models->getMLettersa(), "bbbbbb", pPlay, rPlay, sPlay, 1, CENTER); // test du text, pour l'instant "abcde"

    pQuit.x=0; pQuit.y=2; pQuit.z=0;
    rQuit.x=0; rQuit.y=0; rQuit.z=-0;
    sQuit.x=2; sQuit.y=2; sQuit.z=0.5;
    textQuit = Text(models->getMChiffres(),models->getMLettersa(), "aaabaaa", pQuit, rQuit, sQuit, 1, CENTER); // test du text, pour l'instant "aaaaaaa"
    
    vect pTruc={-8,2,8}, rTruc={0,0,0}, sTruc={1.2,1.2,0.5};
    truc = Text(models->getMChiffres(),models->getMLettersa(), "ccc", pTruc, rTruc, sTruc, 1, RIGHT); // test du text, pour l'instant "abcde"
}


void ModeMenu::menuManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height)
{
    Mode::Manager(stateKeys, stateButtons, deltaMouse, deltaWheel, time, width, height);

 /* demo:  Voila des nouvel fonction de text que tu pourra utilise pour les effets du menu */
    if (stateKeys[K_TIR_SECOND])
    {
      vect r={0,1,0};
      truc.rotate(r);
    }
    else if (stateKeys[K_TIR])
    {
      vect r={0,-1,0};
      truc.rotate(r);
    }
    else {
      vect r={0,0.1,0};
      truc.rotate(r);
    }
    
    if (stateKeys[K_SHIFT])
    {
        vect s={0.2,0.2,0.2};
	truc.scal(s);
    }
    else if (stateKeys[K_ALT])
    {
        vect s={-0.2,-0.2,-0.2};
	truc.scal(s);
    }
    
    if (stateKeys[K_LEFT])
    {
        vect t={-1,0,0};
	truc.translate(t);
    }
    else if (stateKeys[K_RIGHT])
    {
        vect t={1,0,0};
	truc.translate(t);
    }
/* fin demo */

    
    if(stateKeys[K_UP] || stateKeys[K_DOWN]) {
      cout << "UP ou Down : ";
      if(itemSelected==0) {
	//on agrandit le text Quit et on reduit le Play
// 	sPlay={2,2,0.5}; // Les fonctions son donner au dessus !
// 	sQuit={2.5,2.5,1};
	itemSelected=1;
      }
      else {
	//on agrandit le texte Play et on reduit le Quit
// 	sPlay={2.5,2.5,1};
// 	sQuit={2,2,0.5};
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
    text = truc.getText();
    for (itA=text.begin(); itA!=text.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
}

//comment supprimer les warning
//comment faire pour que sa ne change pas 2000 mille fois quand on appuye une fois
//comment resize le text ?? si on pouvait me donner plus d'explication sur le render
  //Utilise un booleen "changement" qui tant que c'est appuiez reste a true et change le bouton une fois que la touche est relache
  //tu peut metre que si la touche n'est pas relacher dans la 1/2 seconde on passe quand meme au bouton suivant , pour ensuite passer au suivant du suivant !
  //C'est des proposition, il y a biensure 50 facon de la faire !

//++creer un tableau ou un truc comme sa pour gérer les K_UP...