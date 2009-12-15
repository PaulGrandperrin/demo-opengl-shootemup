#include "window.h"
#include <QApplication>
#include <QtGui>
#include <QtOpenGL>

#include <math.h>


Window::Window()
{
  glWidget= new GLWidget(this);
//   QHBoxLayout *mainLayout = new QHBoxLayout;
//   mainLayout->addWidget(glWidget);
//   setLayout(mainLayout);
  
  setWindowTitle(tr("Shmup"));
  qDebug() << "Ouverture de la fenetre";
  grabKeyboard();
}

Window::~Window()
{
}

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
  angle=0;  
  
}

GLWidget* Window::getGlWidget()
{
  return this->glWidget;
}


Thread::Thread()
{
//   if(QCoreApplication::arguments().count() > 1)
//     test.load(QCoreApplication::arguments().at(1).toStdString());
//   else
//     test.load("meshes/cube.obj");


}

void Thread::run()
{
     while(true)
     {
       //Appel au moteur de jeu
       // CUBE
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-5,0,0,0,0,1,0);
// 	glTranslatef(posx,posy,0);
	glRotatef(angle,0.5,0.5,0);
// 	glScalef(s,s,s);
// 	test.render(); 
	updateQt();
     }
}


void Thread::setDisplayWidget(GLWidget* displayWidget)
{
    connect(this, SIGNAL(updateQt()), displayWidget, SLOT(updateGL()));
    displayWidget->makeCurrent();
}



GLWidget::~GLWidget()
{
  makeCurrent();
}

QSize GLWidget::minimumSizeHint() const
{
  return QSize(50,50);
}

QSize GLWidget::sizeHint() const
{
  return QSize(400,400);
}

void GLWidget::initializeGL()
{
  glClearColor ( 1,1,1,0 );
  glEnable (GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  
}

void GLWidget::paintGL()
{
}

void GLWidget::resizeGL(int width, int height)
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


void Window::keyPressEvent(QKeyEvent * event)
{
   kb.kbEvent(event->key(),true);
}

void Window::keyReleaseEvent(QKeyEvent * event)
{
   kb.kbEvent(event->key(),false);
}