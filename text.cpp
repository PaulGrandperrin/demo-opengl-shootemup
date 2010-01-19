#include "text.h"

// for trace during test , to kept
#include <iostream>
using namespace std;
#include <string.h>
#include <stdlib.h>
#include <function.h>
#include <sstream>
#include <math.h>
//---------------------------------------------------------------
// Text
//---------------------------------------------------------------

Text::Text(vector<int> MChiffres, vector<int> MLettersa, string text, vect position,vect rotation,vect scale, float esp, TextStyle style)
{
    this->position=position;
    this->rotation=rotation;
    this->scale=scale;
    this->style=style;
    this->text=text;
    this->espace=esp;

    Actor car;
    float rayon= 0;
    
    if (style == CENTER) {
      rayon = -((text.size()*(esp * scale.x))/(float)2) - (esp * scale.x)/(float)2;
    }
    else if (style == RIGHT) {
      rayon = -(text.size()*esp*scale.x);
    }
    
    vect p={position.x,position.y,position.z} ,r={rotation.x-90,rotation.z,rotation.y},s={scale.x,scale.y,scale.z};
    
    for (unsigned int i=0;i<text.size();i++) {
      
	rayon += esp*scale.x;
	p.x = position.x + cos(rotation.y*3.1415/180) * rayon;
	p.z = position.z - sin(rotation.y*3.1415/180) * rayon;
        //  (int)text[i] - (int)'0' --> on converti le caractere de la chaine en entier
      if  ((int)text[i] >= (int)'0' &&  (int)text[i] <= (int)'9') {
        car = Actor(MChiffres[ (int)text[i] - (int)'0'], p, r, s);
        this->caract.push_back(car);
      }
      else if  ((int)text[i] >= (int)'a' &&  (int)text[i] <= (int)'e') {
	car = Actor(MLettersa[ (int)text[i] - (int)'a'], p, r, s);
	this->caract.push_back(car);
      }
      else {
	cout << "Probleme, le caractere \"" << text[i] << "\" n'est pas trouvable dans la base " << endl;
      }
    }

}

void Text::rotate(vect rot) {
    rotation.x+=rot.x;
    rotation.y+=rot.y;
    rotation.z+=rot.z;
    float rayon= 0;
    if (style == CENTER) {
      rayon = -((text.size()*espace*scale.x)/(float)2) - espace*scale.x/(float)2;
    }
    else if (style == RIGHT) {
      rayon = -(text.size()*espace*scale.x);
    }
   
    vector<Actor>::iterator itA;
    vect r={rotation.x-90,rotation.z,rotation.y}, p={position.x,position.y,position.z};
    
    for (itA=caract.begin(); itA!=caract.end(); itA++) {
	rayon += espace*scale.x;
      	p.x = position.x + cos(rotation.y*3.1415/180) * rayon;
	p.z = position.z - sin(rotation.y*3.1415/180) * rayon;
	itA->setRotation(r);
        itA->setTranslation(p);	
    }
}

void Text::scal(vect sca) {
    scale.x+=sca.x;
    scale.y+=sca.y;
    scale.z+=sca.z;
    if (scale.x < 0.1) { scale.x = 0.1; }
    if (scale.y < 0.1) { scale.y = 0.1; }
    if (scale.z < 0.1) { scale.z = 0.1; }
    if (scale.x > 10) { scale.x = 10; }
    if (scale.y > 10) { scale.y = 10; }
    if (scale.z > 10) { scale.z = 10; }
    
     float rayon= 0;
    if (style == CENTER) {
      rayon = -((text.size()*espace*scale.x)/(float)2) - espace*scale.x/(float)2;
    }
    else if (style == RIGHT) {
      rayon = -(text.size()*espace*scale.x);
    }
    
    vector<Actor>::iterator itA;
    vect p={position.x,position.y,position.z}, s={scale.x,scale.y,scale.z};
    
    for (itA=caract.begin(); itA!=caract.end(); itA++) {
	rayon += espace*scale.x;
      	p.x = position.x + cos(rotation.y*3.1415/180) * rayon;
	p.z = position.z - sin(rotation.y*3.1415/180) * rayon;
        itA->setTranslation(p);
	itA->setScale(s);
    }
}

void Text::translate(vect tr) {
    position.x+=tr.x;
    position.y+=tr.y;
    position.z+=tr.z;
    if (position.x < -NB_UNITY_WIDTH) { position.x = NB_UNITY_WIDTH; }
    if (position.z < -NB_UNITY_HEIGHT) { position.z = NB_UNITY_HEIGHT; }
    if (position.x > NB_UNITY_WIDTH) { position.x = -NB_UNITY_WIDTH; }
    if (position.z > NB_UNITY_HEIGHT) { position.z = -NB_UNITY_HEIGHT; }
    
     float rayon= 0;
    if (style == CENTER) {
      rayon = -((text.size()*espace*scale.x)/(float)2) - espace*scale.x/(float)2;
    }
    else if (style == RIGHT) {
      rayon = -(text.size()*espace*scale.x);
    }
    
    vector<Actor>::iterator itA;
    vect p={position.x,position.y,position.z};
    
    for (itA=caract.begin(); itA!=caract.end(); itA++) {
	rayon += espace*scale.x;
      	p.x = position.x + cos(rotation.y*3.1415/180) * rayon;
	p.z = position.z - sin(rotation.y*3.1415/180) * rayon;
        itA->setTranslation(p);
    }
}

//---------------------------------------------------------------
// Number
//---------------------------------------------------------------

Number::Number(vector<int> MChiffres, int nombre, vect position,vect rotation,vect scale, float esp, TextStyle style)
{
    this->position=position;
    this->rotation=rotation;
    this->scale=scale;


    string text = entierToString(nombre);

    Actor car;
    
    if (style == CENTER) {
      position.x = position.x-((text.size()*esp)/(float)2);
    }
    else if (style == RIGHT) {
      position.x = position.x-(text.size()*esp);
    }
    
    vect p={position.x,position.y,position.z} ,r={rotation.x-90,rotation.y,rotation.z},s={scale.x,scale.y,scale.z};
    vect p2={position.x,position.y,position.z};
    
    for (unsigned int i=0;i<text.size();i++) {
      if  ((int)text[i] < (int)'0' ||  (int)text[i] > (int)'9') {
	cout << "Probleme, le caractere \"" << text[i] << "\" n'est pas un chiffre " << endl;
      }
      else {
	p.x += esp;

        car = Actor(MChiffres[ (int)text[i] - (int)'0'], p2, r, s); //  (int)text[i] - (int)'0' --> on converti le caractere de la chaine en entier
        this->caract.push_back(car);
      }
    }
}


void Number::update(int nombre, float esp, vector<int> MChiffres)
{
  // TODO a revoir, surment optimisation a faire !
    string text = entierToString(nombre);
    Actor car;
    this->caract.clear();
    vect p={position.x,position.y,position.z} ,r={rotation.x-90,rotation.y,rotation.z},s={scale.x,scale.y,scale.z};

    for (unsigned int i=0;i<text.size();i++) {
      if  ((int)text[i] < (int)'0' ||  (int)text[i] > (int)'9') {
	cout << "Probleme, le caractere \"" << text[i] << "\" n'est pas un chiffre " << endl;
      }
      else {
	p.x += esp;
        //  (int)text[i] - (int)'0' --> on converti le caractere de la chaine en entier
        car = Actor(MChiffres[ (int)text[i] - (int)'0'], p, r, s);
        this->caract.push_back(car);
      }
    }
}
