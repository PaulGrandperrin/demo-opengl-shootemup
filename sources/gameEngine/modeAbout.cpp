#include "./modeAbout.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <typeinfo>

/* le plan de jeu ce fait sur xz */

//     Y--------X
//     |
//     |
//     |
//     Z

// for trace during test , to kept
#include <iostream>
using namespace std;
extern Parameters *parametre;

ModeAbout::ModeAbout(Models* models, Camera* camera, Etat* etatGame, SwitchEtat* switchMode) : Mode(models, camera, etatGame, switchMode)
{
  
    // on reconstruit les objet du menu
    vect p={0,0,-9}, r={0,0,0}, s={2,2,1};
    Text madeBy(models, "Made By  ",p, r, s, 0.5, RIGHT);
    this->vectorText.push_back(madeBy);
    
    p.x=0;p.y=0;p.z=-6; r.x=0;r.y=0;r.z=0; s.x=1.5;s.y=1.5;s.z=0.75;
    Text robin(models, "DAVID Robin",p,r,s, 0.5, CENTER);
    this->vectorText.push_back(robin);
    
    p.x=0;p.y=0;p.z=-3; r.x=0;r.y=0;r.z=0; s.x=1.5;s.y=1.5;s.z=0.75;
    Text jeanlu(models, "PASQUIER Jean-Luc",p,r,s, 0.5, CENTER);
    this->vectorText.push_back(jeanlu);

    p.x=0;p.y=0;p.z=0; r.x=0;r.y=0;r.z=0; s.x=1.5;s.y=1.5;s.z=0.75;
    Text sebastien(models, "BERTHIER Sebastien", p,r,s, 0.5, CENTER);
    this->vectorText.push_back(sebastien);
    
    p.x=0;p.y=0;p.z=3; r.x=0;r.y=0;r.z=0; s.x=1.5;s.y=1.5;s.z=0.75;
    Text remi(models, "PEYRIN Remi", p,r,s, 0.5, CENTER);
    this->vectorText.push_back(remi);
    
    p.x=0;p.y=0;p.z=6; r.x=0;r.y=0;r.z=0; s.x=1.5;s.y=1.5;s.z=0.75;
    Text paul(models, "GRANDPERRIN Paul", p,r,s, 0.5, CENTER);
    this->vectorText.push_back(paul);
    
    p.x=0;p.y=0;p.z=9; r.x=0;r.y=0;r.z=0; s.x=1.5;s.y=1.5;s.z=0.75;
    Text romain(models, "LETENDART Romain", p,r,s, 0.5, CENTER);
    this->vectorText.push_back(romain);
}


void ModeAbout::aboutManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height) {
    Mode::Manager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
    if(stateKeys[parametre->getEsc()]) {
	*etatGame=MENU;
	*switchMode=TOMENU;
    }
}


void ModeAbout::getRender(vector<instance>* /*instances*/, vector<instance>* instances2D) {
//NOTE:je me demande si sa serait pas bien de faire un getRender pour le texte y aurait moins de redondance    
    vector<Text>::iterator itA;
    vector<Actor> tex;
    vector<Actor>::iterator itB;
    
    for (itA=vectorText.begin(); itA!=vectorText.end(); itA++) {
        tex = itA->getText();
	for (itB=tex.begin(); itB!=tex.end(); itB++) {
	    instances2D->push_back(itB->getInstance());
	}
    }

}
