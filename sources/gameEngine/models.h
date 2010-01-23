#ifndef MODELS_H_
#define MODELS_H_


#include "../graphicEngine/graphicEngine.h"
#include "./objects/enemy.h"
#include "./objects/trajectory.h"
#include "../utilities.h"

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
    inline vector<int> getMLettersM() {
        return MLettersM;
    }
    inline vector<int> getMNuages() {
        return MNuages;
    }
    inline vector<int> getMSols() {
        return MSols;
    }
    inline vector<EnemyInfo> getEnemiesInfos() {
      return enemiesInfos;
    }

//public : //TODO metre private probleme vector
    int Mplayer,Mboulet,MCursorPause;
    vector<int> MChiffres;
    vector<int> MLettersM;
    vector<int> MNuages;
    vector<int> MSols;
    vector<EnemyInfo> enemiesInfos;
};

#endif
