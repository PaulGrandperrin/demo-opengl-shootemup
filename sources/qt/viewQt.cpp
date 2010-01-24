#include "./viewQt.h"

extern Parameters *parametre;
//-------------------------------------------------------------------------------
//GLWidget
//-------------------------------------------------------------------------------

ViewOpenGl::ViewOpenGl( QWidget *parent) : QGLWidget(parent)
{
    setMinimumSize(QSize(parametre->getTailleMinX(),parametre->getTailleMinY())); // le minimunSizeHint n'a pas d'effets, a voir.
    passageScreen = false;
    setWindowTitle(tr("Shmup"));
    grabKeyboard();
    grabMouse();
    setMouseTracking(true);
    connect(&thread, SIGNAL(updateGame()), this, SLOT(update()));

    thread.start();
}

ViewOpenGl::~ViewOpenGl()
{
    makeCurrent(); //Context openGl
    thread.stop(); //On demande au thread de se suicider (=! on tue le thread)
    thread.wait(); //et donc on attend qu'il soit bien mort (et enterré)
    delete parametre; // on suprime les parametre (var global)
}

void ViewOpenGl::initializeGL()
{
    game = new Game();
}

void ViewOpenGl::paintGL()
{
    float t=time.elapsed(); // TODO Delta time
    time.restart();
    game->update(kb.getStateKeys(),mouse.getStateButtons(),mouse.getCoordMouse(), mouse.getDeltaWheel(),t,width,height);
    mouse.updateWheel(0); //naicessaire, sinon le delta (molette) n'est pas calculer

    if (game->close()) //FIXME il ya surement une place plus adaptée pour ça
        close();

    if (passageScreen && !(kb.getStateKeys()[K_FULLSCREEN] || (kb.getStateKeys()[K_ALT] && kb.getStateKeys()[K_FULLSCREEN_SECOND]))) {
        if (!isFullScreen())
            setWindowState(Qt::WindowFullScreen);
        else
            setWindowState(Qt::WindowMaximized);
        passageScreen = false;
    }
    else if (!passageScreen && (kb.getStateKeys()[K_FULLSCREEN] || (kb.getStateKeys()[K_ALT] && kb.getStateKeys()[K_FULLSCREEN_SECOND]))) {
        passageScreen = true;
    }
}

void ViewOpenGl::resizeGL(int width, int height)
{
    game->resize(width,height);
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

void ViewOpenGl::mousePressEvent(QMouseEvent * event) // action on keyboard
{
    mouse.updateEvent(event->button(),true); // update tab state of key
}

void ViewOpenGl::mouseReleaseEvent(QMouseEvent * event)
{
    mouse.updateEvent(event->button(),false); // update tab state of key
}

void ViewOpenGl::mouseMoveEvent(QMouseEvent * event)
{
    mouse.updateXY(event->pos());
}

void ViewOpenGl::wheelEvent(QWheelEvent * event)
{
    mouse.updateWheel(event->delta());
}

QSize ViewOpenGl::minimumSizeHint() const
{
    return QSize(parametre->getTailleMinX(),parametre->getTailleMinY()); // minimal size of window
}

QSize ViewOpenGl::sizeHint() const
{
    return QSize(parametre->getTailleDefaultX(),parametre->getTailleDefaultY()); // size of window
}
