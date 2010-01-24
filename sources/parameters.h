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
        string j,k,l,m;
        int a,b,c,d;
        if (fichier) {

            fichier >> j >> a >> k >> b >> l>>c >> m >> d; // lit les variables et les noms des variables de parameters.txt
            fichier.close();
            cout << j <<a << endl<< k<< b << endl <<l << c << endl<< m << d<<endl;
        }
        else {
            cout << "Unable to open \"" << fichier << "\"" << endl;
        }
        this->TAILLE_DEFAULT_X = a;
        this->TAILLE_DEFAULT_Y = b;
        this->TAILLE_MIN_X = c;
        this->TAILLE_MIN_Y = d;
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

private :
    int TAILLE_DEFAULT_X;
    int TAILLE_DEFAULT_Y;
    int TAILLE_MIN_X;
    int TAILLE_MIN_Y;
};
#define HEALTH_PLAYER 1000;
#define DAMAGE_PLAYER 0;
#define ACTOR_DAMAGE 100;

#define NB_NUAGE 6 // le nombre de nuage sur la scene
#define NB_SOL 20

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

#define ZOOM_MENU 30 // temps mis pour reset l'angle apres la pause
#define LATITUDE_MENU 1.0 // temps mis pour reset l'angle apres la pause
#define LONGITUDE_MENU 0.0 // temps mis pour reset l'angle apres la pause
#define ZOOM_GAME 30 // temps mis pour reset l'angle apres la pause
#define LATITUDE_GAME 1.5 // temps mis pour reset l'angle apres la pause
#define LONGITUDE_GAME 0.0 // temps mis pour reset l'angle apres la pause
#define CENTERX_MIN -100 // le plus proche
#define CENTERX_MAX 100 // le plus loins
#define CENTERZ_MIN -100 // le plus proche
#define CENTERZ_MAX 100 // le plus loins
#define ZOOM_MIN 3 // le plus proche
#define ZOOM_MAX 100 // le plus loins

#define NB_KEYS 18
#define K_QUIT 0
#define K_CTRL 1
#define K_SHIFT 2
#define K_ALT 3
#define K_UP 4
#define K_DOWN 5
#define K_LEFT 6
#define K_RIGHT 7
#define K_TIR 8
#define K_TIR_SECOND 9
#define K_PAUSE 10
#define K_FULLSCREEN 11
#define K_FULLSCREEN_SECOND 12
#define K_QUIT_SECOND 13
#define K_ESC 14
#define K_MENU 15
#define K_ENTER 16
#define K_SCREENSHOT 17

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
#define QT_K_QUIT_SECOND Key_C // NOTE Bof, robin tu as deja fermer une application graphic avec CTRL-C ?
#define QT_K_ESC Key_Escape
#define QT_K_MENU Key_M
#define QT_K_ENTER Key_Return
#define QT_K_SCREENSHOT Key_F10

#define NB_BUTTON 9 // mouse
#define B_LEFT 0
#define B_MIDLE 1
#define B_RIGHT 2


#endif
