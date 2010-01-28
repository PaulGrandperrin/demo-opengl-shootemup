#ifndef INPUT_OUTPUT_H_
#define INPUT_OUTPUT_H_

#include "../../../sources/gameEngine/objects/enemy.h"
#include "../../../sources/gameEngine/objects/trajectory.h"
#include "../../../sources/utilities.h"
#include <QString>
#include <list>
using namespace std;

#define LEVELS_DIR ../../../levels/

class InputOutput {
  public:
    InputOutput();
    list<QString> getEnemiesInfos();
    void recordEnemy(QString model_name, int health, int damages, int score, double mask_radius);
    void recordTrajectory(vect initPos, int interval, vector<t_key_state> keyStates, list<int> recordNumbers);
  private:
    TrajectoryFile traj_file;
    EnemyInfosFile enem_file;
};

#endif