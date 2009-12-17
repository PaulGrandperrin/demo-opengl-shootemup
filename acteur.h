#ifndef ACTEUR_H_
#define ACTEUR_H_

#include "parametres.h"
#include "modelActeur.h"
//#include <QWidget>
//#include <QGLWidget>
//#include <QKeyEvent>
//#include "keyboard.h"
//#include <QThread>


// #include <iostream>
// using namespace std;

class Acteur {
public:
    Acteur(ModelActeur* model = NULL, float posx = POSX_DEFAULT_VAISSEAU, float posy = POSY_DEFAULT_VAISSEAU, float posz = POSZ_DEFAULT_VAISSEAU, float anglex = ANGLEX_DEFAULT_VAISSEAU, float angley = ANGLEY_DEFAULT_VAISSEAU, float anglez = ANGLEZ_DEFAULT_VAISSEAU, float size = TAILLE_DEFAULT_VAISSEAU);
    ~Acteur();
    void Deplacement(float x, float y, float z);
    void Rotation(float x, float y, float z);
    void Scale(float s);
    void Afficher();

private:
    ModelActeur* model;  // 3D objet here, but will be replace by more complet Objects
    float size; // just fort test, but will go to the objet (Ennemis...)
    float anglex, angley, anglez; // just fort test, but will go to the objet (Ennemis...)
    float posx, posy, posz; // public, more easy, but test
};
#endif