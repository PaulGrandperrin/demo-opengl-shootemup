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
#define VELOCITY_BOULET 2
#define TAILLE_BOULET 0.03
#define INTERVALE_TEMP_ENEMY 50  // provisoire

#define ZOOM_DEFAULT 8 // temps mis pour reset l'angle apres la pause
#define ZOOM_MIN 3 // le plus proche
#define ZOOM_MAX 30 // le plus loins
 

#define NB_KEYS 9
#define K_ESC 0
#define K_UP 1
#define K_DOWN 2
#define K_LEFT 3
#define K_RIGHT 4
#define K_CTRL 5
#define K_SHIFT 6
#define K_ALT 7
#define K_SPACE 8


#define NB_BUTTON 9 // mouse
#define B_LEFT 0
#define B_MIDLE 1
#define B_RIGHT 2

#endif