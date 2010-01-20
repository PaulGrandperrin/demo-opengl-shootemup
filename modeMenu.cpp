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
    itemSelected=0;
    keyDown=false;
    keyUp=false;
    vect pPlay={0,2,-3}, rPlay={0,0,0}, sPlay={2.5,2.5,1};
    textPlay = Text(models->getMChiffres(),models->getMLettersM(), "Play Game", pPlay, rPlay, sPlay, 0.6, CENTER); // test du text, pour l'instant "abcde"

    vect pOption={0,2,0}, rOption={0,0,0}, sOption={2,2,1};
    textOption = Text(models->getMChiffres(),models->getMLettersM(), "Rien", pOption, rOption, sOption, 0.6, CENTER);
    
    vect pQuit={0,2,3}, rQuit={0,0,0}, sQuit={2,2,1};
    textQuit = Text(models->getMChiffres(),models->getMLettersM(), "Quit Game", pQuit, rQuit, sQuit, 0.6, CENTER); // test du text, pour l'instant "aaaaaaa"

}


void ModeMenu::menuManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height)
{
    Mode::Manager(stateKeys, stateButtons, deltaMouse, deltaWheel, time, width, height);
    if(stateKeys[K_DOWN] && !keyDown) {
      //si on appuye sur down et qu'il est pas activé
      keyDown=true;//on l'active
      if(itemSelected==0) {
	//on agrandit le text Option et on reduit le Play
	vect s={0.5,0.5,0.5};
	textOption.scal(s);
	s.x=-0.5; s.y=-0.5; s.z=-0.5;
	textPlay.scal(s);
	itemSelected=1;
      }
      else if(itemSelected==1) {
	//on agrandit le text Quit et on reduit le Option
	vect s={0.5,0.5,0.5};
	textQuit.scal(s);
	s.x=-0.5; s.y=-0.5; s.z=-0.5;
	textOption.scal(s);
	itemSelected=2;
      }
      else {
	//on agrandit le texte Play et on reduit le Quit
	vect s={0.5,0.5,0.5};
	textPlay.scal(s);
	s.x=-0.5; s.y=-0.5; s.z=-0.5;
	textQuit.scal(s);
	itemSelected=0;
      }
    }
    else if(!stateKeys[K_DOWN] && keyDown) {
      //si keyDown est actif mais qu'on a relaché K_DOWN
      keyDown=false;
    }
    
    if(stateKeys[K_UP] && !keyUp) {
      //si on appuye sur down et qu'il est pas activé
      keyUp=true;//on l'active
      if(itemSelected==0) {
	//on agrandit le text Quit et on reduit le Play
	vect s={0.5,0.5,0.5};
	textQuit.scal(s);
	s.x=-0.5; s.y=-0.5; s.z=-0.5;
	textPlay.scal(s);
	itemSelected=2;
      }
      else if(itemSelected==1) {
	//on agrandit le text Play et on reduit le Option
	vect s={0.5,0.5,0.5};
	textPlay.scal(s);
	s.x=-0.5; s.y=-0.5; s.z=-0.5;
	textOption.scal(s);
	itemSelected=0;
      }
      else {
	//on agrandit le texte Option et on reduit le Quit
	vect s={0.5,0.5,0.5};
	textOption.scal(s);
	s.x=-0.5; s.y=-0.5; s.z=-0.5;
	textQuit.scal(s);
	itemSelected=1;
      }
    }
    else if(!stateKeys[K_UP] && keyUp) {
      //si keyDown est actif mais qu'on a relaché K_DOWN
      keyUp=false;
    }
    
    if(stateKeys[K_ENTER]) {
      if(itemSelected==0)
	  *etatGame=GAME;
      else if(itemSelected==1)
	  cout << "fonction non implémentée" << endl;
      else if(itemSelected==2)
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
    text = textOption.getText();
    for (itA=text.begin(); itA!=text.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
}

//comment faire pour que sa ne change pas 2000 mille fois quand on appuye une fois
//comment resize le text ?? si on pouvait me donner plus d'explication sur le render
  //Utilise un booleen "changement" qui tant que c'est appuiez reste a true et change le bouton une fois que la touche est relache
  //tu peut metre que si la touche n'est pas relacher dans la 1/2 seconde on passe quand meme au bouton suivant , pour ensuite passer au suivant du suivant !
  //C'est des proposition, il y a biensure 50 facon de la faire !

//++creer un tableau ou un truc comme sa pour gérer les K_UP...