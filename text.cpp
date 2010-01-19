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

    size_t size = text.size() + 1;

    Actor car;
    float espace =0.0; // espace entre les caracteres
    
    if (style == CENTER) {
      position.x = position.x-((text.size()*esp)/(float)2);
    }
    else if (style == RIGHT) {
      position.x = position.x-(text.size()*esp);
    }

    for (unsigned int i=0;i<text.size();i++) {
        espace+=esp;
        //  (int)text[i] - (int)'0' --> on converti le caractere de la chaine en entier
      if  ((int)text[i] >= (int)'0' &&  (int)text[i] <= (int)'9') {
        car = Actor(MChiffres[ (int)text[i] - (int)'0'], {position.x+espace,position.y,position.z}, {rotation.x-90,rotation.y,rotation.z}, {scale.x,scale.y,scale.z});
        this->caract.push_back(car);
      }
      else if  ((int)text[i] >= (int)'a' &&  (int)text[i] <= (int)'e') {
	car = Actor(MLettersa[ (int)text[i] - (int)'a'], {position.x+espace,position.y,position.z}, {rotation.x-90,rotation.y,rotation.z}, {scale.x,scale.y,scale.z});
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
    
    size_t size = text.size() + 1;
    Actor car;
    float espace =0.0; // espace entre les caracteres

    for (unsigned int i=0;i<text.size();i++) {
      if  ((int)text[i] < (int)'0' ||  (int)text[i] > (int)'9') {
	cout << "Probleme, le caractere \"" << text[i] << "\" n'est pas un chiffre " << endl;
      }
      else {
        espace+=esp;
        //  (int)text[i] - (int)'0' --> on converti le caractere de la chaine en entier
        car = Actor(MChiffres[ (int)text[i] - (int)'0'], {position.x+espace,position.y,position.z}, {rotation.x-90,rotation.y,rotation.z}, {scale.x,scale.y,scale.z});
        this->caract.push_back(car);
      }
    }
}


void Number::update(int nombre, float esp, vector<int> MChiffres)
{
  // TODO a revoir, surment optimisation a faire !
    string text = entierToString(nombre);
    size_t size = text.size() + 1;
    Actor car;
    float espace =0.0; // espace entre les caracteres
    this->caract.clear();

    for (unsigned int i=0;i<text.size();i++) {
      if  ((int)text[i] < (int)'0' ||  (int)text[i] > (int)'9') {
	cout << "Probleme, le caractere \"" << text[i] << "\" n'est pas un chiffre " << endl;
      }
      else {
        espace+=esp;
        //  (int)text[i] - (int)'0' --> on converti le caractere de la chaine en entier
        car = Actor(MChiffres[ (int)text[i] - (int)'0'], {position.x+espace,position.y,position.z}, {rotation.x-90,rotation.y,rotation.z}, {scale.x,scale.y,scale.z});
        this->caract.push_back(car);
      }
    }
}
