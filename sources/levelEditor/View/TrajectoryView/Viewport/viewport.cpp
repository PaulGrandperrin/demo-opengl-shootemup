#include "viewport.h"
#include "viewportPainter.h"
#include "../../parameters.h"
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <sstream>
using namespace std;

///////////////////////////////
// VIEWPORT
///////////////////////////////

// Public methods

Viewport::Viewport() {
  this->setFixedSize(VIEW_WIDTH,VIEW_HEIGHT);
  selectedPoint = NULL; // Au debut, comme aucun point n'existe, aucun point n'est selectionne
  movingPoint = NULL;
}

void Viewport::selectNewPoint(Point2D * point) {
  // On deselectionne le point actuellement selectionne
  if(selectedPoint != NULL)
      selectedPoint->deselect();
  // Puis on en selectionne un autre
  point->select();
  selectedPoint = point;
}

Point2D * Viewport::pointInPosition(int x, int y) {
  list<Point2D>::iterator itp;
  // On boucle tant que le point courant n'est pas dans le "rayon" d'un autre point
  for(itp=points.begin(); itp!=points.end() && (x < ((*itp).x()-POINT_SIZE/2) || x > ((*itp).x()+POINT_SIZE/2) 
    || y < ((*itp).y()-POINT_SIZE/2) || y > ((*itp).y()+POINT_SIZE/2));itp++);
  if(itp!=points.end())
    return &(*itp);
  else {
    list<BezierCurve>::iterator itc;
    for(itc=curves.begin(); itc != curves.end() && (x < ((*itc).getControlPoint()->x()-POINT_SIZE/2) || x > ((*itc).getControlPoint()->x()+POINT_SIZE/2) 
    || y < ((*itc).getControlPoint()->y()-POINT_SIZE/2) || y > ((*itc).getControlPoint()->y()+POINT_SIZE/2));itc++);
    if(itc!=curves.end())
      return (*itc).getControlPoint();
    else
      return NULL;
  }
}

void Viewport::addPoint(int x, int y, CurvePos pos) {
  Point2D * second = NULL, * nextolast = NULL;
  if(pos == BEGIN) {
    second = &(points.front());
    points.push_front(Point2D(x,y));
    selectNewPoint(&(points.front()));
  } else {
    nextolast = &(points.back());
    points.push_back(Point2D(x,y));
    selectNewPoint(&(points.back()));
  }
  // Si plus d'un point sont crees, alors on peut creer une nouvelle courbe
  if(points.size() > 1) {
    if(pos == BEGIN)
      curves.push_back(BezierCurve(&(points.front()),second));
    else
      curves.push_back(BezierCurve(nextolast,&(points.back())));
  }
}

void Viewport::enterTime(Point2D * point) {
  double time, min_time = 0, max_time = 2147483647;
  list<Point2D>::iterator itp = points.begin();
  if(point != &(points.front())) {
    Point2D * previous = NULL;
    for(itp = points.begin(); itp != points.end() && &(*itp) != point; itp++)
      previous = &(*itp);
    min_time = previous->getTime().toDouble()+0.1;
  }
  if(point != &(points.back())) {
    itp++;
    max_time = (*itp).getTime().toDouble();
    if(max_time >= 0.1)
      max_time -= 0.1;
  }
  time = QInputDialog::getDouble(this, "Time", "Please enter the time you want to apply this position (in seconds)", min_time, min_time, max_time);
  ostringstream out;
  out << time;
  string text = out.str();
  point->setTime(QString(text.data()));
}

bool Viewport::isEmpty() {
  return points.size() == 0;
}

// Private methods

void Viewport::mousePressEvent(QMouseEvent * event) {
  int x = event->x();
  int y = event->y();
  Point2D * point = pointInPosition(x,y);
  if(event->button() == Qt::LeftButton) { // Clic gauche
    // Un point ne peut etre cree que s'il ne se superpose pas a un autre.
    // De plus, si des points sont presents dans le viewport, il faut que le point actuellement selectionne soit le premier point de la
    // trajectoire ou le dernier.
    if(point == NULL && (selectedPoint == &(points.front()) || selectedPoint == &(points.back()) || selectedPoint == NULL)) {
      if(selectedPoint == &(points.back())){
	addPoint(x,y,END);
	this->repaint();
	enterTime(&(points.back()));
      } else {
	addPoint(x,y,BEGIN);
	this->repaint();
	enterTime(&(points.front()));
      }
    }
  } else if(event->button() == Qt::RightButton) { // Clic droit
    if(point != NULL && !point->selected())
      selectNewPoint(point);
  } else if(event->button() == Qt::MidButton) { // Clic du milieu
    if(point != NULL && point->selected())
      movingPoint = point;
  }
  this->repaint();
}

void Viewport::mouseReleaseEvent(QMouseEvent * event) {
  if(event->button() == Qt::MidButton)
    movingPoint = NULL;
}

void Viewport::mouseMoveEvent(QMouseEvent * event) {
  if(movingPoint != NULL) {
    movingPoint->setX(event->x());
    movingPoint->setY(event->y());
    this->repaint();
  }
}

void Viewport::paintEvent(QPaintEvent *) { 
  ViewportPainter painter(width(),height(),this);
  // On dessine les courbes
  list<BezierCurve>::iterator itc;
  for(itc=curves.begin(); itc != curves.end(); itc++) {
    painter.drawBezierCurve(*itc);
  }
  // On dessine les points
  list<Point2D>::iterator itp;
  for(itp=points.begin(); itp!=points.end();itp++) {
    painter.drawPoint(*itp);
  }
  painter.drawHiddenArea();
  painter.end();
}