#ifndef WINDOW_H_
#define WINDOW_H_

#include "acteur.h"
#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include "keyboard.h"
#include <QThread>


// #include <iostream>
// using namespace std;

class GLWidget : public QGLWidget // It's the widget which will contain openGl view
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    //void VerificationTouche();
    void updateGLView() {
      //  angle +=2;    // called with the Update function in Window (Thread)
        updateGL(); //reafficher la vue opengl
    }
    Acteur* getActeur() { return acteur; }
  //  void setPosx(float x) { posx += x; }
//    void setPosy(float y) { posy += y; }

protected:
    void initializeGL(); // automatiquement appelée
    void paintGL(); // appeller pas updateGL
    void resizeGL(int width, int height);      // public at this momment, but would be change to protected. (for resizeEvent of Window)

private:
    int width,height; //size of OpenGl view
    Acteur* acteur;  // 3D objet here, but will be replace by more complet Objects
  //  float angle; // just fort test, but will go to the objet (Ennemis...)
  //  float posx,posy; // public, more easy, but test
};

class Window: public QWidget
{
    Q_OBJECT
//   private :
public:
    Window();
    ~Window();
//     GLWidget* getGlWidget();  // pas utile

private:
    Keyboard kb; // le gestion du clavier (reception d'evenement)
    GLWidget* glWidget; // la vue opengl
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void VerificationTouche();
    void BougerEnnemie();


private slots: // fonction appeller par le thread tout les 20ms.
    void Update() {
	BougerEnnemie();
        VerificationTouche(); // on recptionnent les actions de l'utilisateur
        glWidget->updateGLView(); // on met a jour la vue.
    }
};




class ThApplication : public QThread
{
    Q_OBJECT
public:
    ThApplication();
    void run(); // coeur du thread
    void setDisplayWidget(Window* displayWidget);
  //  void 
  //void quit() { exit(0); }

  private:
    Window* win;

signals:
    void updateQt(/* you can put the resulting data */);
};

#endif