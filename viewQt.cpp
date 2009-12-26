#include "viewQt.h"

//-------------------------------------------------------------------------------
//GLWidget
//-------------------------------------------------------------------------------

ViewOpenGl::ViewOpenGl( QWidget *parent) : QGLWidget(parent)
{
    setWindowTitle(tr("Shmup"));
    grabKeyboard();
    connect(&thread, SIGNAL(updateGame()), this, SLOT(update()));

    thread.start();
}

ViewOpenGl::~ViewOpenGl()
{
    makeCurrent(); //Context openGl
    thread.stop(); //On demande au thread de se suicider (=! on tue le thread)
    thread.wait(); //et donc on attend qu'il soit bien mort (et enterré)
}

void ViewOpenGl::initializeGL()
{
    game.init();
}

void ViewOpenGl::paintGL()
{
    float t=time.elapsed();
    time.restart();
    game.update(kb.getStateKeys(),t);

    if (game.close()) //FIXME il ya surement une place plus adaptée pour ça
        close();
}

void ViewOpenGl::resizeGL(int width, int height)
{
    game.resize(width,height);
    this->width=width;
    this->height=height;
}

//-------------------------------------------------------------------------------

void ThreadQt::run()
{

    running=true;
    while (running) //tant de l'application n'a pas demander a s'arreter
    {
        msleep(1000.0/60); // frequence : 60hz
        emit updateGame();
    }
}

void ThreadQt::stop()
{
    running=false;
}

// Les trucs pas interressants:

void ViewOpenGl::keyPressEvent(QKeyEvent * event) // action on keyboard
{
    kb.updateEvent(event->key(),true); // update tab state of key
}

void ViewOpenGl::keyReleaseEvent(QKeyEvent * event)
{
    kb.updateEvent(event->key(),false); // update tab state of key
}

QSize ViewOpenGl::minimumSizeHint() const
{
    return QSize(TAILLE_MIN_X,TAILLE_MIN_Y); // minimal size of window
}

QSize ViewOpenGl::sizeHint() const
{
    return QSize(TAILLE_DEFAULT_X,TAILLE_DEFAULT_Y); // size of window
}
