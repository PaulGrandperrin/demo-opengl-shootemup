#ifndef VIEWPORT_H_
#define VIEWPORT_H_
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <list>

#include "viewportComponent.h"

using namespace std;

class Viewport : public QWidget {

  public:
    Viewport();
    void selectNewPoint(Point2D * point);
    Point2D * pointInPosition(int x, int y); // Retourne le point present a la position (x,y) s'il y en a un, NULL sinon
    void addPoint(int x, int y, CurvePos pos);
    void enterTime(Point2D * point);
    bool isEmpty();
    inline list<Point2D> getPositions() {
      return points;
    }
  private:
    // Methods
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *);
    // Attributes
    list<Point2D> points;
    list<BezierCurve> curves;
    Point2D * selectedPoint;
    Point2D * movingPoint; // Point que l'on est en train de deplacer, NULL si aucun point en deplacement
};

#endif