#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "parameters.h"

#include <QKeyEvent>
#include <QMouseEvent>

class Keyboard {
private:
    int connectionKey[NB_KEYS];  // connection between keycode of Qt, and our keycode
    bool stateKeys[NB_KEYS]; // every key has one state (push or not)
public:
    Keyboard();
    void updateEvent(int key, int state);  // change state of key : state of key = state. If invalid key, nothing
    inline bool* getStateKeys() {
        return stateKeys;
    };
};

class Mouse {
private:
    int connectionButton[NB_BUTTON];  // connection between keycode of Qt, and our keycode
    bool stateButtons[NB_BUTTON]; // every key has one state (push or not)
    QPoint pMouse, lastPMouse;
    int dWheel;
public:
    Mouse();
    void updateEvent(int button, int state);  // change state of key : state of key = state. If invalid key, nothing
    void updateXY(QPoint pt);  // change state of key : state of key = state. If invalid key, nothing
    void updateWheel(int d);
    inline bool* getStateButtons() {
        return stateButtons;
    };
    inline QPoint getDeltaMouse() {
        QPoint pt;
        pt.setX(pMouse.x()-lastPMouse.x());
        pt.setY(pMouse.y()-lastPMouse.y());
        return pt; // return un couple du delta de la souris
    };
    inline int getDeltaWheel() { //TODO terminer gestion molette
        return (dWheel); // - lastDWheel
    };

};

#endif
