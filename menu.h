#ifndef MENU_H_
#define MENU_H_

#include <list>
#include <math.h>

#include "actor.h"
#include "models.h"
#include "parameters.h"
#include "function.h"
#include "text.h"




class Menu
{
public:
    ~Menu();
    void init(Models* models,Etat* etatGame);
    void menuManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height);

    void getRender(vector<instance>* instances);

private:
    Etat* etatGame;
    Models* models; // menu peut avoir des instance de tout les models
    
    Text textMenu; // "aaaaaaa" 

    bool* stateKeys;
    bool* stateButtons;
    Point deltaMouse;
    int deltaWheel;

    float dTime;
    int widthView,heightView; // nombre de pixel
    float width, height; // correspond au nombre d'uniter "opengl" sur la larger et la hauteur


};

#endif
