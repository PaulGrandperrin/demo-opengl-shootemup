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
    Text( vector<int> MChiffres, vector<int> MLettersa, string text, vect position,vect rotation,vect scale, float esp, TextStyle style);

    void update(string, vector<int>) {}


    inline vector<Actor> getText() {
        return caract;
    }

    inline vect getPosition() {
        return position;
    }
    void translate(vect t);
    void rotate(vect r);
    void scal(vect s);

protected:
    vect position;
    vect rotation;
    vect scale;
    vector<Actor> caract;
    string text;
    TextStyle style;
    float espace;
};

class Number : public Text
{
  public :
    Number() {};
    Number(vector<int> MChiffres, int nombre, vect position,vect rotation,vect scale, float esp, TextStyle style);
    void update(int nombre, float esp, vector<int> MChiffres);
    
  private:
    int number;
};

#endif
