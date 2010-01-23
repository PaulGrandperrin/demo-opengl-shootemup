#include "./modeMenu.h"
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

void ModeMenu::init(Models* models, Camera* camera, Etat* etatGame, SwitchEtat* switchMode)
{
    Mode::init(models, camera, etatGame, switchMode);
    itemSelected=&itemPlay;
    keyDown=false;
    keyUp=false;
    MenuItem itemPlay(models->getMChiffres(),models->getMLettersM(), "Play Game", {0,2,-6}, {0,0,0}, {2.5,2.5,1.5}, 0.6, CENTER,true,GAME,TOGAME);
    MenuItem itemPause(models->getMChiffres(),models->getMLettersM(), "Stop Motion", {0,2,-3}, {0,0,0},{2,2,1}, 0.6, CENTER,false,PAUSE,TOPAUSE);
    MenuItem itemOption(models->getMChiffres(),models->getMLettersM(), "Option",{0,2,0},{0,0,0}, {2,2,1}, 0.6, CENTER,false,NO,NONE);
    MenuItem itemQuit(models->getMChiffres(),models->getMLettersM(), "Quit Game", {0,2,3}, {0,0,0}, {2,2,1}, 0.6, CENTER,false,STOP,NONE);
    this->vectorItems.push_back(itemPlay);
    this->vectorItems.push_back(itemPause);
    this->vectorItems.push_back(itemOption);
    this->vectorItems.push_back(itemQuit);
}


void ModeMenu::menuManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height) {
    float halfWidth=width/2;
    float halfHeight=height/2;
    float curHeightScale=NB_UNITY_WIDTH*2;
    float curWidthScale=NB_UNITY_HEIGHT*2;
    
      Mode::Manager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
      //cout << "les coordonnées sont : x = " << coordMouse.x << " et y = " << coordMouse.y << endl;
      if(stateKeys[K_DOWN] && !keyDown) {
	//si on appuye sur down et qu'il est pas activé
	keyDown=true;//on l'active
	
	/*vector<MenuItem>::iterator it;
	for (it=vectorItems.begin(); it!=vectorItems.end(); it++) {
	      //utiliser la methode sans iterateur
	      vect s={0.5,0.5,0.5};
	      if(it==vectorItems.end() {//si on est sur le dernier*/
	for(unsigned int i=0; i<vectorItems.size();i++) {
	  vect s={0.5,0.5,0.5};
	  if(&vectorItems[i]==itemSelected) {//si on est sur l'item selectionné
	      if(i==vectorItems.size()) {//si on est sur le dernier*/
		  vectorItems[0].changeScale(s);//on agrandit le premier!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		  *itemSelected=vectorItems[0];//l'item selectionné devient le premier
	      }
	      else {
		  vectorItems[i+1].changeScale(s);//on agrandit le suivant!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		  itemSelected=&vectorItems[i+1];
	      }
	      s.x=-0.5; s.y=-0.5; s.z=-0.5;
	      vectorItems[i].changeScale(s);//dans tout les cas on réduit le courant!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  }
	}
      }
      else if(!stateKeys[K_DOWN] && keyDown) {
	//si keyDown est actif mais qu'on a relaché K_DOWN
	keyDown=false;
      }
      
      
      if(stateKeys[K_UP] && !keyUp) {
	//si on appuye sur down et qu'il est pas activé
	keyUp=true;//on l'active
	
	for(unsigned int i=0; i<vectorItems.size();i++) {
	  vect s={0.5,0.5,0.5};
	  if(&vectorItems[i]==itemSelected) {//si on est sur l'item selectionné
	      if(i==0) {//si on est sur le premier
		  vectorItems[vectorItems.size()].changeScale(s);//on agrandit le dernier!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		  *itemSelected=vectorItems[vectorItems.size()];//l'item selectionné devient le dernier
	      }
	      else {
		  vectorItems[i+1].changeScale(s);//on agrandit le suivant!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		  *itemSelected=vectorItems[i+1];
	      }
	      s.x=-0.5; s.y=-0.5; s.z=-0.5;
	      vectorItems[i].changeScale(s);//dans tout les cas on réduit le courant!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  }
	}
      }
      else if(!stateKeys[K_UP] && keyUp) {
	//si keyDown est actif mais qu'on a relaché K_DOWN
	keyUp=false;
      }
      
      //gestion de la touche entrée en fonctione
      if(stateKeys[K_ENTER]) {
	for(unsigned int i=0; i<vectorItems.size();i++) {
	    if(&vectorItems[i]==itemSelected) {//si on est sur l'item selectionné
		*etatGame = vectorItems[i].getState();
		*switchMode = vectorItems[i].getSwitchState();
	    }
	}
      }

      //gestion de la souris
	for(unsigned int i=0; i<vectorItems.size();i++) {
		vect s={0.5,0.5,0.5};
		if(vectorItems[i].mouseOver(coordMouse,halfWidth,halfHeight,curHeightScale,curWidthScale)) {//si la souris est sur l'item
			if(itemSelected==&vectorItems[i]) {//si la souris est sur l'item selectionnée on ne fais rien
			}
			else {
				vectorItems[i].changeScale(s);//on agrandit l'item!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				s.x=-0.5; s.y=-0.5; s.z=-0.5;
				for(unsigned int j=0; j<vectorItems.size();j++)
					if(&vectorItems[j]==itemSelected)
						vectorItems[j].changeScale(s);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//itemSelected.changeScale(s);//on reduit l'item selectionné
				itemSelected=&vectorItems[i];//l'item selectionné devient celui sur lequel on est
			}
			
			if(stateButtons[B_LEFT]) {//si le bouton de la souris est cliqué on change l'etat
				*etatGame=vectorItems[i].getState();
				*switchMode = vectorItems[i].getSwitchState();
			}
		break;//on sort de la boucle car la souris ne peut pas être a deux endroit en même temps
		}
	}

}


void ModeMenu::getRender(vector<instance>* instances) {
    for(unsigned int i=0; i<vectorItems.size();i++)
	vectorItems[i].getRender(instances);
}
