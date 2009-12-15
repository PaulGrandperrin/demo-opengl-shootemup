#ifndef ACTEUR_H_
#define ACTEUR_H_

#include "Model3D.h"
//#include <QWidget>
//#include <QGLWidget>
//#include <QKeyEvent>
//#include "keyboard.h"
//#include <QThread>


// #include <iostream>
// using namespace std;

class Acteur {
public:
    Acteur(float posx = 0, float posy = 0, float size = 0);
    ~Acteur();
    void Deplacement(float posx, float posy);
    void Rotation(float y);
    void Afficher();

private:
    Model3D mesh;  // 3D objet here, but will be replace by more complet Objects
    float size; // just fort test, but will go to the objet (Ennemis...)
    float anglex, angley; // just fort test, but will go to the objet (Ennemis...)
    float posx,posy; // public, more easy, but test
};
#endif