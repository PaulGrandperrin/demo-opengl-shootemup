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
    void menuManager(bool stateKeys[], bool stateButtons[], Point deltaMouse, int deltaWheel,float time, int width, int height);

    void getRender(vector<instance>* instances);

private:


    Text textMenu; // "aaaaaaa"
    Text shump; // "aaaaaaa"<
    Text truc; // "aaaaaaa"<

    int itemSelected;
    Text textPlay; // "aaaaaaa"
    Text textQuit; // "aaaaaaa"
    // Peut etre pas besoin -> j'ai mis la declaration des vecteur dans init, ce qui permet de supprimer les warnings.
    // vect truc;
    // truc = {0,0,0} n'est pas permi avec l'ancienne norme !
    vect pPlay,rPlay,sPlay;//vecteur de play
    vect pQuit,rQuit,sQuit;//vecteur de quitter
    
};

#endif
