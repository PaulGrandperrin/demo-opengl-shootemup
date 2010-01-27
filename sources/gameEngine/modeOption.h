#ifndef MODEOPTION_H_
#define MODEOPTION_H_

#include <list>
#include <math.h>

#include "./mode.h"
#include "./objects/menuItem.h"

class ModeOption : public Mode
{
public:
    ~ModeOption() {};
    ModeOption() {}
    ModeOption(Models* models, Camera* camera,Etat* etatGame, SwitchEtat* switchMode);
    void optionManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height);
    void getRender(vector<instance>* instances,vector<instance>* instances2D);

private:

    MenuItem title,up,down,right,left,fire1,fire2,full,screen,pause,menu;
    vector<MenuItem> vectorItems;
    Actor fondMenu;
};

#endif
