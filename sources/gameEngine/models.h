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
    Models() {}
    Models(graphicEngine* GE); // on charge tout les models 3D

    inline int getMplayer() {
        return Mplayer;
    }
    inline int getMboulet() {
        return Mboulet;
    }
    inline int getMCursorPause() {
        return MCursorPause;
    }
    inline int getMFondScore() {
        return MFondScore;
    }
    inline int getMFondMenu() {
        return MFondMenu;
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
    inline int getMSol() {
        return MSol;
    }
    inline vector<EnemyInfo> getEnemiesInfos() {
        return enemiesInfos;
    }

//public : //TODO metre private probleme vector
    int Mplayer,Mboulet,MCursorPause,MFondScore,MFondMenu;
    vector<int> MChiffres;
    vector<int> MLettersM;
    vector<int> MNuages;
    int MSol;
    vector<EnemyInfo> enemiesInfos;
};

#endif
