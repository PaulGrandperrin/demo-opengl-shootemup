

#include "keyboard.h"


// #include <iostream>
// using namespace std;
/*
Keyboard::Keyboard()
{
  for(int i=0;i<NB_KEYS;i++)
    keys[i]=false;
}

void Keyboard::kbEvent(int keycode,bool pressed)
{
  switch (keycode)
  {
    case Qt::Key_Escape: keys[K_QUIT]=pressed;break;
    case Qt::Key_Left: 	keys[K_LEFT]=pressed;break;
    case Qt::Key_Right: keys[K_RIGHT]=pressed;break;
    case Qt::Key_Down: keys[K_DOWN]=pressed;break;
    case Qt::Key_Up: keys[K_UP]=pressed;break;
    case Qt::Key_Control: keys[K_FIRE1]=pressed;break;
    case Qt::Key_Alt: keys[K_FIRE2]=pressed;break;
  }
}

void Keyboard::poolKeys(int keys[])
{
  for(int i=0;i<NB_KEYS;i++)
    keys[i]=this->keys[i];
}*/


#include <stdlib.h>
//#include "GestionClavier.h"

Keyboard::Keyboard() {
  // On definit les touches par defaut
  int tab_temp_corresp[NB_KEYS] = {Qt::Key_Escape, Qt::Key_Left, Qt::Key_Up, Qt::Key_Right, Qt::Key_Down, Qt::Key_Control, Qt::Key_Shift, Qt::Key_Space};
  // Initialisation des attributs
  for(int i = 0; i<NB_KEYS; i++) {
    etatTouche[i] = 0;
    correspTouche[i] = tab_temp_corresp[i];
  }
}

void Keyboard::majEvenements(int touche, int etat) {
  int i = 0;
  // Grace au code de la touche et au tableau de correspondance, on recupere son etat
  while(i < NB_KEYS && correspTouche[i] != touche) { i++; }
//      	cout << "defini keyboard"<< endl;
  if(i < NB_KEYS)
    etatTouche[i] = etat;
}

int Keyboard::toucheActivee(int touche) {
  if(touche >= 0 && touche < NB_KEYS)
    return etatTouche[touche];
  else
    return 0;
}