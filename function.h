#ifndef FUNCTION_H_
#define FUNCTION_H_


#include <stdio.h>
#include <string>
// #include "graphicEngine.h"

#include <iostream>
using namespace std;


float random(float min, float max);
string entierToString(int nombre);
string charToString(char ca );


enum Etat
{
    STOP, GAME, MENU, PAUSE, PASSAGEPAUSE, PASSAGEMENU
};

struct Point
{
	float x,y;
};



#endif