

#include "keyboard.h"


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
}