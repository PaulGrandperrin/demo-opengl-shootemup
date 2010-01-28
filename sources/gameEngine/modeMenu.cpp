#include "./modeMenu.h"
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
ModeMenu::ModeMenu(Models* models, Camera* camera, Etat* etatGame, SwitchEtat* switchMode,SoundEngine* SE) : Mode(models, camera, etatGame, switchMode)
{
    this->SE=SE;

    keyDown=false;
    keyUp=false;
    bMouse=false;
    select = 0;
    selectMouse = 0;
    oldMouse.x = 0;
    oldMouse.y = 0;

    // on reconstruit les objet du menu
    vect p={POSITION_MENU_X,0,-6}, r={0,0,0}, s={2,2,1}; // on donne la meme taille pour tout les objet pour uniformiser les fond !
    MenuItem itemPlay(models, "Play Game",p, r, s, 0.6, CENTER,GAME,TOGAME);

    p.x=POSITION_MENU_X;
    p.y=0;
    p.z=-3;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=2;
    s.y=2;
    r.z=1;
    MenuItem itemPause(models, "Pause Mode", p, r,s, 0.6, CENTER,PAUSE,TOPAUSE);

    p.x=POSITION_MENU_X;
    p.y=0;
    p.z=0;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=2;
    s.y=2;
    r.z=1;
    MenuItem itemOption(models, "Options",p, r, s, 0.6, CENTER,OPTION,NONE);

    p.x=POSITION_MENU_X;
    p.y=0;
    p.z=3;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=2;
    s.y=2;
    r.z=1;
    MenuItem itemAbout(models, "About", p,r,s, 0.6, CENTER,ABOUT,NONE);

    p.x=POSITION_MENU_X;
    p.y=0;
    p.z=6;
    r.x=0;
    r.y=0;
    r.z=0;
    s.x=2;
    s.y=2;
    r.z=1;
    MenuItem itemQuit(models, "Quit Game", p,r, s, 0.6, CENTER,STOP,NONE);

    s.x=0.5;
    s.y=0.5;
    s.z=0.5;
    itemPlay.changeScale(s); // et on agrandi le selectionne

    vect pFond={POSITION_MENU_X,-1,0}, rFond={-90,0,0}, sFond={9.5,9.5,2};
    fondMenu = Actor(models->getMFondMenu(), pFond, rFond, sFond);


    this->vectorItems.push_back(itemPlay);
    this->vectorItems.push_back(itemPause);
    this->vectorItems.push_back(itemOption);
    this->vectorItems.push_back(itemAbout);
    this->vectorItems.push_back(itemQuit);
}


void ModeMenu::menuManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height) {
    SE->play("sounds/ocean.wav",true);
    Point deltaMouse = {coordMouse.x-oldMouse.x,coordMouse.y-oldMouse.y};
    oldMouse.x=coordMouse.x;
    oldMouse.y=coordMouse.y;
    float halfWidth=width/2;
    float halfHeight=height/2;
    float curHeightScale=NB_UNITY_HEIGHT;
    float curWidthScale=NB_UNITY_WIDTH;


    Mode::Manager(stateKeys, stateButtons, coordMouse, deltaWheel, time, width, height);
    //cout << "les coordonnées sont : x = " << coordMouse.x << " et y = " << coordMouse.y << endl;
    if (stateKeys[K_DOWN] && !keyDown) {
        //si on appuye sur down et qu'il est pas activé
        keyDown=true;//on l'active
        vect s={-0.5,-0.5,-0.5}; // on diminue la taille du courant
        vectorItems[select].changeScale(s);

        s.x=0.5;
        s.y=0.5;
        s.z=0.5; // on selectionne le suivant et on augement sa taille
        if (select == (int)vectorItems.size()-1) { // dernier -> suivant = 0
            vectorItems[0].changeScale(s);
            select = 0;
        }
        else {
            vectorItems[select+1].changeScale(s);
            select +=1;
        }
        selectMouse = -1; // on annule la secection de la souris
    }
    else if (!stateKeys[K_DOWN] && keyDown) {
        //si keyDown est actif mais qu'on a relaché K_DOWN
        keyDown=false;
    }


    if (stateKeys[K_UP] && !keyUp) {
        //si on appuye sur down et qu'il est pas activé
        keyUp=true;//on l'active
        vect s={-0.5,-0.5,-0.5};
        vectorItems[select].changeScale(s);

        s.x=0.5;
        s.y=0.5;
        s.z=0.5;
        if (select == 0) {
            vectorItems[vectorItems.size()-1].changeScale(s);
            select = vectorItems.size()-1;
        }
        else {
            vectorItems[select-1].changeScale(s);
            select -=1;
        }
        selectMouse = -1; // on annule la secection de la souris
    }
    else if (!stateKeys[K_UP] && keyUp) {
        //si keyDown est actif mais qu'on a relaché K_DOWN
        keyUp=false;
    }

    //gestion de la touche entrée en fonctione
    if (stateKeys[K_ENTER]) {
        for (int i=0; i<(int)vectorItems.size();i++) {
            if (i==select) {//si on est sur l'item selectionné
                *etatGame = vectorItems[i].getState();
                *switchMode = vectorItems[i].getSwitchState();
            }
        }
    }

    //gestion de la souris
    for (int i=0; i<(int)vectorItems.size();i++) {
        vect s={-0.5,-0.5,-0.5};
        if (!vectorItems[i].mouseOver(coordMouse,halfWidth,halfHeight,height/curHeightScale/2,width/curWidthScale/2) && selectMouse == i && select != i ) {//si la souris n'est plus sur l'item precedement selectionne
            vectorItems[selectMouse].changeScale(s);
            selectMouse = select;
        }
        if (vectorItems[i].mouseOver(coordMouse,halfWidth,halfHeight,height/curHeightScale/2,width/curWidthScale/2) && selectMouse != i && i != select
                && (deltaMouse.x != 0 || deltaMouse.y != 0)) {//si la souris est sur l'item
            vectorItems[select].changeScale(s);
            select = i;
            s.x = 0.5;
            s.y=0.5;
            s.z=0.5;
            vectorItems[i].changeScale(s);
            selectMouse = i;
        }
    }

    if (stateButtons[B_LEFT] && !bMouse) { // si le bouton gauche de la souris est clicker, on previens le menu
        bMouse=true;
    }

    if (bMouse && !stateButtons[B_LEFT] && selectMouse != -1) {//si le bouton de la souris n'est plus cliqué mais qu'il la etait juste avant, on change l'etat
        bMouse=false; // et on previens l'application quel peut resevoir d'autre click
        *etatGame=vectorItems[selectMouse].getState();
        *switchMode = vectorItems[selectMouse].getSwitchState();
    }

}


void ModeMenu::getRender(vector<instance>* /*instances*/, vector<instance>* instances2D) {
    instances2D->push_back(fondMenu.getInstance());
    vector<MenuItem>::iterator itA;
    for (itA=vectorItems.begin(); itA!=vectorItems.end(); itA++) {
        itA->getRender(instances2D);
    }

}
