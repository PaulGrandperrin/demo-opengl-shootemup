#include "./inputDevice.h"

#include <stdlib.h>

// for trace during test , to kept
#include <iostream>
using namespace std;
extern Parameters *parametre;

//http://doc.trolltech.com/4.1/qt.html

Keyboard::Keyboard() {
    // On definit les touches par defaut
    int connectionKeyTab[NB_KEYS] = {Qt::QT_K_QUIT, Qt::QT_K_CTRL,  Qt::QT_K_SHIFT, Qt::QT_K_ALT, Qt::QT_K_UP, Qt::QT_K_DOWN, Qt::QT_K_LEFT, Qt::QT_K_RIGHT, Qt::QT_K_TIR, Qt::QT_K_TIR_SECOND, Qt::QT_K_PAUSE, Qt::QT_K_FULLSCREEN, Qt::QT_K_FULLSCREEN_SECOND, Qt::QT_K_QUIT_SECOND, Qt::QT_K_ESC, Qt::QT_K_MENU, Qt::QT_K_ENTER, Qt::QT_K_SCREENSHOT};
    // Initialisation des attributs
    for (int i = 0; i<NB_KEYS; i++) {
        stateKeys[i] = 0;
        connectionKey[i] = connectionKeyTab[i];
    }
}


void Keyboard::updateEvent(int key, bool state) {
    int i = 0;
    // Grace au code de la touche et au tableau de correspondance, on recupere son etat
    while (i < NB_KEYS && connectionKey[i] != key) {
        i++;
    }
    if (i < NB_KEYS)
        stateKeys[i] = state;
}


Mouse::Mouse() {
    int connectionButtonTab[NB_BUTTON] = {Qt::LeftButton, Qt::MidButton, Qt::RightButton};
    for (int i = 0; i<NB_BUTTON; i++) {
        stateButtons[i] = 0;
        connectionButton[i] = connectionButtonTab[i];
    }
    lastPMouse.x = 0; // lastPMouse est un QPoint donc methode set().
    lastPMouse.y = 0;
    dWheel=0;
}

void Mouse::updateEvent(int button, int state) {
    int i = 0;
    while (i < NB_BUTTON && connectionButton[i] != button) {
        i++;
    }
    if (i < NB_BUTTON)
        stateButtons[i] = state;
}

void Mouse::updateXY(QPoint pt) { // avec lastxy et xy on recupere le delta de la souris a l'instant d'avant.
    lastPMouse = pMouse; //pMouse Point
    pMouse.x = pt.x(); // pt QPoint
    pMouse.y = pt.y();
}

//FIXME : quelque probleme de fonctionnement, je mis prend peut etre pas de la bonne maniere.
void Mouse::updateWheel(int d) { // idem udpdateXY, mais sur un seul axe pour la molette
    dWheel = d;
}
