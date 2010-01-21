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
#include <iostream>
/* Classe general qui contient tout les caractere possible (0.9,A.z) */


class Text 
{
public:
    Text() {};
    Text( vector<int> MChiffres, vector<int> MLettersM, string text, vect position,vect rotation,vect scale, float esp, TextStyle style);

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
    
    inline Point getXY() {
	Point p;
	p.x=((caract.size())*(espace * scale.x))/2;
	p.y=scale.z/2;
	return p;
    }
       
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
    Number(vector<int> MChiffres, int number, vect position,vect rotation,vect scale, float esp, TextStyle style);
    void update(vector<int> MChiffres, int number);
};

class Score : public Number
{
  public :
    Score() {};
    Score(vector<int> MChiffres, int number, vect position,vect rotation,vect scale, float esp, TextStyle style);
    void setScore(vector<int> MChiffres, int number);
    void initScore(vector<int> MChiffres, int number);
    int getScore() { return score; }
    
  private:
    int score;
};

class Health : public Number
{
  public :
    Health() {};
    Health(vector<int> MChiffres, int number, vect position,vect rotation,vect scale, float esp, TextStyle style);
    void setHealth(vector<int> MChiffres, int number);
    int getHealth() { return health; }
    
  private:
    int health;
};
#endif
