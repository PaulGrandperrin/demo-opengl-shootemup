#ifndef VIEWQT_H_
#define VIEWQT_H_

#include "actor.h" // for the viewOpenGl
#include "parameters.h" // general settings
#include "game.h" // general application, 
#include "keyboard.h"

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <QThread>
#include <QtGui> // for qDebug()




class ViewOpenGl : public QGLWidget // It's the widget which will contain openGl view
{
    Q_OBJECT

public:
    ViewOpenGl(QWidget *parent = 0);
    ~ViewOpenGl();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void setGame(Game* app); // need for display openGl
    inline void updateViewOpengl() { // called with the Update function in Window (Thread)
        updateGL(); //display view
    }

protected:
    void initializeGL(); // automatic
    void paintGL(); // automatic (updateGL())
    void resizeGL(int width, int height);  // automatic

private:
    Game* pGame; // need for display openGl -> pGame->getPlayer->display
    int width,height; //size of OpenGl view == size of window

};



class Window: public QWidget
{
    Q_OBJECT
public:
    Window();
    ~Window();

private:
    Keyboard kb; // keyboard management
    Game game; // game management
    ViewOpenGl* viewOpenGl; // view management
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void checkKeyboard(); //action to do with key(s) activate
    void gameManagement(); //score, life management, enemies ...

private slots: // function called by threadQt every 20ms.
    void update() { // update every thing in game
        checkKeyboard(); // Check action of the gamer
        game.manager(); // brain
        viewOpenGl->updateViewOpengl(); // display
    }
    void closeApp() { // after self murder, thread send a signal to kill application
        close();
    }

signals:
    void killThread(); // before kill application, we need to kill timer, it resend a signal when it will be done
};




class ThreadQt : public QThread
{
    Q_OBJECT
public:
    ThreadQt();
    void run(); // what the thread must do
    void setDisplayWidget(Window* displayWidget); // connection

private:
    bool running; // = true while game run.

private slots:
    void selfKillThread(); // gamer want to quit, we need to kill thread

signals:
    void updateGame(/* you can put the resulting data */); // update general game.
    void closeApp(/* you can put the resulting data */); // just before self-murder
};

#endif
