#ifndef MENU_H_
#define MENU_H_

#include <list>
#include <math.h>

#include "mode.h"


class ModeMenu : public Mode
{
public:
    ~ModeMenu();
    void init(Models* models,Etat* etatGame);
    void menuManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height);

    void getRender(vector<instance>* instances);

private:

    /*------------- a retirer plus tards --------------
    Text truc; // "aaaaaaa"<
    vect pTruc={-8,2,8}, rTruc={0,0,0}, sTruc={1.2,1.2,0.5};
    truc = Text(models->getMChiffres(),models->getMLettersa(), "ccc", pTruc, rTruc, sTruc, 1, RIGHT); // test du text, pour l'instant "abcde"
      vect r={0,1,0};
      truc.rotate(r);
      vect s={0.2,0.2,0.2};
      truc.scal(s);
      vect t={-1,0,0};
      truc.translate(t);
    */
    int itemSelected;
    Text textPlay; // "aaaaaaa"
    Text textOption;
    Text textQuit; // "aaaaaaa"
    bool keyDown, keyUp;
    // Peut etre pas besoin -> j'ai mis la declaration des vecteur dans init, ce qui permet de supprimer les warnings.
    // vect truc;
    // truc = {0,0,0} n'est pas permi avec l'ancienne norme !
    
};

#endif
