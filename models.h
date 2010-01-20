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
    vector<int> getMLettersM() {
        return MLettersM;
    }
    // obsolete pour le moment
//     vector<int> getMLettersm() {
//         return MLettersA;
//     }

//public : //TODO metre private probleme vector
    int Mplayer,Mboulet,MCursorPause;
    vector<int> MChiffres;
    vector<int> MLettersM;
//     vector<int> MLettersm; // vide pour l'instant, Majuscules
};

#endif
