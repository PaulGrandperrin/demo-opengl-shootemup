#ifndef TRAJECTORY_H_
#define TRAJECTORY_H_

#include <vector>
#include <list>
#include <string>
#include <fstream>
#include "actor.h"
#include "enemy.h"
using namespace std;

#define MODIFY_ACC 0
#define MODIFY_VEL 1

// Structure to define changes on the trajectory
struct t_key_state {
    short type; // Does it modify the velocity or the acceleration ?
    float x; // X new coordinate (velocity or acceleration)
    float y; // Y new coordinate (velocity or acceleration)
    float z; // Z new coordinate (velocity or acceleration)
    float t; // (relative) time when the modification has to be applied
};

class Trajectory {
  public:
    Trajectory() {};
    Trajectory(vect initialPosition, int interval = 50);
    inline vect getInitialPosition();
    inline int getInterval();
    inline vector<t_key_state> getKeyStates();
    inline list<int> getRecordNumbers();
    inline list<Enemy> getEnemies();
    void addKeyState(t_key_state s);
    void addRecordNumber(int rec_num);
    void addEnemy(Enemy e);
    void removeFirstRecordNumber();
  private:
    vect initialPosition;
    int interval; // Intervalle de temps entre l'apparition de deux ennemis consecutifs (temp = X*20ms ex: 50*20 = 1s)
    vector<t_key_state> keyStates;
    list<int> recordNumbers; // NOTE : cet attribut permet de ne pas creer les instances d'ennemies des la creation de la trajectoire
			       // C'est le "game" qui le fera en utilisant cette liste et son propre tableau d'infos ennemies
			       // NOTE : ce tableau sera vidé une fois tous les ennemis créés
    list<Enemy> enemies;
};

class TrajectoryFile {
  public:
    TrajectoryFile(string fileName = "levels/traj_lvl_default.data");
    ~TrajectoryFile();
    void open(string fileName);
    void close();
    bool isEnded();
    void begin(); // Place le pointeur de lecture au debut du fichier
    void end(); // Place le pointeur d'ecriture en fin de fichier
    void write(t_key_state s); // Ecrit un etat cle dans le fichier (ecrit en fait ses attributs les uns à la suite des autres)
    //void write(Trajectory t); // Ecrit une trajectoire dans le fichier sous la forme : intervalle_de_temps - nombre_keystates - [keystate_1..keystate_n] - 
				// nombre_ennemis - [Numero_enregistrement_ennemi_1..Numero_enregistrement_ennemi_n]
				// NOTE : Je pense pas qu'on s'en servira donc...
    void read(t_key_state & s);
    void read(Trajectory & t);
    void read(list<Trajectory> & l);
    void enterInfos(); // Permet de saisir une nouvelle trajectoire et de l'ajouter au fichier
    void displayContent(); // affiche le contenu du fichier
  private:
    fstream file;
    string fileName;
};

#endif