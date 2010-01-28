#include "viewportPainter.h"
#include "../../parameters.h"

ViewportPainter::ViewportPainter(int width,int height,QPaintDevice * device) : QPainter(device) {
  this->height = height;
  this->width = width;
  this->setRenderHint(QPainter::Antialiasing, true);
  this->setPen(Qt::DotLine);
  this->setBrush(QColor(255, 255, 255, 255));
  this->drawRect(HIDDEN_BORDER,HIDDEN_BORDER,width-2*HIDDEN_BORDER,height-2*HIDDEN_BORDER);
  this->setPen(Qt::SolidLine);
}

void ViewportPainter::drawHiddenArea() {
  this->setPen(Qt::DotLine);
  this->setBrush(QColor(0, 0, 0, 100));
  this->drawRect(0,0,HIDDEN_BORDER,height);
  this->drawRect(0,0,width,HIDDEN_BORDER);
  this->drawRect(width-HIDDEN_BORDER,0,HIDDEN_BORDER,height);
  this->drawRect(0,height-HIDDEN_BORDER,width,HIDDEN_BORDER);
}

void ViewportPainter::drawPoint(Point2D & point) {
    if(point.getTime() != "-1") {
      QString text("t = " + point.getTime());
      QRect rect(point.x()+TEXT_OFFSET_X, point.y()-TEXT_OFFSET_Y,10*text.length()+2*TEXT_MARGIN,15+2*TEXT_MARGIN);
      this->setBrush(QColor(255, 255, 255, 255));
      this->drawRect(rect);
      this->drawText(rect,Qt::AlignHCenter|Qt::AlignVCenter,text);
    }
    if(point.selected())
      this->setBrush(QColor(255, 0, 0, 255));
    else
      this->setBrush(QColor(255, 248, 133, 255));
    this->drawEllipse(point.x()-POINT_SIZE/2,point.y()-POINT_SIZE/2,POINT_SIZE,POINT_SIZE);
}

void ViewportPainter::drawBezierCurve(BezierCurve & curve) {
    Point2D * beginPoint = curve.getBeginPoint();
    Point2D * endPoint = curve.getEndPoint();
    Point2D * controlPoint = curve.getControlPoint();
    
    // Plus tard dessin de la courbe :
    // this->drawArc(beginPoint->x(),beginPoint->y(),endPoint->x()-beginPoint->x(),endPoint->y()-beginPoint->y(),0*16,360*16);
      
    this->drawLine(beginPoint->x(),beginPoint->y(),endPoint->x(),endPoint->y());
    
    // Dessin du vecteur
    /*this->setPen(QColor(255, 120, 0, 255));
    this->drawPoint(*controlPoint);
    this->drawLine(beginPoint->x(),beginPoint->y(),controlPoint->x(),controlPoint->y());
    // Dessiner la fleche du vecteur
    //this->drawLine(controlPoint->x(),controlPoint->y());
    //this->drawLine(controlPoint->x(),controlPoint->y());
    this->setPen(QColor(0, 0, 0, 255));*/
}