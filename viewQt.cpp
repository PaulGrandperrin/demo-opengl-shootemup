#include "viewQt.h"

#include <QApplication>
#include <QtOpenGL>
#include <QThread>
#include <math.h>

// for trace during test , to kept
#include <iostream>
using namespace std;


//-------------------------------------------------------------------------------
//GLWidget
//-------------------------------------------------------------------------------

ViewOpenGl::ViewOpenGl( QWidget *parent) : QGLWidget(parent)
{
}

ViewOpenGl::~ViewOpenGl()
{
    makeCurrent(); //Context openGl
}

void ViewOpenGl::setGame(Game* game)
{
    pGame = game; // easier for display
}


QSize ViewOpenGl::minimumSizeHint() const
{
    return QSize(TAILLE_MIN_X,TAILLE_MIN_Y); // minimal size of window
}

QSize ViewOpenGl::sizeHint() const
{
    return QSize(TAILLE_DEFAULT_X,TAILLE_DEFAULT_Y); // size of window
}


void ViewOpenGl::initializeGL()
{
    glClearColor ( 1,1,1,0 );
    glEnable (GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    
    //load each model in this function, I don't know why
    
    map<string,Model3D>::iterator it;
    map<string,Model3D>* models = pGame->getModels();

    for (it=models->begin(); it!= models->end(); it++)
    {
        if (QCoreApplication::arguments().count() > 1) // ????????????????????????????????
            (it)->second.load(QCoreApplication::arguments().at(1).toStdString()); // ????????????????????????
        else
            (it)->second.load("meshes/" +  (it)->first );
    }
}

void ViewOpenGl::paintGL() // update viewOpenGl
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    gluLookAt(0,0,5,0,0,0,0,1,0);
    pGame->display(); // display every actor
    glFlush();
}

void ViewOpenGl::resizeGL(int width, int height) // pour redimenssioner la vue (garder les proportions ...)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        45,
        width/(float)height,
        0.1,
        100
    );
    glMatrixMode(GL_MODELVIEW);
    this->width=width;
    this->height=height;
}



//-------------------------------------------------------------------------------
//Window
//-------------------------------------------------------------------------------

Window::Window() : kb(), game() // Window has keyboard and Game
{
    viewOpenGl= new ViewOpenGl(this); // Qt widet, here openglview
    viewOpenGl->setGame(&game);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(viewOpenGl);
    setLayout(mainLayout);
    
    setWindowTitle(tr("Shmup"));
    grabKeyboard();
    
    application.setDisplayWidget(this); //Display the thread with Window widget
    application.start(); // Start the Thread, run() call to update function in Window
}

Window::~Window()
{
    application.stop();
    application.wait();
    delete viewOpenGl;
}


void Window::keyPressEvent(QKeyEvent * event) // action on keyboard
{
    kb.updateEvent(event->key(),true); // update tab state of key
}

void Window::keyReleaseEvent(QKeyEvent * event)
{
    kb.updateEvent(event->key(),false); // update tab state of key
}

void Window::checkKeyboard()
{
    if (kb.hotKey(T_ECHAP))
    {
        close();
    }
    if (kb.hotKey(T_CTRL))
    {
        if (kb.hotKey(T_GAUCHE)) //zoom -
            game.getPlayer()->scale(-0.02);
        if (kb.hotKey(T_DROITE)) // zoom +
            game.getPlayer()->scale(0.02);
        if (kb.hotKey(T_HAUT)) // +z
            game.getPlayer()->translate(0.0,0.0,0.1);
        if (kb.hotKey(T_BAS)) // -z
            game.getPlayer()->translate(0.0,0.0,-0.1);
    }
    else if (kb.hotKey(T_SHIFT))
    {
        if (kb.hotKey(T_GAUCHE)) //rot - z
            game.getPlayer()->rotation(0.0,0.0,-1);
        if (kb.hotKey(T_DROITE)) // rot - z
            game.getPlayer()->rotation(0.1,0.0,1);
        if (kb.hotKey(T_HAUT)) // rot +x
            game.getPlayer()->rotation(-1,0.0,0.0);
        if (kb.hotKey(T_BAS)) // rot -x
            game.getPlayer()->rotation(1,0.0,0.0);
    }
    else
    {
        if (kb.hotKey(T_GAUCHE)) // -x
            game.getPlayer()->translate(-0.05,0.0,0.0);
        if (kb.hotKey(T_DROITE)) // +x
            game.getPlayer()->translate(0.05,0.0,0.0);
        if (kb.hotKey(T_HAUT)) // +y
            game.getPlayer()->translate(0.0,0.05,0.0);
        if (kb.hotKey(T_BAS)) // -y
            game.getPlayer()->translate(0.0,-0.05,0.0);
	if (kb.hotKey(T_SPACE)) // add enemy (currently)
//             game.addActeur("avion.obj",0.1,game.getPlayer()->getPosition().x,game.getPlayer()->getPosition().y,game.getPlayer()->getPosition().z,0,0,0,0,1,0);
	    game.addTire();
    }
}

//-------------------------------------------------------------------------------
//ThApplication : thread de l'application
//-------------------------------------------------------------------------------

ThreadQt::ThreadQt()
{
}

void ThreadQt::run() // le coeur du thread
{

    running=true;
    while (running) //tant de l'application n'a pas demander a s'arreter
    {
        msleep(20); // frequence : 50hz
        emit updateGame(); // on envois un signal au a la fonction Update()
    }
}

void ThreadQt::stop()
{
    running=false; // on arrete la boucle du thread
}

void ThreadQt::setDisplayWidget(Window* displayWidget) // on defini le thread
{
    connect(this, SIGNAL(updateGame()), displayWidget, SLOT(update())); // defini les signaux et slots a utiliser.
    connect(displayWidget, SIGNAL(killThread()), this, SLOT(selfKillThread()));
    connect(this, SIGNAL(closeApp()), displayWidget, SLOT(closeApp()));
}


