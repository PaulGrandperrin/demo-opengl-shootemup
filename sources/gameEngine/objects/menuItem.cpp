#include "./menuItem.h"

// for trace during test , to kept
#include <iostream>
using namespace std;

MenuItem::MenuItem(vector<int> MChiffres, vector<int> MLettersM, string text, vect position,vect rotation,vect scale, float esp, TextStyle style,bool selec, Etat stat, SwitchEtat switchstat): 
text(MChiffres,MLettersM,text,position,rotation,scale,esp,style) {
	selected=selec;
	state=stat;
	switchState=switchstat;
}


bool MenuItem::mouseOver(Point mouse, float halfW, float halfH, float curW, float curH) {
	return (mouse.x >= halfW-text.getXY().x*curW) && (mouse.y <= halfH+(text.getPosition().z+text.getXY().y)*curH) &&
       (mouse.x <= halfW+text.getXY().x*curW) && (mouse.y >= halfH+(text.getPosition().z-text.getXY().y)*curH);
}

void MenuItem::getRender(vector<instance>* instances) {
    vector<Actor> tex;
    vector<Actor>::iterator itA;
    tex = text.getText();//le premier getText renvoie l'objet, le deuxième le texte
    for (itA=tex.begin(); itA!=tex.end(); itA++) {
        instances->push_back(itA->getInstance());
    }
}