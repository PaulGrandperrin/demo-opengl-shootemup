#ifndef MODELACTEUR_H_
#define MODELACTEUR_H_

#include "parametres.h"
#include "Model3D.h"
//#include <QWidget>
//#include <QGLWidget>
//#include <QKeyEvent>
//#include "keyboard.h"
//#include <QThread>


// #include <iostream>
// using namespace std;

class ModelActeur {
public:
    ModelActeur(string type = TYPE_DEFAULT_MESH);
    ~ModelActeur();
    Model3D* getMesh() { return &mesh; }
    string getType() { return type; }
//     void Deplacement(float x, float y, float z);
//     void Rotation(float x, float y, float z);
//     void Scale(float s);
//     void Afficher();

private:
    string type;
    Model3D mesh;  // 3D objet here, but will be replace by more complet Objects
};
#endif