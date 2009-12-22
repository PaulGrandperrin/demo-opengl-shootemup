#include <QtGui>
//#include "acteur.h"
#include "gameplay.h"
#include <iostream>
#include <stdio.h>

Application::Application()
{
// acteurs.NULL;
    addModelActeur("cube.obj"); // on creer les modele d'acteur
    addModelActeur("demon.obj"); // on creer les modele d'acteur
    addModelActeur("cow.obj"); // on creer les modele d'acteur
    addModelActeur("UFO.obj"); // on creer les modele d'acteur
    addModelActeur("tire2.obj"); // on creer les modele d'acteur
    addModelActeur("avion.obj"); // on creer les modele d'acteur
		
    joueur = Acteur(getModelActeur("demon.obj")); // on ajoute le joueur (il faudra creer une fonction appart)
   // addActeur("cow.obj",1,0,0); // on ajoute 3 acteur pour test
    addActeur("UFO.obj",1,1.5);
    //addActeur("avion.obj",-1,-1.5);
    addActeur("cube.obj");
// Acteur* acteur = new Acteur();
//   vector<Model3D>::iterator it;
//   for (it=modeles.begin(); it!= modeles.end(); it++)
//   {
//     if (QCoreApplication::arguments().count() > 1) // ????????????????????????????????
//         mesh.load(QCoreApplication::arguments().at(1).toStdString()); // ????????????????????????
//     else
//         mesh.load("meshes/" + type ); // on charge en memoir le demon (objet 3D a afficher dans la vue)
//   }
}

Application::~Application()
{
//     list<Acteur>::iterator it;
//     for (it=acteurs.begin(); it!= acteurs.end(); it++)
//     {
//         delete (it)->remove;
//     }
//     delete joueur;
}

void Application::Afficher()
{
    //qDebug()<< "0";
    joueur.Afficher();
    list<Acteur>::iterator it;
    for (it=acteurs.begin(); it!= acteurs.end(); it++)
    {
        it->Afficher();
    }

}

// void Application::SetActeur(Acteur* act)
// {
//   acteurs = act;
// }

Model3D* Application::getModelActeur(string type) // avec le nom du model, on recupere celui ci.
{
//     ModelActeur* modelActeur = NULL;
//     //ModelActeur* modelActeur2 = NULL;
//     //set<ModelActeur>* models;
//     //models* getModelActeurs();
//     vector<ModelActeur>::iterator it;
//     for (it=modeles.begin(); it!= modeles.end(); it++)
//     {
//         //modeles.begin()+it
//         //modelActeur2 = modeles.it();
//         if ((it)->getType() == type)
//             modelActeur = &(*it);
//     }
//     modeles.find(type);
// //   if (trouver)
    return &(modeles.find(type)->second);
//   else
//     return NULL;
}

void Application::addActeur(string type, float posx, float posy , float posz) // parametre pour test, a completer
{
    Acteur acteur = Acteur(getModelActeur(type),posx,posy,posz);
    acteurs.push_back(acteur);
}
void Application::addModelActeur(string type)
{ 	
//   cout << type << endl;
//             qDebug()<< "debut model add acteur";
    Model3D model3D = Model3D(); //Model3D(type);
//                 qDebug()<< "millieu model add acteur";

//     modeles.insert(type,model3D);
     modeles.insert( pair<string,Model3D>(type,(Model3D)model3D) );
//                  qDebug()<< "fin model add acteur";
}