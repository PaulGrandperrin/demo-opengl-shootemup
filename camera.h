#ifndef CAMERA_H_
#define CAMERA_H_


#include "parameters.h"


class Camera
{
public:
  
    inline void init() {
        longitude=0;
        latitude=1.5; //3.14158/2
        zoom=ZOOM_DEFAULT;
        centerX = 0;
        centerY = 0;
	resetCamS = true;
	nbfoisResetCamSmart = 0;
    }
    inline bool camOK() {
      return ((longitude==0) && (latitude==(1.5)) && (zoom==ZOOM_DEFAULT) && (centerX == 0) && (centerY == 0));
      //return true;
    }
    
    void setZoom(float f);
    void setLongitude(float f);
    void setLatitude(float f);
    void setCenterX(float f);
    void setCenterY(float f);
    
    float getLongitude() { return longitude; }
    float getLatitude() { return latitude; }
    float getZoom() { return zoom; }
    float getCenterX() { return centerX; }
    float getCenterY() { return centerY; }
    
    void resetSmart();

private:
    
    float longitude, latitude, zoom, centerX, centerY; // parametre de la camera    
    float stepLong, stepLat, stepZoom, stepCentreX, stepCentreY; // pour resetCamSmart, le changement a chaque etape

    bool resetCamS; // si on a à reinitialise la camera (Smart), il ne faut evaluer les step..s qu'une seule fois (constant)
    int nbfoisResetCamSmart; // le nombre de fois a faire resetCamSmart pour arriver proche de 0

};

#endif
