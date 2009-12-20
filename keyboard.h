// #include <QKeyEvent>
// 
// #define NB_KEYS 7
// #define K_QUIT 0
// #define K_LEFT 1
// #define K_UP 2
// #define K_RIGHT 3
// #define K_DOWN 4
// #define K_FIRE1 5
// #define K_FIRE2 6
// 
// 
// class Keyboard
// {
//   public:
//     Keyboard();
//     void kbEvent(int keycode,bool pressed);
//     
//     void poolKeys(int keys[]);
//     
//   private:
//     
//     bool keys[NB_KEYS];
// };


#ifndef GESTION_CLAVIER_H_
#define GESTION_CLAVIER_H_

#include "parametres.h"

#define NB_KEYS 8
#define T_ECHAP 0
#define T_GAUCHE 1
#define T_HAUT 2
#define T_DROITE 3
#define T_BAS 4
//#define T_TIR1 5
//#define T_TIR2 6
#define T_CTRL 5
#define T_SHIFT 6
#define T_SPACE 7

#include <QKeyEvent>

class Keyboard {
  private:
    int correspTouche[NB_KEYS]; // tableau de correspondance entre les touches utilisees et le code des touche utilise par Qt
    int etatTouche[NB_KEYS]; // tableau associant chaque touche a son etat (appuye ou relache)
  public:
    Keyboard();
    void majEvenements(int touche, int etat); // passe l'etat de la touche "touche" a l'etat "etat", ne fait rien si le numero de touche est invalide
    int toucheActivee(int touche); // renvoie 1 si la touche "touche" est activee, 0 sinon
};
#endif