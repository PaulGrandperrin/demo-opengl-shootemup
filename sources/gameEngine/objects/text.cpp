#include "./text.h"

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

Text::Text(Models* models, string text, vect position,vect rotation,vect scale, float esp, TextStyle style)
{
    // on sauvegarde certaines donne qui reservirons plutart
    this->position=position;
    this->rotation=rotation;
    this->scale=scale;
    this->style=style;
    this->text=text;
    this->espace=esp;
    this->models = models;

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
            car = Actor(models->getMChiffres()[ (int)text[i] - (int)'0'], p, r, sMajChi);
        }
        else if  ((int)text[i] >= (int)'a' &&  (int)text[i] <= (int)'z') {
            car = Actor(models->getMLettersM()[ (int)text[i] - (int)'a'], p, r, s);
        }
        else if ((int)text[i] >= (int)'A' &&  (int)text[i] <= (int)'Z') {
            car = Actor(models->getMLettersM()[ (int)text[i] - (int)'A'], p, r, sMajChi);
        }
	else if (text[i] == '.') { car = Actor(models->getMPoint(), p, r, s); }
	else if (text[i] == ':') { car = Actor(models->getMDpoint(), p, r, s); }
	else if (text[i] == '!') { car = Actor(models->getMPointEx(), p, r, s); }
	else if (text[i] == '?') { car = Actor(models->getMPointInt(), p, r, s); }
	else if (text[i] == '.') { car = Actor(models->getMVirg(), p, r, s); }
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

Number::Number(Models* models, int number, vect position, vect rotation, vect scale, float esp, TextStyle style)
{
    // grosso modo meme procedure que Text (au dessus)
    string text = entierToString(number);

    this->position=position;
    this->rotation=rotation;
    this->scale=scale;
    this->style=style;
    this->text=text;
    this->espace=esp;
    this->models = models;

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
            car = Actor(models->getMChiffres()[ (int)text[i] - (int)'0'], p, r, s);
        }
        else {
            car = Actor(-1, p, r, s);
        }
        this->caract.push_back(car); // meme si le car n'existe pas, on ajout un actor = -1
    }

}


void Number::update(int number)
{
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
            car = Actor(models->getMChiffres()[ (int)text[i] - (int)'0'], p, r, s);
        }
        else {
            car = Actor(-1, p, r, s);
        }
        this->caract.push_back(car); // meme si le car n'existe pas, on ajout un actor = -1
    }
}

Score::Score(Models* models, int number, string st, vect position, vect rotation, vect scale, float esp, TextStyle style) : Number(models, number, position, rotation, scale, esp, style)
{
    this->score = number;
      
    vect p=position, r= rotation, s=scale;
    p.z +=-1;
    tScore = Text(models, st, p, r, s, 0.6, style); // test du text, pour l'instant "abcde"
    
    p.z +=0.8; p.x += 0.8;
    s.x -= 0.1; s.z-=0.02;
    fondScore = Actor(models->getMFondScore(), p, r, s);
}

void Score::setScore(int number) {
    score += number;
    Number::update(score);
}

void Score::initScore( int number) {
    score = number;
    Number::update(score);
}

void Score::getRender(vector<instance>* instances2D) {
    vector<Actor> vActor;
    vector<Actor>::iterator itA;
    
    instances2D->push_back(fondScore.getInstance());
    for (itA=caract.begin(); itA!=caract.end(); itA++) {
	instances2D->push_back(itA->getInstance());
    }
    vActor = tScore.getText();
    for (itA=vActor.begin(); itA!=vActor.end(); itA++) {
	instances2D->push_back(itA->getInstance());
    }
}

Health::Health(Models* models, int number, string st, vect position, vect rotation, vect scale, float esp, TextStyle style) : Number(models, number, position, rotation, scale, esp, style)
{
    this->health = number;
    vect p=position, r= rotation, s=scale;
    p.z +=-1;
    tHealth = Text(models, st, p, r, s, 0.6, style); // test du text, pour l'instant "abcde"
    
    p.z +=0.8; p.x += -0.8;
    s.x -= 0.1; s.z-=0.02;
    fondHealth = Actor(models->getMFondScore(), p, r, s);
}

void Health::setHealth(int number) { //TODO a modifier
    this->health = number;
    Number::update(health);
}

void Health::getRender(vector<instance>* instances2D) {
    vector<Actor> vActor;
    vector<Actor>::iterator itA;
    
    instances2D->push_back(fondHealth.getInstance());
    for (itA=caract.begin(); itA!=caract.end(); itA++) {
	instances2D->push_back(itA->getInstance());
    }
    vActor = tHealth.getText();
    for (itA=vActor.begin(); itA!=vActor.end(); itA++) {
	instances2D->push_back(itA->getInstance());
    }
}
