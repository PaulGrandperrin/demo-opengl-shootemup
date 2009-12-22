#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <set>

#include <vector>

#include <list>
#include <map>
#include "acteur.h"
#include "model3D.h"
//#include "Model3D.h"
//#include "window.h"

class Application  // It's the widget which will contain openGl view
{
public:
    Application();
    ~Application();
    void Afficher(); // on affichera tout les objets
    list<Acteur>* getActeurs() {
        return &acteurs;
    }
    map<string,Model3D>* getModelActeurs() {
        return &modeles;
    }
    Model3D* getModelActeur(string type);
    void addActeur(string type = TYPE_DEFAULT_MESH, float posx = POSX_DEFAULT_VAISSEAU, float posy = POSY_DEFAULT_VAISSEAU, float posz = POSZ_DEFAULT_VAISSEAU);
    void addModelActeur(string type = TYPE_DEFAULT_MESH); // pour creer les modeles des acteurs
    Acteur* getJoueur() {
        return &joueur;
    }

private:
    map<string,Model3D> modeles; // les modele 3d  (maillage)
    //  Window* myWindow; //??
    Acteur joueur; // le joueur
    list<Acteur> acteurs;  // 3D objet here, but will be replace by more complet Objects
};

#endif
