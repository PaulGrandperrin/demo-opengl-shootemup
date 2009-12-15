#include "Model3D.h"
#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include "keyboard.h"
#include <QThread>

class GLWidget : public QGLWidget
{
  Q_OBJECT
  
  public:
    GLWidget(QWidget *parent = 0);
     ~GLWidget();

     QSize minimumSizeHint() const;
     QSize sizeHint() const;
     
  protected:
     void initializeGL();
     void paintGL();
     void resizeGL(int width, int height);

  private:
    
    //rien a foutre ici
    float angle;
     float posx,posy,accx,accy,s;
     int width,height;
     
};


class Thread : public QThread
{
  Q_OBJECT
public:
    Thread();
    void run();
    void setDisplayWidget(GLWidget* displayWidget);

    signals:
        void updateQt(/* you can put the resulting data */);
	
  private:
        float angle;
	Model3D test;  
};

class Window: public QWidget
{
  public:
    Window();
    ~Window();
    GLWidget* getGlWidget();
  private:
    Keyboard kb;
    GLWidget* glWidget;
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    
};


//-------------







