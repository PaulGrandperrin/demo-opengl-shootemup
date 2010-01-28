#include "viewportComponent.h"
#include <QDebug>

///////////////////////////////
// POINT
///////////////////////////////

Point2D::Point2D(int x, int y, QString time, bool selected) : QPoint(x,y) {
  this->time = time;
  _selected = selected;
}

///////////////////////////////
// BEZIERCURVE
///////////////////////////////

BezierCurve::BezierCurve(Point2D * beginPoint, Point2D * endPoint) {
  this->beginPoint = beginPoint;
  this->endPoint = endPoint;
  this->controlPoint = new Point2D(0.75 * (endPoint->x()-beginPoint->x()) + beginPoint->x(), 0.75 * (endPoint->y()-beginPoint->y()) + beginPoint->y(),"-1");
  /*this->controlPoint = new Point( (endPoint->x()-beginPoint->x())/(endPoint->getTime().toFloat()-beginPoint->getTime().toFloat()) , 
  (endPoint->y()-beginPoint->y())/(endPoint->getTime().toFloat()-beginPoint->getTime().toFloat()));*/
  qDebug() << "(" << controlPoint->x() << "," << controlPoint->y() << ")";
}