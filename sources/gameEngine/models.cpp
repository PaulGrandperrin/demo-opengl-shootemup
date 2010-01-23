#include "./models.h"

#include <stdio.h>
#include <sstream>
#include <stdlib.h>



void Models::chargerModels(graphicEngine* GE) {
    Mplayer=GE->loadModel("meshes/player.obj","textures/player.png");
    Mboulet=GE->loadModel("meshes/boulet.obj","textures/boulet.png");
    MCursorPause=GE->loadModel("meshes/cursorPause.obj","textures/noir.png");
    for (int i=0; i<=9; i++) {
        MChiffres.push_back(GE->loadModel("meshes/chiffres/" + entierToString(i) + ".obj","textures/noir.png"));
    }
    for (char c = 'A'; c<='Z'; c++) {
	MLettersM.push_back(GE->loadModel("meshes/letters/" + charToString(c) + ".obj","textures/noir.png"));
    }
    for (int i=1; i<=2;i++) {
	MNuages.push_back(GE->loadModel("meshes/plan.obj","textures/nuage" + entierToString(i) + ".png"));
    }
    for (int i=1; i<=2;i++) {
	MSols.push_back(GE->loadModel("meshes/plan.obj","textures/sol" + entierToString(i) + ".png"));
    }
    
    // Chargement des infos des ennemis
    // NOTE j'ai (normalement) fait en sorte qu'on n'ait pas à modifier le code si on rajoute un ennemi dans le fichier d'ennemis
    // TODO gerer plusieurs niveaux (2 fichiers par niveau : un "enem_lvl_<n°_du_niveau>.data" et un "traj_lvl_<n°_du_niveau>.data"
    // dans le dossier levels
    EnemyInfosFile eFile("levels/enem_lvl_default.data");
    if(eFile.isEnded()) {
      cout << "Enemies file not found !" << endl;
      exit(0);
    }
    string s;
    int h, idM;
    while(!eFile.isEnded()) {
	eFile.read(s);
	eFile.read(h);
	idM = GE->loadModel("meshes/"+s+".obj","textures/"+s+".png");
	EnemyInfo enemyInfo={idM,h};
	enemiesInfos.push_back(enemyInfo);
	cout << "Enemy infos : (idModel = " << idM << ", Health = " << h << ") ... Loaded" << endl;
    }
}


