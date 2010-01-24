#ifndef MODEMENU_H_
#define MODEMENU_H_

#include <list>
#include <math.h>

#include "./mode.h"
#include "./objects/menuItem.h"

class ModeMenu : public Mode
{
public:
    ~ModeMenu() {};
    ModeMenu() {}
    ModeMenu(Models* models, Camera* camera,Etat* etatGame, SwitchEtat* switchMode);
    void menuManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height);

    void getRender(vector<instance>* instances);

private:
    Point oldMouse;
    MenuItem itemPlay, itemPause, itemOption, itemQuit;
    bool keyDown, keyUp, bMouse;
    vector<MenuItem> vectorItems;
    int select;
    int selectMouse;

};

#endif
