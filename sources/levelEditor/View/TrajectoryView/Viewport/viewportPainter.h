#ifndef VIEWPORT_PAINTER_H_
#define VIEWPORT_PAINTER_H_

#include <QPainter>

#include "viewportComponent.h"

class ViewportPainter : public QPainter {
  public:
    ViewportPainter(int width,int height,QPaintDevice * device);
    void drawHiddenArea();
    void drawPoint(Point2D & point);
    void drawBezierCurve(BezierCurve & curve);
  private:
    int width;
    int height;
};

#endif