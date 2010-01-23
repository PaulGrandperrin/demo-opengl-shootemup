#ifndef FUNCTION_H_
#define FUNCTION_H_


#include <stdio.h>
#include <string>

#include <iostream>
using namespace std;

float random(float min, float max);
string entierToString(int nombre);
string charToString(char ca );


enum Etat
{
    STOP, GAME, MENU, PAUSE, NO
};

enum SwitchEtat
{
    NONE, TOGAME, TOMENU, TOPAUSE
};

enum TextStyle
{
    CENTER, LEFT, RIGHT
};

struct Point
{
	float x,y;
};

struct vect
{
    float x,y,z;
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

struct instance
{
  float x,y,z;
  float ax,ay,az;
  float sx,sy,sz;
  int idModel;
  //TODO ajouter coefficient de transparence et d'autres attribus
};

#endif