#include "./models.h"

#include <stdio.h>
#include <sstream>
#include <stdlib.h>



Models::Models(graphicEngine* GE) {
// l'ordre n'est pas sans importance !
    MSol=GE->loadModel("meshes/plan.obj","textures/sol2.png");
    for (int i=1; i<=3;i++) {
        MNuages.push_back(GE->loadModel("meshes/plan.obj","textures/nuage" + entierToString(i) + ".png"));
    }
    Mplayer=GE->loadModel("meshes/player.obj","textures/player.png");
    MbouletP=GE->loadModel("meshes/boulet.obj","textures/bouletPlayer.png");
    MbouletE=GE->loadModel("meshes/boulet.obj","textures/bouletEnemy.png");
    Mharpon=GE->loadModel("meshes/harpon.obj","textures/harpon.png");
    MBomb=GE->loadModel("meshes/bomb.obj","textures/bomb.png");
    MCursorPause=GE->loadModel("meshes/cursorPause.obj","textures/noir.png");
    MFondScore=GE->loadModel("meshes/plan.obj","textures/papyrus.png");
    MFondMenu=GE->loadModel("meshes/panneau.obj","textures/panneau.png");
    MPoint=GE->loadModel("meshes/ponctuation/point.obj","textures/noir.png");
    MDpoint=GE->loadModel("meshes/ponctuation/dpoint.obj","textures/noir.png");
    MPointEx=GE->loadModel("meshes/ponctuation/excl.obj","textures/noir.png");
    MPointInt=GE->loadModel("meshes/ponctuation/int.obj","textures/noir.png");
    MVirg=GE->loadModel("meshes/ponctuation/virg.obj","textures/noir.png");
    for (int i=0; i<=9; i++) {
        MChiffres.push_back(GE->loadModel("meshes/chiffres/" + entierToString(i) + ".obj","textures/noir.png"));
    }
    for (char c = 'A'; c<='Z'; c++) {
        MLettersM.push_back(GE->loadModel("meshes/letters/" + charToString(c) + ".obj","textures/noir.png"));
    }

    // Chargement des infos des ennemis
    // NOTE j'ai (normalement) fait en sorte qu'on n'ait pas à modifier le code si on rajoute un ennemi dans le fichier d'ennemis
    // TODO gerer plusieurs niveaux (2 fichiers par niveau : un "enem_lvl_<n°_du_niveau>.data" et un "traj_lvl_<n°_du_niveau>.data"
    // dans le dossier levels
    EnemyInfosFile eFile("levels/enem_lvl_default.data");
    if (eFile.isEnded()) {
        cout << "Enemies file not found !" << endl;
        exit(0);
    }
    string s;
    int h, idM;
    while (!eFile.isEnded()) {
        eFile.read(s);
        eFile.read(h);
        idM = GE->loadModel("meshes/"+s+".obj","textures/"+s+".png");
        EnemyInfo enemyInfo={idM,h};
        enemiesInfos.push_back(enemyInfo);
        cout << "Enemy infos : (idModel = " << idM << ", Health = " << h << ") ... Loaded" << endl;
    }
}


