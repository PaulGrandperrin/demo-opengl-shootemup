#ifndef VIEWQT_H_
#define VIEWQT_H_

#include "parameters.h" // general settings
#include "game.h" // general application, 
#include "keyboard.h"

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <QThread>
#include <QtGui> // for qDebug()

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

protected:
    void initializeGL(); // automatic
    void paintGL(); // automatic
    void resizeGL(int width, int height);  // automatic

private:
	Keyboard kb;
	ThreadQt thread;
    Game game;
	QTime time;
    int width,height;
};

#endif
