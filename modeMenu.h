#ifndef MENU_H_
#define MENU_H_

#include <list>
#include <math.h>

#include "mode.h"


class ModeMenu : public Mode
{
public:
    ~ModeMenu();
    void init(Models* models,Etat* etatGame);
    void menuManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height);

    void getRender(vector<instance>* instances);

private:

    Text textMenu; // "aaaaaaa"

};

#endif
