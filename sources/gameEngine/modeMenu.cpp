#include "./modeMenu.h"
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

void ModeMenu::init(Models* models, Camera* camera, Etat* etatGame, SwitchEtat* switchMode)
{
    Mode::init(models, camera, etatGame, switchMode);
    itemSelected=0;
    keyDown=false;
    keyUp=false;
    vect pPlay={0,2,-6}, rPlay={0,0,0}, sPlay={2.5,2.5,1.5};
    textPlay = Text(models->getMChiffres(),models->getMLettersM(), "Play Game", pPlay, rPlay, sPlay, 0.6, CENTER);
    
    vect pPause={0,2,-3}, rPause={0,0,0}, sPause={2,2,1};
    textPause = Text(models->getMChiffres(),models->getMLettersM(), "Stop Motion", pPause, rPause, sPause, 0.6, CENTER); // test du text, pour l'instant "abcde"

    vect pOption={0,2,0}, rOption={0,0,0}, sOption={2,2,1};
    textOption = Text(models->getMChiffres(),models->getMLettersM(), "Option", pOption, rOption, sOption, 0.6, CENTER);
    
    vect pQuit={0,2,3}, rQuit={0,0,0}, sQuit={2,2,1};
    textQuit = Text(models->getMChiffres(),models->getMLettersM(), "Quit Game", pQuit, rQuit, sQuit, 0.6, CENTER);

}


void ModeMenu::menuManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height)
{
    float halfWidth=width/2;
    float halfHeight=height/2;
    float curHeightScale=height/24;
    float curWidthScale=width/24;
    
      Mode::Manager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
      //cout << "les coordonnées sont : x = " << coordMouse.x << " et y = " << coordMouse.y << endl;
      if(stateKeys[K_DOWN] && !keyDown) {
	//si on appuye sur down et qu'il est pas activé
	keyDown=true;//on l'active
	if(itemSelected==0) {
	  //on agrandit le text Pause et on reduit le Play
	  vect s={0.5,0.5,0.5};
	  textPause.scal(s);
	  s.x=-0.5; s.y=-0.5; s.z=-0.5;
	  textPlay.scal(s);
	  itemSelected=1;
	}
	else if(itemSelected==1) {
	  //on agrandit le text Option et on reduit le Pause
	  vect s={0.5,0.5,0.5};
	  textOption.scal(s);
	  s.x=-0.5; s.y=-0.5; s.z=-0.5;
	  textPause.scal(s);
	  itemSelected=2;
	}
	else if(itemSelected==2) {
	  //on agrandit le text Quit et on reduit le Option
	  vect s={0.5,0.5,0.5};
	  textQuit.scal(s);
	  s.x=-0.5; s.y=-0.5; s.z=-0.5;
	  textOption.scal(s);
	  itemSelected=3;
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
	  itemSelected=3;
	}
	else if(itemSelected==1) {
	  //on agrandit le text Play et on reduit le Pause
	  vect s={0.5,0.5,0.5};
	  textPlay.scal(s);
	  s.x=-0.5; s.y=-0.5; s.z=-0.5;
	  textPause.scal(s);
	  itemSelected=0;
	}
	else if(itemSelected==2) {
	  //on agrandit le text Pause et on reduit le Option
	  vect s={0.5,0.5,0.5};
	  textPause.scal(s);
	  s.x=-0.5; s.y=-0.5; s.z=-0.5;
	  textOption.scal(s);
	  itemSelected=1;
	}
	else {
	  //on agrandit le texte Option et on reduit le Quit
	  vect s={0.5,0.5,0.5};
	  textOption.scal(s);
	  s.x=-0.5; s.y=-0.5; s.z=-0.5;
	  textQuit.scal(s);
	  itemSelected=2;
	}
      }
      else if(!stateKeys[K_UP] && keyUp) {
	//si keyDown est actif mais qu'on a relaché K_DOWN
	keyUp=false;
      }
      
      if(stateKeys[K_ENTER]) {
	if(itemSelected==0) {
	    *etatGame = GAME;
	    *switchMode = TOGAME;
	}
	else if(itemSelected==1)
	    *etatGame=PAUSE;
	else if(itemSelected==2)
	    cout << "fonction non implémentée" << endl;
	else if(itemSelected==3)
	    *etatGame=STOP;
      }
//---gestion de la souris--

    //test pour play
    /*cout << "Coordonnée de xmin de Play : " << halfWidth-textPlay.getXY().x*curWidthScale << endl;*/
     if((coordMouse.x >= halfWidth-textPlay.getXY().x*curWidthScale) && (coordMouse.y <= halfHeight+(textPlay.getPosition().z+textPlay.getXY().y)*curHeightScale) &&
       (coordMouse.x <= halfWidth+textPlay.getXY().x*curWidthScale) && (coordMouse.y >= halfHeight+(textPlay.getPosition().z-textPlay.getXY().y)*curHeightScale)) {
	//on est sur play
	/*cout << "on rentre dans play" <<endl;*/
	vect s={-0.5,-0.5,-0.5};
	switch(itemSelected) {
	  case 0:
	    //on fait rien play est deja en gros
	    break;
	  case 1:
	    textPause.scal(s);// on réduit option
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textPlay.scal(s);//on agrandit play
	    itemSelected=0;//on le déclare comme séléctionné
	    break;
	  case 2:
	    textOption.scal(s);
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textPlay.scal(s);//on agrandit play
	    itemSelected=0;//on le déclare comme séléctionné
	    break;
	  case 3:
	    textQuit.scal(s);
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textPlay.scal(s);//on agrandit play
	    itemSelected=0;//on le déclare comme séléctionné
	    break;
	}
	//on test si l'on a cliqué auquel cas on active l'etat
	if(stateButtons[B_LEFT]) {
	  *etatGame=GAME;
	  *switchMode = TOGAME;
	  //break;//on break la boucle pour même pas évaluer la touche ENTER
	  //NOTE: je sais pas si il est utile
	}
    }
    
    if((coordMouse.x >= halfWidth-textPause.getXY().x*curWidthScale) && (coordMouse.y <= halfHeight+(textPause.getPosition().z+textPause.getXY().y)*curHeightScale) &&
       (coordMouse.x <= halfWidth+textPause.getXY().x*curWidthScale) && (coordMouse.y >= halfHeight+(textPause.getPosition().z-textPause.getXY().y)*curHeightScale)) {
	//on est sur Pause
	/*cout << "on rentre dans pause" <<endl;*/
	vect s={-0.5,-0.5,-0.5};
	switch(itemSelected) {
	  case 0:
	    textPlay.scal(s);// on réduit play
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textPause.scal(s);//on agrandit pause
	    itemSelected=1;//on le déclare comme séléctionné
	    break;
	  case 1:
	    //on fai rien
	    break;
	  case 2:
	    textOption.scal(s);//on réduit quit
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textPause.scal(s);//on agrandit Pause
	    itemSelected=1;//on le déclare comme séléctionné
	    break;
	  case 3:
	    textQuit.scal(s);//on réduit quit
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textPause.scal(s);//on agrandit Pause
	    itemSelected=1;//on le déclare comme séléctionn
	    break;
	}
	//on test si l'on a cliqué auquel cas on active l'etat
	if(stateButtons[B_LEFT]) {
	  *etatGame=PAUSE;
	}
    }
    
    
    
    //test pour Option
     /*cout << "Coordonnée de xmin de Option : " << halfWidth-textOption.getXY().x*curWidthScale << endl;*/
     if((coordMouse.x >= halfWidth-textOption.getXY().x*curWidthScale) && (coordMouse.y <= halfHeight+(textOption.getPosition().z+textOption.getXY().y)*curHeightScale) &&
       (coordMouse.x <= halfWidth+textOption.getXY().x*curWidthScale) && (coordMouse.y >= halfHeight+(textOption.getPosition().z-textOption.getXY().y)*curHeightScale)) {
	//on est sur Option
	/*cout << "on rentre dans option" <<endl;*/
	vect s={-0.5,-0.5,-0.5};
	switch(itemSelected) {
	  case 0:
	    textPlay.scal(s);// on réduit play
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textOption.scal(s);//on agrandit option
	    itemSelected=2;//on le déclare comme séléctionné
	    break;
	  case 1:
	    textPause.scal(s);
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textOption.scal(s);//on agrandit option
	    itemSelected=2;//on le déclare comme séléctionné
	    break;
	  case 2:
	    //on fait rien on est deja sur Pause
	    break;
	  case 3:
	    textQuit.scal(s);//on réduit Quit
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textOption.scal(s);//on agrandit option
	    itemSelected=2;//on le déclare comme séléctionné
	    break;
	}
	//on test si l'on a cliqué auquel cas on active l'etat
	if(stateButtons[B_LEFT]) {
	  cout << "fonction non implémentée" << endl;
	  //break;//on break la boucle pour même pas évaluer la touche ENTER
	  //NOTE: je sais pas si il est utile
	}
    }
    
    //test pour Quit
        /*cout << "Coordonnée de xmin de Quit : " << halfWidth-textQuit.getXY().x*curWidthScale << endl;*/
     if((coordMouse.x >= halfWidth-textQuit.getXY().x*curWidthScale) && (coordMouse.y <= halfHeight+(textQuit.getPosition().z+textQuit.getXY().y)*curHeightScale) &&
       (coordMouse.x <= halfWidth+textQuit.getXY().x*curWidthScale) && (coordMouse.y >= halfHeight+(textQuit.getPosition().z-textQuit.getXY().y)*curHeightScale)) {
	//on est sur Quit
	/*cout << "on rentre dans quit" <<endl;*/
	vect s={-0.5,-0.5,-0.5};
	switch(itemSelected) {
	  case 0:
	    textPlay.scal(s);// on réduit play
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textQuit.scal(s);//on agrandit option
	    itemSelected=3;//on le déclare comme séléctionné
	    break;
	  case 1:
	    textPause.scal(s);//on réduit Option
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textQuit.scal(s);//on agrandit Quit
	    itemSelected=3;//on le déclare comme séléctionné
	    break;
	  case 2:
	    textOption.scal(s);//on réduit Option
	    s.x=0.5; s.y=0.5; s.z=0.5;
	    textQuit.scal(s);//on agrandit Quit
	    itemSelected=3;//on le déclare comme séléctionné
	    break;
	  case 3:
	    //on fait rien on est deja sur Quit
	    break;
	}
	//on test si l'on a cliqué auquel cas on active l'etat
	if(stateButtons[B_LEFT]) {
	  *etatGame=STOP;
	  //break;//on break la boucle pour même pas évaluer la touche ENTER
	  //NOTE: je sais pas si il est utile
	}
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
    text = textPause.getText();
    for (itA=text.begin(); itA!=text.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
    text = textOption.getText();
    for (itA=text.begin(); itA!=text.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
}