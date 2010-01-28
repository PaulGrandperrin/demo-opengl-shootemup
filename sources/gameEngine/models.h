#ifndef MODELS_H_
#define MODELS_H_


#include "../graphicEngine/graphicEngine.h"
#include "../soundEngine/soundEngine.h"
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
    inline int getMbouletE() {
        return MbouletE;
    }
    inline int getMbouletP() {
        return MbouletP;
    }
    inline int getMharpon() {
        return Mharpon;
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
    inline int getMDpoint() {
        return MDpoint;
    }
    inline int getMPoint() {
        return MPoint;
    }
    inline int getMPointEx() {
        return MPointEx;
    }
    inline int getMPointInt() {
        return MPointInt;
    }
    inline int getMVirg() {
	return MVirg;
    }
    inline int getMBomb() {
	return MBomb;
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
    int Mplayer,MbouletP, MbouletE,Mharpon,MCursorPause,MFondScore,MFondMenu, MBomb;
    int MDpoint, MPoint, MPointEx, MPointInt, MVirg;
    vector<int> MChiffres;
    vector<int> MLettersM;
    vector<int> MNuages;
    int MSol;
    vector<EnemyInfo> enemiesInfos;
};

#endif
