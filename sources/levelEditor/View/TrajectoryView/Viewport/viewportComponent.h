#ifndef VIEWPORT_COMPONENT_H_
#define VIEWPORT_COMPONENT_H_

#include <QPoint>
#include <QString>

enum CurvePos{BEGIN,END};

class Point2D : public QPoint {
  public:
    Point2D(int x, int y, QString time = "0", bool selected = false);
    inline QString getTime() {
      return time;
    }
    inline void setTime(QString time) {
      this->time = time;
    }
    inline bool selected() {
      return _selected;
    }
    inline void select() {
      _selected = true;
    }
    inline void deselect() {
      _selected = false;
    }
  private:
    QString time;
    bool _selected;
};

class BezierCurve {
  public:
    BezierCurve(Point2D * beginPoint, Point2D * endPoint);
    inline Point2D * getBeginPoint() {
      return beginPoint;
    }
    inline Point2D * getEndPoint() {
      return endPoint;
    }
    inline Point2D * getControlPoint() {
      return controlPoint;
    }
  private:
    Point2D * beginPoint;
    Point2D * endPoint;
    Point2D * controlPoint;
};

#endif