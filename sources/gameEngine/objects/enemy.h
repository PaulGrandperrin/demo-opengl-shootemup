#ifndef ENEMY_H_
#define ENEMY_H_

#include "./actor.h"
#include "../../utilities.h"
#include <string>

using namespace std;

struct EnemyInfo {
    int idModel;
    int health;
    int damages;
    int score;
    float mask_radius;
};

class EnemyInfosFile {
public:
    EnemyInfosFile(string fileName = "levels/enem_lvl_default.data");
    ~EnemyInfosFile();
    void open(string fileName);
    inline void close() {file.close(); }
    bool isEnded();
    inline void begin() {file.seekg(ios_base::beg);} // Place le pointeur de lecture au debut du fichier
    inline void end() {file.seekp(ios_base::end);} // Place le pointeur d'ecriture en fin de fichier
    inline void write(string s) {file << s;} // Ecrit une chaine dans le fichier (sa taille puis la chaine)
    inline void write(int i) {file << i;}
    inline void write(float & f) {file << f;}
    inline void read(string & s) { file >> s;}
    inline void read(int & i) {file >> i;}
    inline void read(float & f) {file >> f;}
    inline void writeLine() {  file << endl;}
    inline void writeSpace() {  file << " ";}
    void enterInfos();
    void displayContent();
private:
    fstream file;
    string fileName;
};

#endif
