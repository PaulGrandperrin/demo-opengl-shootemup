#include "dataTranslator.h"
#include "../parameters.h"

#define OPENGL_SCREEN_RATIO 14

DataTranslator::DataTranslator() {
}

void DataTranslator::trajectoryQtToTrajectoryDatas(list<Point2D> pointsList, double interval, 
				       vect &initPos, int &interval_converted, vector<t_key_state> &keyStates) {
  Point2D firstPoint = pointsList.front();
  initPos.x = (((float)firstPoint.x()*OPENGL_SCREEN_RATIO)/(VIEW_WIDTH/2))-OPENGL_SCREEN_RATIO;
  initPos.y = 0;
  initPos.z = (((float)firstPoint.y()*OPENGL_SCREEN_RATIO)/(VIEW_WIDTH/2))-OPENGL_SCREEN_RATIO;
  
  interval_converted = interval*50;
  
  t_key_state ks = {0, 0, 0, 0, 0, 0, 0};
  list<Point2D>::iterator itp = pointsList.begin();
  Point2D * precPoint = &(*(itp));
  itp++;
  for(; itp != pointsList.end(); itp++) {
    ks.vx = (((((float)(*itp).x()*OPENGL_SCREEN_RATIO)/(VIEW_WIDTH/2))-OPENGL_SCREEN_RATIO) - ((((float)precPoint->x()*12)/(VIEW_WIDTH/2))-OPENGL_SCREEN_RATIO)) / ((*itp).getTime().toFloat() - precPoint->getTime().toFloat());
    ks.vz = (((((float)(*itp).y()*OPENGL_SCREEN_RATIO)/(VIEW_WIDTH/2))-OPENGL_SCREEN_RATIO) - ((((float)precPoint->y()*12)/(VIEW_WIDTH/2))-OPENGL_SCREEN_RATIO)) / ((*itp).getTime().toFloat() - precPoint->getTime().toFloat());
    ks.t = precPoint->getTime().toFloat()*1000;
    precPoint = &(*(itp));
    keyStates.push_back(ks);
  }
}