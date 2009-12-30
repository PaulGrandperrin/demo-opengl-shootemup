#include <QtGlobal>
#include <cstdlib>
#include <iostream>
using namespace std;

float random(float min, float max, float time)
{
      qsrand( time ); // we certainly generate random number
     return ((max - min) * qrand()/(float)RAND_MAX + min);
}