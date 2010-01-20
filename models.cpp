#include "models.h"
#include <stdio.h>
#include <sstream>
#include "function.h"



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
}


