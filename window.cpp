#include "window.h"
#include <QApplication>
#include <QtGui>
#include <QtOpenGL>
#include <QThread>
#include <math.h>
#include <typeinfo>
//#include "object.h"


#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------
//Window
//-------------------------------------------------------------------------------

Window::Window() : kb(), app() // windows herite du clavier, il gerera ses evenement.
{
    qDebug()<< "avant, gl";
    glWidget= new GLWidget(this); //creation de la vue opengl, le principel // on donne aussi une app pour facilite l'affichage
    //(seule pour l'instant) widget de la fenetre.
    qDebug()<< "initializeGL Fin 23243";
    glWidget->setApplication(&app);

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
    {
        emit killThread(); // on ordonne au thread de s'arreter
    }
    if (kb.toucheActivee(T_CTRL))
    {
        if (kb.toucheActivee(T_GAUCHE)) //zoom -
            app.getJoueur()->Acteur::Scale(-0.02);
        if (kb.toucheActivee(T_DROITE)) // zoom +
            app.getJoueur()->Acteur::Scale(0.02);
        if (kb.toucheActivee(T_HAUT)) // +z
            app.getJoueur()->Acteur::Deplacement(0.0,0.0,0.1);
        if (kb.toucheActivee(T_BAS)) // -z
            app.getJoueur()->Acteur::Deplacement(0.0,0.0,-0.1);
    }
    else if (kb.toucheActivee(T_SHIFT))
    {
        if (kb.toucheActivee(T_GAUCHE)) //rot - z
            app.getJoueur()->Acteur::Rotation(0.0,0.0,-1);
        if (kb.toucheActivee(T_DROITE)) // rot - z
            app.getJoueur()->Acteur::Rotation(0.1,0.0,1);
        if (kb.toucheActivee(T_HAUT)) // rot +x
            app.getJoueur()->Acteur::Rotation(-1,0.0,0.0);
        if (kb.toucheActivee(T_BAS)) // rot -x
            app.getJoueur()->Acteur::Rotation(1,0.0,0.0);
    }
    else
    {
        if (kb.toucheActivee(T_GAUCHE)) // -x
            app.getJoueur()->Acteur::Deplacement(-0.1,0.0,0.0);
        if (kb.toucheActivee(T_DROITE)) // +x
            app.getJoueur()->Acteur::Deplacement(0.1,0.0,0.0);
        if (kb.toucheActivee(T_HAUT)) // +y
            app.getJoueur()->Acteur::Deplacement(0.0,0.1,0.0);
        if (kb.toucheActivee(T_BAS)) // -y
            app.getJoueur()->Acteur::Deplacement(0.0,-0.1,0.0);
    }
}

void Window::BougerEnnemie() ///////////////// !!!!!!!!!!!!!! ne pas toucher, fait planter l'affichage si transformation sur acteur !!!!!!!!!!!!!!
{
    //qDebug()<< "0";
    vector<Acteur*>::iterator it;
    for (it=app.getActeurs().begin(); it!=app.getActeurs().end(); it++)
    {
        //     qDebug()<< "type joueur :"<< typeid(app.getJoueur()).name();
        //   qDebug()<< "type it :"<< typeid((*it)).name();
        //   (*it)->Scale(0.01);
    }
    //qDebug()<< "0";
    // app->getActeur()->Acteur::Rotation(1.0,0.0,0.0);
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


    running=true;
    while (running) //tant de l'application n'a pas demander a s'arreter
    {
        msleep(20); // frequence : 60hz
        emit updateQt(); // on envois un signal au a la fonction Update()
    }
    emit closeApp(); // on envois un signal a l'appli pour quel s'arrete enfin
}

void ThApplication::suicideThread()
{
    running=false; // on arrete la boucle du thread
}

void ThApplication::setDisplayWidget(Window* displayWidget) // on defini le thread
{
    win = displayWidget;
    connect(this, SIGNAL(updateQt()), displayWidget, SLOT(Update())); // defini les signaux et slots a utiliser.
    connect(displayWidget, SIGNAL(killThread()), this, SLOT(suicideThread()));
    connect(this, SIGNAL(closeApp()), displayWidget, SLOT(closeApp()));
    //    displayWidget->makeCurrent(); ????????????
}


//-------------------------------------------------------------------------------
//GLWidget
//-------------------------------------------------------------------------------

GLWidget::GLWidget( QWidget *parent) : QGLWidget(parent)
{
    qDebug()<< "GLWidget";
}

GLWidget::~GLWidget()
{
// qDebug()<< "0";
// delete acteur;
// qDebug() << "1";
    makeCurrent(); //Context openGl
// qDebug()<< "2";
}

void GLWidget::setApplication(Application* app)
{
    pApp = app;
}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(TAILLE_MIN_X,TAILLE_MIN_Y); // taille minimal de la fenetre
}

QSize GLWidget::sizeHint() const
{
    return QSize(TAILLE_DEFAULT_X,TAILLE_DEFAULT_Y); // taille de base
}


void GLWidget::initializeGL()
{
    glClearColor ( 1,1,1,0 );
    glEnable (GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
//------------------
// besoin, je ne sais pas pourquoi, de chager chaque modele dans cette fonction.
//------------------
    vector<ModelActeur>* models = pApp->getModelActeurs(); // on recupere le vecteur de modele d'acteur (maillage)
//  models getModelActeurs();
    vector<ModelActeur>::iterator it;
    for (it=models->begin(); it!= models->end(); it++)
    {
        if (QCoreApplication::arguments().count() > 1) // ????????????????????????????????
            (it)->getMesh()->load(QCoreApplication::arguments().at(1).toStdString()); // ????????????????????????
        else
            (it)->getMesh()->load("meshes/" + it->getType() ); // on charge en memoir le demon (objet 3D a afficher dans la vue)
    }
}

void GLWidget::paintGL() // mise a jour de la vue
{
    qDebug()<< "updateGL";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // c'est ce qui fait plante l'affichage quand on bouge un acteur (pas joueur)
    // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    qDebug()<< "updateGL";
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    gluLookAt(0,0,5,0,0,0,0,1,0);
    // gluLookAt(3,4,2,0,0,0,0,0,1);
    pApp->Afficher(); // on affiche tout les elements
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
