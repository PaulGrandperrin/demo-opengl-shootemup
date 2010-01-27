#ifndef TEXT_H_
#define TEXT_H_

#include <fstream>
#include <string>
using namespace std;

#include "../../parameters.h"
#include "../../utilities.h"
#include "./actor.h"
#include "../models.h"

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
    Text( Models* models, string text, vect position,vect rotation,vect scale, float esp, TextStyle style);

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
    Models* models;
};

class Number : public Text
{
public :
    Number() {};
    Number(Models* models, int number, vect position,vect rotation,vect scale, float esp, TextStyle style);
    void update(int number);
};

class Score : public Number
{
public :
    Score() {};
    Score(Models* models, int number, string st, vect position,vect rotation,vect scale, float esp, TextStyle style);
    void setScore(int number);
    void initScore(int number);
    int getScore() {
        return score;
    }
    void getRender(vector<instance>* instances2D);

private:
    int score;
    Text tScore;
    Actor fondScore;
};

class Health : public Number
{
public :
    Health() {};
    Health(Models* models, int number, string st, vect position,vect rotation,vect scale, float esp, TextStyle style);
    void setHealth(int number);
    int getHealth() {
        return health;
    }
    void getRender(vector<instance>* instances2D);
    
private:
    int health;
    Text tHealth;
    Actor fondHealth;
};
#endif
