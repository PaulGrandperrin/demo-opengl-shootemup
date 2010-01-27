#ifndef CAMERA_H_
#define CAMERA_H_

#include "../../parameters.h"
#include "../../utilities.h"

class Camera
{
public:

    Camera() {
        longitude=LONGITUDE_MENU;
        latitude=LATITUDE_MENU; //3.14158/2
        zoom=ZOOM_MENU;
        centerX = POSITION_CAM_MENU_X;
        centerZ = POSITION_CAM_MENU_Z;
        resetCamS = true;
        nbfoisResetCamSmart = 0;
    }
    inline bool camOKMenu() {
        return ((longitude==LONGITUDE_MENU) && (latitude==LATITUDE_MENU) && (zoom==ZOOM_MENU) && (centerX == POSITION_CAM_MENU_X) && (centerZ == POSITION_CAM_MENU_Z));
    }
    inline bool camOKGame() {
        return ((longitude==LONGITUDE_GAME) && (latitude==LATITUDE_GAME) && (zoom==ZOOM_GAME) && (centerX == POSITION_CAM_GAME_X) && (centerZ == POSITION_CAM_GAME_Z));
    }
    inline bool camOKPause() {
        return ((longitude==LONGITUDE_PAUSE) && (latitude==LATITUDE_PAUSE) && (zoom==ZOOM_PAUSE) && (centerX == POSITION_CAM_PAUSE_X) && (centerZ == POSITION_CAM_PAUSE_Z));
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
        resetSmart(LONGITUDE_MENU,LATITUDE_MENU,ZOOM_MENU,POSITION_CAM_MENU_X,POSITION_CAM_MENU_Z,TOMENU);
    }

    inline void toModeGameSmart() {
        resetSmart(LONGITUDE_GAME,LATITUDE_GAME,ZOOM_GAME,POSITION_CAM_GAME_X,POSITION_CAM_GAME_Z,TOGAME);
    }
    
    inline void toModePauseSmart() {
        resetSmart(LONGITUDE_PAUSE,LATITUDE_PAUSE,ZOOM_PAUSE,POSITION_CAM_PAUSE_X,POSITION_CAM_PAUSE_Z,TOPAUSE);
    }

private:

    void resetSmart(float longitudeAim, float latitudeAim, float zoomAim, float posXAim, float posZAim, SwitchEtat toEtat);
    float longitude, latitude, zoom, centerX, centerZ; // parametre de la camera
    float stepLong, stepLat, stepZoom, stepCentreX, stepCentreZ; // pour resetCamSmart, le changement a chaque etape

    bool resetCamS; // si on a à reinitialise la camera (Smart), il ne faut evaluer les step..s qu'une seule fois (constant)
    int nbfoisResetCamSmart; // le nombre de fois a faire resetCamSmart pour arriver proche de 0

};

#endif
