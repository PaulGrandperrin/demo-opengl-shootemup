#ifndef MODEABOUT_H_
#define MODEABOUT_H_

#include <list>
#include <math.h>

#include "./mode.h"
#include "./objects/text.h"

class ModeAbout : public Mode
{
public:
    ~ModeAbout() {};
    ModeAbout() {}
    ModeAbout(Models* models, Camera* camera,Etat* etatGame, SwitchEtat* switchMode);
    void aboutManager(bool stateKeys[], bool stateButtons[], Point coordMouse, int deltaWheel,float time, int width, int height);
    
    void getRender(vector<instance>* instances,vector<instance>* instances2D);

private:
    //Point oldMouse;
    Text madeBy,robin,jeanlu,sebastien,remi,paul,romain;
    //bool keyDown, keyUp, bMouse;//pourrais bien servir si on veut faire défiler le texte..
    vector<Text> vectorText;


};

#endif
