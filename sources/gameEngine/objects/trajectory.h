#ifndef TRAJECTORY_H_
#define TRAJECTORY_H_

#include <vector>
#include <list>
#include <string>
#include <fstream>

#include "./actor.h"
#include "../../utilities.h"
using namespace std;

#define MODIFY_ACC 0
#define MODIFY_VEL 1

// Structure to define changes on the trajectory
struct t_key_state {
    float ax, ay, az; // new acceleration coordinates
    float vx, vy, vz; // new velocity coordinates
    int t; // (relative) time when the modification has to be applied
};

class ActorEnemy;

class Trajectory {
public:
    Trajectory() {};
    Trajectory(vect initialPosition, int interval = 50);
    inline vect getInitialPosition() {
        return initialPosition;
    }
    inline int getInterval() {
        return interval;
    }
    inline vector<t_key_state> getKeyStates() {
        return keyStates;
    }
    inline list<int> getRecordNumbers() {
        return recordNumbers;
    }
    inline list<ActorEnemy> getEnemies() {
        return enemies;
    }
    inline void setEnemies(list<ActorEnemy> enemies) {
        this->enemies = enemies;
    }
    void addKeyState(t_key_state s);
    void addRecordNumber(int rec_num);
    void addEnemy(ActorEnemy e);
    void removeFirstRecordNumber();
private:
    vect initialPosition;
    int interval; // Intervalle de temps entre l'apparition de deux ennemis consecutifs (temp = X*20ms ex: 50*20 = 1s)
    vector<t_key_state> keyStates;
    list<int> recordNumbers; // NOTE : cet attribut permet de ne pas creer les instances d'ennemies des la creation de la trajectoire
    // C'est le "game" qui le fera en utilisant cette liste et son propre tableau d'infos ennemies
    // NOTE : ce tableau sera vidé une fois tous les ennemis créés
    list<ActorEnemy> enemies;
};

class TrajectoryFile {
public:
    TrajectoryFile(string fileName = "levels/traj_lvl_default.data");
    ~TrajectoryFile();
    void open(string fileName);
    inline void close() {file.close(); }
    bool isEnded();
    inline void begin() {file.seekg(ios_base::beg);} // Place le pointeur de lecture au debut du fichier
    inline void end() {file.seekp(ios_base::end);} // Place le pointeur d'ecriture en fin de fichier
    void write(t_key_state s); // Ecrit un etat cle dans le fichier (ecrit en fait ses attributs les uns à la suite des autres)
    inline void write(int i) {file << i;}
    inline void write(vect v) {file << v.x; writeSpace(); file << v.y; writeSpace(); file << v.z; }
    inline void writeLine() {  file << endl;}
    inline void writeSpace() {  file << " ";}
    inline void read(vect & v) {file >> v.x; file >> v.y; file >> v.z; }
    void read(t_key_state & s);
    void read(Trajectory & t);
    inline void read(int & i) {file >> i;}
    void read(list<Trajectory> & l);
    void enterInfos(); // Permet de saisir une nouvelle trajectoire et de l'ajouter au fichier
    void displayContent(); // affiche le contenu du fichier
private:
    fstream file;
    string fileName;
};

#endif
