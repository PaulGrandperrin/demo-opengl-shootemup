#ifndef TEXT_H_
#define TEXT_H_

#include <fstream>
#include <string>
using namespace std;

#include "parameters.h"
#include "instance.h"
#include "actor.h"
#include <vector>

/* Classe general qui contient tout les caractere possible (0.9,A.z) */


class Text
{
public:
    Text() {};
    Text(string text, vect position,vect rotation,vect scale, float esp, vector<int> MChiffres, vector<int> MLettersa);

    void update(string, vector<int>) {}


    inline vector<Actor> getText() {
        return caract;
    }

    inline vect getPosition() {
        return position;
    }
    inline void translate(vect t) {
        position.x+=t.x;
        position.y+=t.y;
        position.z+=t.z;
    }
    inline void rotate(vect r) {
        rotation.x+=r.x;
        rotation.y+=r.y;
        rotation.z+=r.z;
    }

protected:
    vect position;
    vect rotation;
    vect scale;
    vector<Actor> caract;
};

class Chiffre : public Text
{
  public :
    Chiffre() {};
    Chiffre(int nombre, vect position,vect rotation,vect scale, float esp, vector<int> MChiffres);
    void update(int nombre, float esp, vector<int> MChiffres);
};

#endif
