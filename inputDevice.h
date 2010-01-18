#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "parameters.h"
#include "function.h"
#include <QKeyEvent>
#include <QMouseEvent>

class Keyboard {
private:
    int connectionKey[NB_KEYS];  // connection between keycode of Qt, and our keycode
    bool stateKeys[NB_KEYS]; // every key has one state (push or not)
public:
    Keyboard();
    void updateEvent(int key, bool state);  // change state of key : state of key = state. If invalid key, nothing
    inline bool* getStateKeys() {
        return stateKeys;
    };
};

class Mouse {
private:
    int connectionButton[NB_BUTTON];  // connection between keycode of Qt, and our keycode
    bool stateButtons[NB_BUTTON]; // every key has one state (push or not)
    Point pMouse, lastPMouse;
    int dWheel;
public:
    Mouse();
    void updateEvent(int button, int state);  // change state of key : state of key = state. If invalid key, nothing
    void updateXY(QPoint pt);  // change state of key : state of key = state. If invalid key, nothing
    void updateWheel(int d);
    inline bool* getStateButtons() {
        return stateButtons;
    };
    inline Point getDeltaMouse() {
        Point pt;
        pt.x = (pMouse.x-lastPMouse.x);
        pt.y = (pMouse.y-lastPMouse.y);
        return pt; // return un couple du delta de la souris
    };
    inline int getDeltaWheel() { //TODO terminer gestion molette
        return (dWheel); // - lastDWheel
    };

};

#endif
