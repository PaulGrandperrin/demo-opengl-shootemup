#include "./modeOption.h"
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

ModeOption::ModeOption(Models* models, Camera* camera, Etat* etatGame, SwitchEtat* switchMode) : Mode(models, camera, etatGame, switchMode)
{
    // on reconstruit les objet du menu
    vect p={0,0,-9}, r={0,0,0}, s={1.5,2,0.75};
    MenuItem title(models, "Key available",p, r, s, 0.5, RIGHT,OPTION,NONE);
    this->vectorItems.push_back(title);
    
    p.x=0;p.y=0;p.z=-7; r.x=0;r.y=0;r.z=0; s.x=1;s.y=1.5;s.z=0.50;
    MenuItem up(models, "UP     Key UP",p,r,s, 0.5, CENTER,OPTION,NONE);
    this->vectorItems.push_back(up);
    
    p.x=0;p.y=0;p.z=-5; r.x=0;r.y=0;r.z=0; s.x=1;s.y=1.5;s.z=0.50;
    MenuItem down(models, "DOWN     Key Down",p,r,s, 0.5, CENTER,OPTION,NONE);
    this->vectorItems.push_back(down);
    
    p.x=0;p.y=0;p.z=-3; r.x=0;r.y=0;r.z=0; s.x=1;s.y=1.5;s.z=0.50;
    MenuItem right(models, "RIGHT     Key Right",p,r,s, 0.5, CENTER,OPTION,NONE);
    this->vectorItems.push_back(right);
    
    p.x=0;p.y=0;p.z=-1; r.x=0;r.y=0;r.z=0; s.x=1;s.y=1.5;s.z=0.50;
    MenuItem left(models, "LEFT     Key Left",p,r,s, 0.5, CENTER,OPTION,NONE);
    this->vectorItems.push_back(left);
    
    p.x=0;p.y=0;p.z=1; r.x=0;r.y=0;r.z=0; s.x=1;s.y=1.5;s.z=0.50;
    MenuItem fire1(models, "FIRE     W",p,r,s, 0.5, CENTER,OPTION,NONE);
    this->vectorItems.push_back(fire1);

    p.x=0;p.y=0;p.z=3; r.x=0;r.y=0;r.z=0; s.x=1;s.y=1.5;s.z=0.50;
    MenuItem fire2(models, "FIRE 2     X",p,r,s, 0.5, CENTER,OPTION,NONE);
    this->vectorItems.push_back(fire2);

    p.x=0;p.y=0;p.z=5; r.x=0;r.y=0;r.z=0; s.x=1;s.y=1.5;s.z=0.50;
    MenuItem full(models, "Fullscreen     F11",p,r,s, 0.5, CENTER,OPTION,NONE);
    this->vectorItems.push_back(full);

    p.x=0;p.y=0;p.z=7; r.x=0;r.y=0;r.z=0; s.x=1;s.y=1.5;s.z=0.50;
    MenuItem screen(models, "Screenshot     F10",p,r,s, 0.5, CENTER,OPTION,NONE);
    this->vectorItems.push_back(screen);
    
    p.x=0;p.y=0;p.z=9; r.x=0;r.y=0;r.z=0; s.x=1;s.y=1.5;s.z=0.50;
    MenuItem pause(models, "Pause     P",p,r,s, 0.5, CENTER,OPTION,NONE);
    this->vectorItems.push_back(pause);
    
    p.x=0;p.y=0;p.z=11; r.x=0;r.y=0;r.z=0; s.x=1;s.y=1.5;s.z=0.50;
    MenuItem menu(models, "Menu     Esc",p,r,s, 0.5, CENTER,OPTION,NONE);
    this->vectorItems.push_back(menu);
}


void ModeOption::optionManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height) {
    Mode::Manager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
    
    //beaucoup de possibilité. On pourrait récuperer une touche en fonction de l'item selectionné.
    
    if(stateKeys[parametre->getEsc()]) {
	*etatGame=MENU;
	*switchMode=TOMENU;
    }
}


void ModeOption::getRender(vector<instance>* /*instances*/, vector<instance>* instances2D) {    
    vector<MenuItem>::iterator itA;
    
    for (itA=vectorItems.begin(); itA!=vectorItems.end(); itA++) {
        itA->getRender(instances2D);
    }

}
