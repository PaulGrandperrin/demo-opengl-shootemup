#ifndef MODELS_H_
#define MODELS_H_


#include "graphicEngine.h"

#include <vector>
#include <iostream>
using namespace std;



class Models {
public :
    Models() {};
    void chargerModels(graphicEngine* GE);
    int getMplayer() {
        return Mplayer;
    }
    int getMboulet() {
        return Mboulet;
    }
    int getMCursorPause() {
        return MCursorPause;
    }
    vector<int> getMChiffres() {
        return MChiffres;
    }
    vector<int> getMLettersa() {
        return MLettersa;
    }
    vector<int> getMLettersA() {
        return MLettersA;
    }

//public : //TODO metre private probleme vector
    int Mplayer,Mboulet,MCursorPause;
    vector<int> MChiffres;
    vector<int> MLettersa;
    vector<int> MLettersA; // vide pour l'instant, Majuscules
};

#endif
