#ifndef MODELS_H_
#define MODELS_H_


#include "graphicEngine.h"
#include "enemy.h"
#include "trajectory.h"

#include <vector>
#include <list>
#include <iostream>
using namespace std;



class Models {
public :
    Models() {};
    void chargerModels(graphicEngine* GE);
    inline int getMplayer() {
        return Mplayer;
    }
    inline int getMboulet() {
        return Mboulet;
    }
    inline int getMCursorPause() {
        return MCursorPause;
    }
    inline vector<int> getMChiffres() {
        return MChiffres;
    }
    vector<int> getMLettersM() {
        return MLettersM;
    }
    // obsolete pour le moment
//     vector<int> getMLettersm() {
//         return MLettersA;
//     }
    inline vector<EnemyInfo> getEnemiesInfos() {
      return enemiesInfos;
    }

//public : //TODO metre private probleme vector
    int Mplayer,Mboulet,MCursorPause;
    vector<int> MChiffres;
    vector<int> MLettersM;
//     vector<int> MLettersm; // vide pour l'instant, Majuscules
    vector<EnemyInfo> enemiesInfos;
};

#endif
