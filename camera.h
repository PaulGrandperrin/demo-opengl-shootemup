#ifndef CAMERA_H_
#define CAMERA_H_

#include "parameters.h"


class Camera
{
public:
  
    inline void init() {
        longitude=LONGITUDE_GAME;
        latitude=LATITUDE_GAME; //3.14158/2
        zoom=ZOOM_GAME;
        centerX = 0;
        centerZ = 0;
	resetCamS = true;
	nbfoisResetCamSmart = 0;
    }
    inline bool camOK() {
      return ((longitude==LONGITUDE_GAME) && (latitude==LATITUDE_GAME) && (zoom==ZOOM_GAME) && (centerX == 0) && (centerZ == 0));
      //return true;
    }
    
    void setZoom(float f);
    void setLongitude(float f);
    void setLatitude(float f);
    void setCenterX(float f);
    void setCenterZ(float f);
    
    float getLongitude() { return longitude; }
    float getLatitude() { return latitude; }
    float getZoom() { return zoom; }
    float getCenterX() { return centerX; }
    float getCenterZ() { return centerZ; }
    
    void resetSmart();

private:
    
    float longitude, latitude, zoom, centerX, centerZ; // parametre de la camera    
    float stepLong, stepLat, stepZoom, stepCentreX, stepCentreZ; // pour resetCamSmart, le changement a chaque etape

    bool resetCamS; // si on a à reinitialise la camera (Smart), il ne faut evaluer les step..s qu'une seule fois (constant)
    int nbfoisResetCamSmart; // le nombre de fois a faire resetCamSmart pour arriver proche de 0

};

#endif
