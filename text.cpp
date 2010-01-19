#include "text.h"

// for trace during test , to kept
#include <iostream>
using namespace std;
#include <string.h>
#include <stdlib.h>
#include <function.h>
#include <sstream>
//---------------------------------------------------------------
// Text
//---------------------------------------------------------------

Text::Text(string text, vect position,vect rotation,vect scale, float esp, vector<int> MChiffres, vector<int> MLettersa, TextStyle style)
{
    this->position=position;
    this->rotation=rotation;
    this->scale=scale;

    Actor car;
    
    if (style == CENTER) {
      position.x = position.x-((text.size()*esp)/(float)2);
    }
    else if (style == RIGHT) {
      position.x = position.x-(text.size()*esp);
    }
    
    vect p={position.x,position.y,position.z} ,r={rotation.x-90,rotation.y,rotation.z},s={scale.x,scale.y,scale.z};

    for (unsigned int i=0;i<text.size();i++) {
//         espace+=esp;
        //  (int)text[i] - (int)'0' --> on converti le caractere de la chaine en entier
      if  ((int)text[i] >= (int)'0' &&  (int)text[i] <= (int)'9') {
	p.x += esp;
        car = Actor(MChiffres[ (int)text[i] - (int)'0'], p, r, s);
        this->caract.push_back(car);
      }
      else if  ((int)text[i] >= (int)'a' &&  (int)text[i] <= (int)'e') {
	p.x += esp;
	car = Actor(MLettersa[ (int)text[i] - (int)'a'], p, r, s);
	this->caract.push_back(car);
      }
      else {
	cout << "Probleme, le caractere \"" << text[i] << "\" n'est pas trouvable dans la base " << endl;
      }
    }

}


//---------------------------------------------------------------
// Number
//---------------------------------------------------------------

Number::Number(int nombre, vect position,vect rotation,vect scale, float esp, vector<int> MChiffres, TextStyle style)
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
