#ifndef TEXT_H_
#define TEXT_H_

#include <fstream>
#include <string>
using namespace std;

#include "parameters.h"
#include "instance.h"
#include "actor.h"
#include "function.h"
#include <vector>

#include <QGLWidget>
#include <QString>
#include <QFont>
#include <QGLWidget>

/* Classe general qui contient tout les caractere possible (0.9,A.z) */


class Text 
{
public:
    Text() {};
    Text(string text, vect position,vect rotation,vect scale, float esp, vector<int> MChiffres, vector<int> MLettersa, TextStyle style);

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

class Number : public Text
{
  public :
    Number() {};
    Number(int nombre, vect position,vect rotation,vect scale, float esp, vector<int> MChiffres, TextStyle style);
    void update(int nombre, float esp, vector<int> MChiffres);
    
  private:
    int number;
};

#endif
