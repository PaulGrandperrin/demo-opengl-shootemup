#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "../../parameters.h"
#include "../../utilities.h"
#include "./text.h"
#include <iostream>
#include <vector>

class MenuItem {

private:
    Text text;
    Etat state;
    SwitchEtat switchState;
public:
    MenuItem() {}
    MenuItem(Models* models, string text, vect position,vect rotation,vect scale, float esp, TextStyle style, Etat stat, SwitchEtat switchstat);
    inline void changeScale(vect sca) {
        text.scal(sca);
    }
    inline Etat getState() {
        return state;
    }
    inline SwitchEtat getSwitchState() {
        return switchState;
    }
    bool mouseOver(Point mouse, float screenW, float screenH, float curW, float curH);
    void getRender(vector<instance>* instances);

};

#endif
