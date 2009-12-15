#include "window.h"
#include <QApplication>
#include <QtGui>
#include <QtOpenGL>
#include <QThread>
#include <math.h>

bool Enma = true;
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------
//Window
//-------------------------------------------------------------------------------

Window::Window() : kb() // windows herite du clavier, il gerera ses evenement.
{
    glWidget= new GLWidget(this); //creation de la vue opengl, le principel
    //(seule pour l'instant) widget de la fenetre.

    /* Le trois lignes perment de pouvoir redimmesioner
    la vue opengl lors de celle de la fenetre.
    A approfondir ...*/
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(glWidget);
    setLayout(mainLayout);
    setWindowTitle(tr("Shmup")); // le titre de la fenetre, il est afficher dans la barre des taches

    grabKeyboard(); //permet de reagir au evenement clavier !!!
}

Window::~Window()
{
   delete glWidget; // vide la memoire !
}


void Window::keyPressEvent(QKeyEvent * event) // permet les entre du clavier (deplacement vaisseau ...)
{
    kb.majEvenements(event->key(),true); // si une touche est presser
}

void Window::keyReleaseEvent(QKeyEvent * event) // idem dessus
{
    kb.majEvenements(event->key(),false);
}

void Window::VerificationTouche() // defini les actions a effectuer suivant la(es) touche(s) presente.
{
    if (kb.toucheActivee(T_ECHAP))
       Enma = false;
       // close();
    if(kb.toucheActivee(T_GAUCHE))
        glWidget->setPosx(-0.1);
    if(kb.toucheActivee(T_DROITE))
        glWidget->setPosx(0.1);
    if(kb.toucheActivee(T_HAUT))
        glWidget->setPosy(0.1);
    if(kb.toucheActivee(T_BAS))
        glWidget->setPosy(-0.1);
}


// GLWidget* Window::getGlWidget() // pas utile
// {
//   return this->glWidget;
// }

//-------------------------------------------------------------------------------
//ThApplication : thread de l'application
//-------------------------------------------------------------------------------

ThApplication::ThApplication() 
{
}
//        close();
void ThApplication::run() // le coeur du thread
{
    while (Enma) //win->getEnMarc() == 1
    {
        msleep(20); // frequence : 60hz
        emit updateQt(); // on envois un signal au a la fonction Update()
    }
    win->close();

}


void ThApplication::setDisplayWidget(Window* displayWidget) // on defini le thread
{
    win = displayWidget;
    connect(this, SIGNAL(updateQt()), displayWidget, SLOT(Update())); // defini les signaux et slots a utiliser.
//    displayWidget->makeCurrent(); ????????????
}


//-------------------------------------------------------------------------------
//GLWidget
//-------------------------------------------------------------------------------

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
}

GLWidget::~GLWidget()
{
 makeCurrent(); //??????????????????
}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(50,50); // taille minimal de la fenetre
}

QSize GLWidget::sizeHint() const
{
    return QSize(400,400); // taille de base
}


void GLWidget::initializeGL()
{
    angle = 0; // pour les tests
    posx=0;
    posy=0;
    glClearColor ( 1,1,1,0 );
    glEnable (GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    if (QCoreApplication::arguments().count() > 1) // ????????????????????????????????
        test.load(QCoreApplication::arguments().at(1).toStdString()); // ????????????????????????
    else
        test.load("meshes/demon.obj"); // on charge en memoir le demon (objet 3D a afficher dans la vue)
}

void GLWidget::paintGL() // mise a jour de la vue
{


    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    
    gluLookAt(0,0,5,0,0,0,0,1,0);
   // gluLookAt(3,4,2,0,0,0,0,0,1);
    glTranslatef(posx,posy,0);
    glRotatef(this->angle,0.5,0.5,0); // test : rotation du demon
    test.render(); 

    glFlush(); // force l'affichage opengl
}

void GLWidget::resizeGL(int width, int height) // pour redimenssioner la vue (garder les proportions ...)
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


