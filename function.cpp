#include <cstdlib>
#include <iostream>
using namespace std;

float random(float min, float max)
{
     return ((max - min) * rand()/(float)RAND_MAX + min);
     
}