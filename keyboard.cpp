#include "keyboard.h"
#include <stdlib.h>

// for trace during test , to kept
#include <iostream>
using namespace std;

//http://doc.trolltech.com/4.1/qt.html

Keyboard::Keyboard() {
    // On definit les touches par defaut
    int connectionKeyTab[NB_KEYS] = {Qt::Key_Escape, Qt::Key_Left, Qt::Key_Up, Qt::Key_Right, Qt::Key_Down, Qt::Key_Control, Qt::Key_Shift, Qt::Key_Space, Qt::Key_Alt};
    // Initialisation des attributs
    for (int i = 0; i<NB_KEYS; i++) {
        stateKeys[i] = 0;
        connectionKey[i] = connectionKeyTab[i];
    }
}

void Keyboard::updateEvent(int key, int state) {
    int i = 0;
    // Grace au code de la touche et au tableau de correspondance, on recupere son etat
    while (i < NB_KEYS && connectionKey[i] != key) {
        i++;
    }
    if (i < NB_KEYS)
        stateKeys[i] = state;
}

