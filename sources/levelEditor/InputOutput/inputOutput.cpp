#include "inputOutput.h"
#include <sstream>

InputOutput::InputOutput() : traj_file("../../levels/traj_lvl_default.data"), enem_file("../../levels/enem_lvl_default.data") {
}

list<QString> InputOutput::getEnemiesInfos() {
  list<QString> enemies_list;
  enem_file.begin();
  while(!enem_file.isEnded()) {
    ostringstream out;
    string text;
    string name;
    int health = 0, damages =0, score=0, mask_radius=0;
    enem_file.read(name);
    enem_file.read(health);
    enem_file.read(damages);
    enem_file.read(score);
    enem_file.read(mask_radius);
    out << name << " (" << health << " HP, " <<  damages << " damages, " << score << " points, radius : " <<  ((float)mask_radius/1000) << ")" << endl;
    text = out.str();
    if(name != "")
      enemies_list.push_back(QString(text.data()));
  }
  return enemies_list;
}

void InputOutput::recordEnemy(QString model_name, int health, int damages, int score, double mask_radius) {
  enem_file.write(model_name.toStdString());
  enem_file.writeSpace();
  enem_file.write(health);
  enem_file.writeSpace();
  enem_file.write(damages);
  enem_file.writeSpace();
  enem_file.write(score);
  enem_file.writeSpace();
  enem_file.write(mask_radius*1000);
  enem_file.writeLine();
}

void InputOutput::recordTrajectory(vect initPos, int interval, vector<t_key_state> keyStates, list<int> recordNumbers) {
  traj_file.write(initPos);
  traj_file.writeLine();
  traj_file.write(interval);
  traj_file.writeLine();
  int size = keyStates.size();
  traj_file.write(size);
  traj_file.writeLine();
  vector<t_key_state>::iterator itk;
  for (itk = keyStates.begin(); itk != keyStates.end(); itk++)
  {
	traj_file.write(*itk);
	traj_file.writeLine();
  }
  size = recordNumbers.size();
  traj_file.write(size);
  traj_file.writeLine();
  list<int>::iterator iti;
  for (iti = recordNumbers.begin(); iti!= recordNumbers.end(); iti++)
  {
	  traj_file.write(*iti);
	  traj_file.writeLine();
  }
}