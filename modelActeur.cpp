#include "acteur.h"
#include <QApplication>
#include <QtGui>
//#include <QtOpenGL>
#include <QThread>
//#include <math.h>

#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------
//Object
//-------------------------------------------------------------------------------


ModelActeur::ModelActeur(string type)
{
    this->type=type; // petite mise en forme
//     if (QCoreApplication::arguments().count() > 1) // ????????????????????????????????
//         mesh.load(QCoreApplication::arguments().at(1).toStdString()); // ????????????????????????
//     else
//         mesh.load("meshes/" + type ); // on charge en memoir le demon (objet 3D a afficher dans la vue)

}

ModelActeur::~ModelActeur() { }
