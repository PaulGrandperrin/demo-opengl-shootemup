#ifndef CAMERA_H_
#define CAMERA_H_

#include "parameters.h"
#include "function.h"

class Camera
{
public:

    inline void init() {
        longitude=LONGITUDE_MENU;
        latitude=LATITUDE_MENU; //3.14158/2
        zoom=ZOOM_MENU;
        centerX = 0;
        centerZ = 0;
        resetCamS = true;
        nbfoisResetCamSmart = 0;
    }
    inline bool camOKMenu() {
        return ((longitude==LONGITUDE_MENU) && (latitude==LATITUDE_MENU) && (zoom==ZOOM_MENU) && (centerX == 0) && (centerZ == 0));
        //return true;
    }
    inline bool camOKGame() {
        return ((longitude==LONGITUDE_GAME) && (latitude==LATITUDE_GAME) && (zoom==ZOOM_GAME) && (centerX == 0) && (centerZ == 0));
        //return true;
    }

    void setZoom(float f);
    void setLongitude(float f);
    void setLatitude(float f);
    void setCenterX(float f);
    void setCenterZ(float f);

    float getLongitude() {
        return longitude;
    }
    float getLatitude() {
        return latitude;
    }
    float getZoom() {
        return zoom;
    }
    float getCenterX() {
        return centerX;
    }
    float getCenterZ() {
        return centerZ;
    }

    inline void toModeMenuSmart() {
        resetSmart(LONGITUDE_MENU,LATITUDE_MENU,ZOOM_MENU,TOMENU);
    }

    inline void toModeGameSmart() {
	resetSmart(LONGITUDE_GAME,LATITUDE_GAME,ZOOM_GAME,TOGAME);
    }

private:

    void resetSmart(float longitudeGame, float latitudeGame, float zoomGame, SwitchEtat toEtat);
    float longitude, latitude, zoom, centerX, centerZ; // parametre de la camera
    float stepLong, stepLat, stepZoom, stepCentreX, stepCentreZ; // pour resetCamSmart, le changement a chaque etape

    bool resetCamS; // si on a à reinitialise la camera (Smart), il ne faut evaluer les step..s qu'une seule fois (constant)
    int nbfoisResetCamSmart; // le nombre de fois a faire resetCamSmart pour arriver proche de 0

};

#endif
