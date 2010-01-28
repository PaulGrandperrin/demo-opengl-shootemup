#ifndef DATA_TRANSLATOR_H_
#define DATA_TRANSLATOR_H_

#include "../../../sources/gameEngine/objects/enemy.h"
#include "../../../sources/gameEngine/objects/trajectory.h"
#include "../../../sources/utilities.h"

#include "../View/TrajectoryView/Viewport/viewportComponent.h"

#include "inputOutput.h"
#include <QString>
#include <list>
using namespace std;

class DataTranslator {
  public:
    DataTranslator();
    void trajectoryQtToTrajectoryDatas(list<Point2D> pointsList, double interval, 
				       vect &initPos, int &interval_converted, vector<t_key_state> &keyStates);
};

#endif