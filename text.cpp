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

Text::Text(vector<int> MChiffres, vector<int> MLettersM, string text, vect position,vect rotation,vect scale, float esp, TextStyle style)
{
  // on sauvegarde certaines donne qui reservirons plutart
    this->position=position;
    this->rotation=rotation;
    this->scale=scale;
    this->style=style;
    this->text=text;
    this->espace=esp;

    Actor car;
    float rayon= 0;
    vect p={position.x,position.y,position.z} ,r={rotation.x-90,rotation.z,rotation.y},s={scale.x,scale.y,scale.z};
    vect sMajChi={s.x+0.4,s.y+0.4,s.z+0.4};

    if (style == CENTER) { // on adapte le rayon du text, qui changera pour chaque caract suivant ça place.
        rayon = -((text.size()*(esp * scale.x))/(float)2) - (esp * scale.x)/(float)2;
    }
    else if (style == RIGHT) {
        rayon = -(text.size()*esp*scale.x)-(esp * scale.x);
    }

// pour chaque caract de la chaine, on ajuste son rayon, calcule la rotation du text avec et creer le caracter avec une petite diference de taille si c'est une Maj ou Min
// si le caractere n'existe pas, un espace et inserer
    for (unsigned int i=0;i<text.size();i++) {
        rayon += esp*scale.x;
        p.x = position.x + cos(rotation.y*3.1415/180) * rayon;
        p.z = position.z - sin(rotation.y*3.1415/180) * rayon;
        //  (int)text[i] - (int)'0' --> on converti le caractere de la chaine en entier
        if  ((int)text[i] >= (int)'0' &&  (int)text[i] <= (int)'9') {
            car = Actor(MChiffres[ (int)text[i] - (int)'0'], p, r, sMajChi);
        }
        else if  ((int)text[i] >= (int)'a' &&  (int)text[i] <= (int)'z') {
            car = Actor(MLettersM[ (int)text[i] - (int)'a'], p, r, s);
        }
        else if ((int)text[i] >= (int)'A' &&  (int)text[i] <= (int)'Z') {
            car = Actor(MLettersM[ (int)text[i] - (int)'A'], p, r, sMajChi);
        }
        else {
	    car = Actor(-1, p, r, s);
        }
	this->caract.push_back(car); // meme si le car n'existe pas, on ajout un actor = -1
    }

}

void Text::rotate(vect rot) {
    rotation.x+=rot.x;
    rotation.y+=rot.y;
    rotation.z+=rot.z;
    float rayon= 0;
    vector<Actor>::iterator itA;
    vect r={rotation.x-90,rotation.z,rotation.y}, p={position.x,position.y,position.z};
    
    if (style == CENTER) {
        rayon = -((text.size()*espace*scale.x)/(float)2) - espace*scale.x/(float)2;
    }
    else if (style == RIGHT) {
        rayon = -(text.size()*espace*scale.x)-(espace * scale.x);
    }

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
    if (scale.x < 0.1) {
        scale.x = 0.1;
    }
    if (scale.y < 0.1) {
        scale.y = 0.1;
    }
    if (scale.z < 0.1) {
        scale.z = 0.1;
    }
    if (scale.x > 10) {
        scale.x = 10;
    }
    if (scale.y > 10) {
        scale.y = 10;
    }
    if (scale.z > 10) {
        scale.z = 10;
    }

    float rayon= 0;
    vector<Actor>::iterator itA;
    vect p={position.x,position.y,position.z}, s={scale.x,scale.y,scale.z};
    vect sMajChi={s.x+0.4,s.y+0.4,s.z+0.4};
    
    if (style == CENTER) {
        rayon = -((text.size()*espace*scale.x)/(float)2) - espace*scale.x/(float)2;
    }
    else if (style == RIGHT) {
        rayon = -(text.size()*espace*scale.x)-(espace * scale.x);
    }

    int i = 0;
    for (itA=caract.begin(); itA!=caract.end(); itA++) {
        rayon += espace*scale.x;
        p.x = position.x + cos(rotation.y*3.1415/180) * rayon;
        p.z = position.z - sin(rotation.y*3.1415/180) * rayon;
	itA->setTranslation(p);
	if ( ((int)text[i] >= (int)'A' &&  (int)text[i] <= (int)'Z') || ((int)text[i] >= (int)'0' &&  (int)text[i] <= (int)'9')) { // si on a une majuscule, c'est pas la meme taille
	    itA->setScale(sMajChi);
	}
	else {
	    itA->setScale(s);
	}
        i++;
    }
}

void Text::translate(vect tr) {
    position.x+=tr.x;
    position.y+=tr.y;
    position.z+=tr.z;
    if (position.x < -NB_UNITY_WIDTH) {
        position.x = NB_UNITY_WIDTH;
    }
    if (position.z < -NB_UNITY_HEIGHT) {
        position.z = NB_UNITY_HEIGHT;
    }
    if (position.x > NB_UNITY_WIDTH) {
        position.x = -NB_UNITY_WIDTH;
    }
    if (position.z > NB_UNITY_HEIGHT) {
        position.z = -NB_UNITY_HEIGHT;
    }

    float rayon= 0;
    vector<Actor>::iterator itA;
    vect p={position.x,position.y,position.z};
    
    if (style == CENTER) {
        rayon = -((text.size()*espace*scale.x)/(float)2) - espace*scale.x/(float)2;
    }
    else if (style == RIGHT) {
        rayon = -(text.size()*espace*scale.x)-(espace * scale.x);
    }

    for (itA=caract.begin(); itA!=caract.end(); itA++) {
        rayon += espace*scale.x;
        p.x = position.x + cos(rotation.y*3.1415/180) * rayon;
        p.z = position.z - sin(rotation.y*3.1415/180) * rayon;
	itA->setTranslation(p);
    }
}

Number::Number(vector<int> MChiffres, int number, vect position, vect rotation, vect scale, float esp, TextStyle style)
{
  // grosso modo meme procedure que Text (au dessus)
    string text = entierToString(number);
    
    this->position=position;
    this->rotation=rotation;
    this->scale=scale;
    this->style=style;
    this->text=text;
    this->espace=esp;

    Actor car;
    float rayon= 0;
    vect p={position.x,position.y,position.z} ,r={rotation.x-90,rotation.z,rotation.y},s={scale.x+0.4,scale.y+0.4,scale.z+0.4};
    
    if (style == CENTER) {
        rayon = -((text.size()*(esp * scale.x))/(float)2) - (esp * scale.x)/(float)2;
    }
    else if (style == RIGHT) {
        rayon = -(text.size()*esp*scale.x)-(esp * scale.x);
    }


    for (unsigned int i=0;i<text.size();i++) {

        rayon += esp*scale.x;
        p.x = position.x + cos(rotation.y*3.1415/180) * rayon;
        p.z = position.z - sin(rotation.y*3.1415/180) * rayon;
        //  (int)text[i] - (int)'0' --> on converti le caractere de la chaine en entier
        if  ((int)text[i] >= (int)'0' &&  (int)text[i] <= (int)'9') {
            car = Actor(MChiffres[ (int)text[i] - (int)'0'], p, r, s);
        }
        else {
	    car = Actor(-1, p, r, s);
        }
	this->caract.push_back(car); // meme si le car n'existe pas, on ajout un actor = -1
    }

}


void Number::update(vector<int> MChiffres, int number)
{
    // TODO a revoir, surment optimisation a faire !
    string text = entierToString(number);
    Actor car;
    float rayon= 0;
    vect p={position.x,position.y,position.z} ,r={rotation.x-90,rotation.y,rotation.z},s={scale.x+0.4,scale.y+0.4,scale.z+0.4};
    
    if (style == CENTER) {
        rayon = -((text.size()*(espace * scale.x))/(float)2) - (espace * scale.x)/(float)2;
    }
    else if (style == RIGHT) {
        rayon = -(text.size()*espace*scale.x)-(espace * scale.x);
    }
    this->caract.clear();

    for (unsigned int i=0;i<text.size();i++) {
	rayon += espace*scale.x;
        p.x = position.x + cos(rotation.y*3.1415/180) * rayon;
        p.z = position.z - sin(rotation.y*3.1415/180) * rayon;
        
	if  ((int)text[i] >= (int)'0' &&  (int)text[i] <= (int)'9') {
            car = Actor(MChiffres[ (int)text[i] - (int)'0'], p, r, s);
        }
        else {
	    car = Actor(-1, p, r, s);
        }
	this->caract.push_back(car); // meme si le car n'existe pas, on ajout un actor = -1
    }
}

Score::Score(vector<int> MChiffres, int number, vect position, vect rotation, vect scale, float esp, TextStyle style) : Number(MChiffres, number, position, rotation, scale, esp, style)
{
  this->score = number;
}

void Score::setScore(vector<int> MChiffres, int number) {
  score += number;
  Number::update(MChiffres,score);
}

void Score::initScore(vector<int> MChiffres, int number) {
  score = number;
  Number::update(MChiffres,score);
}

Health::Health(vector<int> MChiffres, int number, vect position, vect rotation, vect scale, float esp, TextStyle style) : Number(MChiffres, number, position, rotation, scale, esp, style)
{
  this->health = number;
}

void Health::setHealth(vector<int> MChiffres, int number) { //TODO a modifier
  this->health = number;
  Number::update(MChiffres,health);
}
