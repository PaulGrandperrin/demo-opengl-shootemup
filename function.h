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
    STOP, GAME, MENU, PAUSE/*, PASSAGEPAUSE, PASSAGEMENU*/
};

enum TextStyle
{
    CENTER, LEFT, RIGHT
};

struct Point
{
	float x,y;
};


struct camera
{
  float eyex,eyey,eyez;
  float centerx,centery,centerz;
  float upx,upy,upz;
};

struct color
{
	float r,g,b,a;
};

struct lightVec
{
	float x,y,z;
	color al,dl,sl;
};


#endif