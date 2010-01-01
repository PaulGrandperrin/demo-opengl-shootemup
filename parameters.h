#ifndef PARAMETRE_H_
#define PARAMETRE_H_

// TODO faire le menage !

#define TAILLE_DEFAULT_X 600
#define TAILLE_DEFAULT_Y 600
#define TAILLE_MIN_X 100
#define TAILLE_MIN_Y 150

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


//camera settings (surtout pour le mode pause)
#define ZOOM_DEFAULT 30 // temps mis pour reset l'angle apres la pause
#define NB_UNITY_WIDTH 12
#define NB_UNITY_HEIGHT 12
#define LATITUDE_DEFAULT 1.5 // temps mis pour reset l'angle apres la pause
#define ZOOM_MIN 3 // le plus proche
#define ZOOM_MAX 100 // le plus loins
#define TEMP_RESETCAM_SMART_PAUSE 50
#define CENTERX_MIN -100 // le plus proche
#define CENTERX_MAX 100 // le plus loins
#define CENTERZ_MIN -100 // le plus proche
#define CENTERZ_MAX 100 // le plus loins
 

#define NB_KEYS 11
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

#define QT_K_QUIT Key_Escape
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




#define NB_BUTTON 9 // mouse
#define B_LEFT 0
#define B_MIDLE 1
#define B_RIGHT 2

#endif