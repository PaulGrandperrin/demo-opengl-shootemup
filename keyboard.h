#include <QKeyEvent>

#define NB_KEYS 7
#define K_QUIT 0
#define K_LEFT 1
#define K_UP 2
#define K_RIGHT 3
#define K_DOWN 4
#define K_FIRE1 5
#define K_FIRE2 6


class Keyboard
{
  public:
    Keyboard();
    void kbEvent(int keycode,bool pressed);
    
    void poolKeys(int keys[]);
    
  private:
    
    bool keys[NB_KEYS];
};