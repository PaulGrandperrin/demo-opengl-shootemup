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

    vect p={0,0,-9}, r={0,0,0}, s={2,2,1};
    Text madeBy(models, "Made By:",p, r, s, 0.5, RIGHT);
    this->vectorText.push_back(madeBy);

    p.x=0;
    p.y=0;
    p.z=-6;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=1.5;
    s.y=1.5;
    s.z=1;
    Text sebastien(models, "BERTHIER Sebastien", p,r,s, 0.6, CENTER);
    this->vectorText.push_back(sebastien);

    p.x=0;
    p.y=0;
    p.z=-4;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=1.5;
    s.y=1.5;
    s.z=1;
    Text robin(models, "DAVID Robin",p,r,s, 0.5, CENTER);
    this->vectorText.push_back(robin);

    p.x=0;
    p.y=0;
    p.z=-2;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=1.5;
    s.y=1.5;
    s.z=1;
    Text paul(models, "GRANDPERRIN Paul", p,r,s, 0.6, CENTER);
    this->vectorText.push_back(paul);

    p.x=0;
    p.y=0;
    p.z=0;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=1.5;
    s.y=1.5;
    s.z=1;
    Text romain(models, "LETENDART Romain", p,r,s, 0.6, CENTER);
    this->vectorText.push_back(romain);

    p.x=0;
    p.y=0;
    p.z=2;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=1.5;
    s.y=1.5;
    s.z=1;
    Text jeanlu(models, "PASQUIER Jean-Luc",p,r,s, 0.6, CENTER);
    this->vectorText.push_back(jeanlu);

    p.x=0;
    p.y=0;
    p.z=4;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=1.5;
    s.y=1.5;
    s.z=1;
    Text remi(models, "PEYRIN Remi", p,r,s, 0.6, CENTER);
    this->vectorText.push_back(remi);

    p.x=0;
    p.y=0;
    p.z=7;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=1.4;
    s.y=1.4;
    s.z=1;
    Text paragraphe1(models, "Project realised ", p,r,s, 0.6, CENTER);
    this->vectorText.push_back(paragraphe1);

    p.x=0;
    p.y=0;
    p.z=9;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=1.4;
    s.y=1.4;
    s.z=1;
    Text paragraphe2(models, "for a Diploma exam.", p,r,s, 0.6, CENTER);
    this->vectorText.push_back(paragraphe2);

    vect pFond={0,-1,0}, rFond={-90,0,0}, sFond={13,12,2};
    fondMenu = Actor(models->getMFondMenu(), pFond, rFond, sFond);
}


void ModeAbout::aboutManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height) {
    Mode::Manager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);

    if (*switchMode==TOMENU && !(stateKeys[K_ESC] || stateButtons[B_LEFT])) {
        *etatGame=MENU;
        *switchMode=NONE;
    }
    if (*switchMode==NONE &&  (stateKeys[K_ESC] || stateButtons[B_LEFT])) {
// 	*etatGame=MENU;
        *switchMode=TOMENU;
    }
}


void ModeAbout::getRender(vector<instance>* /*instances*/, vector<instance>* instances2D) {
//NOTE:je me demande si sa serait pas bien de faire un getRender pour le texte y aurait moins de redondance
    vector<Text>::iterator itA;
    vector<Actor> tex;
    vector<Actor>::iterator itB;
    instances2D->push_back(fondMenu.getInstance());
    for (itA=vectorText.begin(); itA!=vectorText.end(); itA++) {
        tex = itA->getText();
        for (itB=tex.begin(); itB!=tex.end(); itB++) {
            instances2D->push_back(itB->getInstance());
        }
    }

}
