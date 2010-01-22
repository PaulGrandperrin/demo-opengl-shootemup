#ifndef VIEWQT_H_
#define VIEWQT_H_


#include "../utilities.h"
#include "../gameEngine/game.h"
#include "./inputDevice.h"

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <QThread>
#include <QTime>
// // for qDebug()

using namespace std;

class ThreadQt : public QThread
{
    Q_OBJECT
public:
    void run();
    void stop();
private:
    bool running;
signals:
    void updateGame(/* you can put the resulting data */);
};

class ViewOpenGl : public QGLWidget
{
    Q_OBJECT

public:
    ViewOpenGl(QWidget *parent = 0);
    ~ViewOpenGl();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);

protected:
    void initializeGL(); // automatic
    void paintGL(); // automatic
    void resizeGL(int width, int height);  // automatic

private:
    Keyboard kb;
    Mouse mouse;
    ThreadQt thread;
    Game game;
    QTime time;
    int width,height;
    bool passageScreen;
};

#endif
