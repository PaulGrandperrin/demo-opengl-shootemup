
#include <QtGui>
#include <stdio.h>
#include <iostream>
using namespace std;

float random(float min, float max)
{
      QTime time;    
      srand( time.elapsed() ); // we certainly generate random number
     return ((max - min) * rand()/(float)RAND_MAX + min);
}

bool etPair(float val)
{
  return ((int)(val*10) % 2) == 0;
}