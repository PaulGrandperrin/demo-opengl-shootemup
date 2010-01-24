#include <QApplication>
#include "./qt/viewQt.h"
#include "./parameters.h"

// for trace during test , to kept
#include <iostream>
using namespace std;

Parameters *parametre; // les parametres sont defini en globaux pour facililter l'accer !



int main(int argc, char *argv[])
{
    parametre = new Parameters(); // initialisation de parametres
    QApplication app(argc, argv); // creating of the Qt application
    ViewOpenGl window;	//Qt window (window.h) It will This Win
    window.show(); // show the Shump window
    return app.exec(); // TODO delete parametre
}
