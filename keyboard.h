#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "parameters.h"

#include <QKeyEvent>

class Keyboard {
private:
    int connectionKey[NB_KEYS];  // connection bettewen keycode of Qt, and our keycode
    int stateKey[NB_KEYS]; // every key has one state (push or not)
public:
    Keyboard();
    void updateEvent(int key, int state);  // change state of key : state of key = state. If invalid key, nothing
    int hotKey(int key); //return 1 if key "key" is active, else 0
};

#endif
