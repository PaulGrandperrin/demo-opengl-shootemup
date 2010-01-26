#ifndef PARAMETRE_H_
#define PARAMETRE_H_

// TODO faire le menage !
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Parameters {

public :
    Parameters() {
        ifstream fichier("parameters.txt", ios::in); //ouverture du fichier
        string j,k,l,m,n,o,p,j1,k1,l1,m1,n1,o1,p1,j2,k2,l2,m2,n2,o2,p2,j3,k3,l3,m3,n3,o3,p3,j4,k4;
        int    a,b,c,d,e,f,g,a1,b1,c1,d1,e1,f1,g1,a2,b2,c2,d2,e2,f2,g2,a3,b3,c3,d3,e3,f3,g3,a4,b4;
        if (fichier) {

            fichier >> j >> a >> k >> b >> l >>c >> m >> d >> n >> e >> o >> f >> p >> g >> 
		       j1 >> a1 >> k1 >> b1 >> l1 >>c1 >> m1 >> d1 >> n1 >> e1 >> o1 >> f1 >> p1 >> g1 >> 
		       j2 >> a2 >> k2 >> b2 >> l2 >> c2 >> m2 >> d2 >> n2 >> e2 >> o2 >> f2 >> p2 >> g2 >> 
		       j3 >> a3 >> k3 >> b3 >> l3 >> c3 >> m3 >> d3 >> n3 >> e3 >> o3 >> f3 >> p3 >> g3 >> 
		       j4 >> a4 >> k4 >> b4; // lit les variables et les noms des variables de parameters.txt
		       
            cout << j <<a << endl<< k<< b << endl <<l << c << endl<< m << d<<endl <<n << e << endl <<o << f << endl <<p << g << endl << 
		    j1 << a1 << endl << k1 << b1 << endl << l1 << c1 << endl << m1 << d1 << endl << n1 << e1 << endl << o1 << f1 << endl << 
		    p1 << g1 << endl << j2 << a2 << endl << k2 << b2 << endl << l2 << c2 << endl << m2 << d2 << endl << n2 << e2 << endl << 
		    o2 << f2 << endl << p2 << g2 << endl << j3 << a3 << endl << k3 << b3 << endl << l3 << c3 << endl << m3 << d3 << endl << 
		    n3 << e3 << endl << o3 << f3 << endl<< p3 << g3 << endl << j4 << a4 << endl << k4 << b4 << endl;
	    
	    //fichier >> j1 >> a1 >> k1 >> b1 >> l1 >>c1 >> m1 >> d1 >> n1 >> e1 >> o1 >> f1 >> p1 >> g1; // lit les variables et les noms des variables de parameters.txt
            //cout << j1 << a1 << endl << k1 << b1 << endl << l1 << c1 << endl << m1 << d1 << endl << n1 << e1 << endl << o1 << f1 << endl << p1 << g1 << endl;
	    
	    //fichier >> j2 >> a2 >> k2 >> b2 >> l2 >> c2 >> m2 >> d2 >> n2 >> e2 >> o2 >> f2 >> p2 >> g2; // lit les variables et les noms des variables de parameters.txt
            //cout << j2 << a2 << endl << k2 << b2 << endl << l2 << c2 << endl << m2 << d2 << endl << n2 << e2 << endl << o2 << f2 << endl << p2 << g2 << endl;
	    
	    //fichier >> j3 >> a3 >> k3 >> b3 >> l3 >> c3 >> m3 >> d3 >> n3 >> e3 >> o3 >> f3 >> p3 >> g3 >> j4 >> a4 >> k4 >> b4; // lit les variables et les noms des variables de parameters.txt
            //cout << j3 << a3 << endl<< k3 << b3 << endl << l3 << c3 << endl << m3 << d3 << endl << n3 << e3 << endl << o3 << f3 << endl<< p3 << g3 << endl << j4 << a4 << endl << k4 << j4 << endl;
	    fichier.close();
        }
        else {
            cout << "Unable to open \"" << fichier << "\"" << endl;
        }
        this->TAILLE_DEFAULT_X = a;
        this->TAILLE_DEFAULT_Y = b;
        this->TAILLE_MIN_X = c;
        this->TAILLE_MIN_Y = d;
	this->HEALTH_PLAYER = e;
	this->DAMAGE_PLAYER = f;
	this->ACTOR_DAMAGE = g;
	this->NB_KEYS = a1;
	this->K_QUIT = b1;
	this->K_CTRL = c1;
	this->K_SHIFT = d1;
	this->K_ALT = e1;
	this->K_UP = f1;
	this->K_DOWN = g1;
	this->K_LEFT = a2;
	this->K_RIGHT = b2;
	this->K_TIR = c2;
	this->K_TIR_SECOND = d2;
	this->K_PAUSE = e2;
	this->K_FULLSCREEN = f2;
	this->K_FULLSCREEN_SECOND = g2;
	this->K_QUIT_SECOND = a3;
	this->K_ESC = b3;
	this->K_MENU = c3;
	this->K_ENTER = d3;
	this->K_SCREENSHOT = e3;
	this->NB_BUTTON = f3;
	this->B_LEFT = g3;
	this->B_MIDDLE = a4;
	this->B_RIGHT = b4;
	
    }
    ~Parameters() {
    }
    inline int getTailleDefaultX() {
        return TAILLE_DEFAULT_X;
    }
    inline int getTailleDefaultY() {
        return TAILLE_DEFAULT_Y;
    }
    inline int getTailleMinX() {
        return TAILLE_MIN_X;
    }
    inline int getTailleMinY() {
        return TAILLE_MIN_Y;
    }
    inline int getHealthPlayer() {
        return HEALTH_PLAYER;
    }
    inline int getDamagePlayer() {
        return DAMAGE_PLAYER;
    }
    inline int getActorDamage() {
        return ACTOR_DAMAGE;
    }
    inline int getNbKeys() {
        return NB_KEYS;
    }
    inline int getQuit() {
        return K_QUIT;
    }
    inline int getCtrl() {
        return K_CTRL;
    }
    inline int getShift() {
        return K_SHIFT;
    }
    inline int getAlt() {
        return K_ALT;
    }
    inline int getUp() {
        return K_UP;
    }
    inline int getDown() {
        return K_DOWN;
    }
    inline int getRight() {
        return K_RIGHT;
    }
    inline int getLeft() {
        return K_LEFT;
    }
    inline int getTir() {
        return K_TIR;
    }
    inline int getTirSecond() {
        return K_TIR_SECOND;
    }
    inline int getPause() {
        return K_PAUSE;
    }
    inline int getFullscreen() {
        return K_FULLSCREEN;
    }
    inline int getFullscreenSecond() {
        return K_FULLSCREEN_SECOND;
    }
    inline int getQuitSecond() {
        return K_QUIT_SECOND;
    }
    inline int getEsc() {
        return K_ESC;
    }
    inline int getMenu() {
        return K_MENU;
    }
    inline int getEnter() {
        return K_ENTER;
    }
    inline int getScreenshot() {
        return K_SCREENSHOT;
    }
    inline int getNbButton() {
        return NB_BUTTON;
    }
    inline int getBLeft() {
        return B_LEFT;
    }
    inline int getBMiddle() {
        return B_MIDDLE;
    }
    inline int getBRight() {
        return B_RIGHT;
    }
    

private :
    int TAILLE_DEFAULT_X;
    int TAILLE_DEFAULT_Y;
    int TAILLE_MIN_X;
    int TAILLE_MIN_Y;
    
    int HEALTH_PLAYER;
    int DAMAGE_PLAYER;
    int ACTOR_DAMAGE;
    
    int NB_KEYS;
    int K_QUIT;
    int K_CTRL;
    int K_SHIFT;
    int K_ALT;
    int K_UP;
    int K_DOWN;
    int K_LEFT;
    int K_RIGHT;
    int K_TIR;
    int K_TIR_SECOND;
    int K_PAUSE;
    int K_FULLSCREEN;
    int K_FULLSCREEN_SECOND;
    int K_QUIT_SECOND;
    int K_ESC;
    int K_MENU;
    int K_ENTER;
    int K_SCREENSHOT;

    int NB_BUTTON;// mouse
    int B_LEFT;
    int B_MIDDLE;
    int B_RIGHT;
};

#define POSTFX_NOTHING 0
#define POSTFX_BLUR 1
#define POSTFX_WATER 2
#define POSTFX_FAKEHDR 4
#define POSTFX_BLACKWHITE 8
#define POSTFX_CELLSHADING 16

#define NB_Button 9
#define NB_Keys 18


#define NB_NUAGE_TYPE 3 // le nombre de nuage sur la scene
#define NB_SOL 30

#define TYPE_DEFAULT_MESH 1
#define TAILLE_DEFAULT_VAISSEAU 0.1
#define POSX_DEFAULT_VAISSEAU 0
#define POSY_DEFAULT_VAISSEAU 0
#define POSZ_DEFAULT_VAISSEAU 0
#define ANGLEX_DEFAULT_VAISSEAU 0
#define ANGLEY_DEFAULT_VAISSEAU 0
#define ANGLEZ_DEFAULT_VAISSEAU 0
#define VELOCITYX_DEFAULT_VAISSEAU 0
#define VELOCITYY_DEFAULT_VAISSEAU 0
#define VELOCITYZ_DEFAULT_VAISSEAU 0
#define ACCELERATIONX_DEFAULT_VAISSEAU 0
#define ACCELERATIONY_DEFAULT_VAISSEAU 0
#define ACCELERATIONZ_DEFAULT_VAISSEAU 0
#define TRAJECTORY_DEFAULT_FILE_NAME ""
#define STRUCT_POSITION_DEF {0,0,0}
#define STRUCT_ROTATION_DEF {0,0,0}
#define STRUCT_VELOCITY_DEF {0,0,0}
#define STRUCT_ACCEL_DEF {0,0,0}

#define INTERVALE_TEMP_SHOOT 20 // temp = X*20ms ex: 50*20 = 1s
#define INTERVALE_TEMP_SHOOT_GROS 100 // temp = X*20ms ex: 50*20 = 1s
#define INTERVALE_TEMP_ENEMY 50  // provisoire
#define INTERVALE_TEMP_TRAJECTORY_SEQUENCE 200
#define TIMER_OFF -1


//camera settings (surtout pour le mode pause)
#define NB_UNITY_WIDTH 12
#define NB_UNITY_HEIGHT 12

#define TEMP_RESETCAM_SMART_PAUSE 50
#define TEMP_BROUILLAGE_CAM_PLAYER_HEARTH 50

#define ZOOM_MENU 20 // temps mis pour reset l'angle apres la pause
#define LATITUDE_MENU 1.0 // temps mis pour reset l'angle apres la pause
#define LONGITUDE_MENU 0.5 // temps mis pour reset l'angle apres la pause
#define ZOOM_GAME 30 // temps mis pour reset l'angle apres la pause
#define LATITUDE_GAME 1.5 // temps mis pour reset l'angle apres la pause
#define LONGITUDE_GAME 0.0 // temps mis pour reset l'angle apres la pause
#define CENTERX_MIN -100 // le plus proche
#define CENTERX_MAX 100 // le plus loins
#define CENTERZ_MIN -100 // le plus proche
#define CENTERZ_MAX 100 // le plus loins
#define ZOOM_MIN 3 // le plus proche
#define ZOOM_MAX 60 // le plus loins

#define QT_K_QUIT Key_Q
#define QT_K_CTRL Key_Control
#define QT_K_SHIFT Key_Shift
#define QT_K_ALT Key_Alt
#define QT_K_UP Key_Up
#define QT_K_DOWN Key_Down
#define QT_K_LEFT Key_Left
#define QT_K_RIGHT Key_Right
#define QT_K_TIR Key_W
#define QT_K_TIR_SECOND Key_X
#define QT_K_PAUSE Key_P
#define QT_K_FULLSCREEN Key_F11
#define QT_K_FULLSCREEN_SECOND Key_F
#define QT_K_QUIT_SECOND Key_C 
#define QT_K_ESC Key_Escape
#define QT_K_MENU Key_M
#define QT_K_ENTER Key_Return
#define QT_K_SCREENSHOT Key_F10


#endif
