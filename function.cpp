#include <cstdlib>
#include <iostream>
#include <sstream>
// #include "function.h"

using namespace std;


float random(float min, float max)
{
    return ((max - min) * rand()/(float)RAND_MAX + min);

}

string entierToString(int nombre) {
    ostringstream oss;
    string buffer;
    oss << nombre; // convertion de entier to string
    buffer = oss.str();
    return buffer;
}
// NOTE, ce ne sont pas les meme fonctions
string charToString(char ca )
{
    // utiliser un flux de sortie pour créer la chaîne
    std::ostringstream oss;
    // écrire la valeur dans le flux
    oss << ca;
    // renvoyer une string
    return oss.str();
}
