#ifndef ENEMY_H_
#define ENEMY_H_

#include "./actor.h"
#include "../../utilities.h"
#include <string>

using namespace std;

struct EnemyInfo {
    int idModel;
    int health;
};

class EnemyInfosFile {
public:
    EnemyInfosFile(string fileName = "levels/enem_lvl_default.data");
    ~EnemyInfosFile();
    void open(string fileName);
    void close();
    bool isEnded();
    void begin(); // Place le pointeur de lecture au debut du fichier
    void end(); // Place le pointeur d'ecriture en fin de fichier
    void write(string s); // Ecrit une chaine dans le fichier (sa taille puis la chaine)
    void write(int i);
    void read(string & s);
    void read(int & i);
    void enterInfos();
    void displayContent();
private:
    fstream file;
    string fileName;
};

#endif
