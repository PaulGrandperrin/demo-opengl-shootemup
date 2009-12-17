#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <set>
#include <vector>
#include "acteur.h"
//#include "Model3D.h"
//#include "window.h"

class Application  // It's the widget which will contain openGl view
{
public:
    Application();
    ~Application();
    void Afficher(); // on affichera tout les objets
    vector<Acteur*> getActeurs() {
        return acteurs;
    }
    vector<ModelActeur>* getModelActeurs() {
        return &modeles;
    }
    ModelActeur* getModelActeur(string type);
    void addActeur(string type = TYPE_DEFAULT_MESH, float posx = POSX_DEFAULT_VAISSEAU, float posy = POSY_DEFAULT_VAISSEAU, float posz = POSZ_DEFAULT_VAISSEAU);
    void addModelActeur(string type = TYPE_DEFAULT_MESH); // pour creer les modeles des acteurs
    Acteur* getJoueur() {
        return joueur;
    }

private:
    vector<ModelActeur> modeles; // les modele 3d  (maillage)
    //  Window* myWindow; //??
    Acteur* joueur; // le joueur
    vector<Acteur*> acteurs;  // 3D objet here, but will be replace by more complet Objects
};

#endif
