#include "./fond.h"

// for trace during test , to kept
#include <iostream>
using namespace std;
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <math.h>
//---------------------------------------------------------------
// Text
//---------------------------------------------------------------

Fond::Fond(vector<int> MNuages, int MSol,vect position,vect rotation,vect scale, vect vel)
{
    // on sauvegarde certaines donnees qui reservirons plutart
    this->position=position;
    this->rotation=rotation;
    this->scale=scale;
    this->velocity = vel;
    

    Actor plan; // le fond est composer de plan
    vect p={position.x,position.y,position.z} ,r={rotation.x,rotation.z,rotation.y},s={scale.x,scale.y,scale.z};
    for (unsigned type = 1; type <= 3; type ++) {
      float step = (48/NB_NUAGE_TYPE); // 48 : nb uniter sur Z pour placer un nuage
      float start = -24;
      for (unsigned int i=0;i<NB_NUAGE_TYPE;i++) { // on genere les nuages
	  p.x = random(-15,15);
	  p.z = random(start,start+step);
	  r.y = random(-180,180);
	  start +=step;
	  p.y +=0.1; // pas de superposition
	  plan = Actor(MNuages[type], p, r, s);
	  this->nuages.push_back(plan);
      }
    }
    p.y = position.y-2; // on descend le sol par rapporgt aux nuages
    s.x= 1.01; // et on agrandit les plan pour recouvrir une plan grande surface
    s.y= 1;
    s.z= 1.01;
    r.y = 0;
    for (int i=-18;i<=18;i = i +12) { // on genere le sol
      for (int j=-18;j<=18;j = j +12) {
        p.x = i;
        p.z = j;
         p.y +=0.001; // pas de superposition
        plan = Actor(MSol, p, r, s);
        this->sols.push_back(plan);
      }
    }

}

void Fond::update(float time) {

    vector<Actor>::iterator itA;
    vect p={position.x,position.y,position.z};

    // on update la position de chaque plan pour donne l'illusion au joueur d'avancer
    for (itA=nuages.begin(); itA!=nuages.end(); itA++) {
        p.z=itA->getPosition().z+time*velocity.z/1000;
        p.y=itA->getPosition().y;
        p.x=itA->getPosition().x;
        if (p.z > 24) { // si le plan est en bas, on le remonte (invisible sur l'ecran)
            p.x = random(-15,15);
            p.z = -24;
        }
        itA->setTranslation(p); // a la fin, on le translate
    }
    for (itA=sols.begin(); itA!=sols.end(); itA++) {
        p.z=itA->getPosition().z+time*velocity.z/2000;
        p.y=itA->getPosition().y;
        p.x=itA->getPosition().x;
        if (p.z > 24) { // si le plan est en bas, on le remonte (invisible sur l'ecran)
            p.z = -24;
        }
        itA->setTranslation(p); // a la fin, on le translate
    }

}
