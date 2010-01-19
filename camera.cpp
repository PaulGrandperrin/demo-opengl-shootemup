#include "camera.h"



void Camera::setZoom(float f) {
    zoom +=f;
    if (zoom<ZOOM_MIN)
	zoom = ZOOM_MIN;
    if (zoom>ZOOM_MAX)
	zoom = ZOOM_MAX;
}

void Camera::setLongitude(float f) {
    longitude +=f;
    if (longitude >3.1415) // permet de continuer en gardant l'angle le plus faible.
        longitude=-3.1415;
    if (longitude <-3.1415)
        longitude=3.1415;
}

void Camera::setLatitude(float f) {
    latitude +=f;
    if (latitude >3.14/*15*//2) // bloque la vue a la vertical
        latitude=3.14/2;
    if (latitude < -3.14/2)
        latitude=-3.14/2;
}

void Camera::setCenterX(float f) {
    centerX +=f;
    if (centerX >CENTERX_MAX)
        centerX=CENTERX_MAX;
    if (centerX < CENTERX_MIN)
        centerX=CENTERX_MIN;
}

void Camera::setCenterZ(float f) {
    centerZ +=f;
    if (centerZ >CENTERZ_MAX)
        centerZ=CENTERZ_MAX;
    if (centerZ < CENTERZ_MIN)
        centerZ=CENTERZ_MIN;
}


void Camera::resetSmart()
{
    if (resetCamS) {
	nbfoisResetCamSmart = TEMP_RESETCAM_SMART_PAUSE;
	stepLong = -(longitude-LONGITUDE_GAME) / TEMP_RESETCAM_SMART_PAUSE;
	stepLat = -(latitude-LATITUDE_GAME) / TEMP_RESETCAM_SMART_PAUSE;
	stepZoom = -(zoom - ZOOM_GAME) / TEMP_RESETCAM_SMART_PAUSE;
	stepCentreX = -centerX / TEMP_RESETCAM_SMART_PAUSE;
	stepCentreZ = -centerZ / TEMP_RESETCAM_SMART_PAUSE;
	resetCamS = false;
    }

    if (longitude != LONGITUDE_GAME) {
        longitude += stepLong;
    }
    if (latitude != LATITUDE_GAME) {
        latitude += stepLat;
    }
    if (zoom != ZOOM_GAME) {
        zoom += stepZoom;
    }
    if (centerX != 0) {
        centerX += stepCentreX;
    }
    if (centerZ != 0) {
        centerZ += stepCentreZ;
    }
    
    nbfoisResetCamSmart--; // on approche du {0,0,ZOOM_DEFAULT,0,0}
    
    if (nbfoisResetCamSmart == 0) { // on est tres proche donc on peut le faire
        longitude=LONGITUDE_GAME;
        latitude=LATITUDE_GAME;
        zoom=ZOOM_GAME;
        centerX = 0;
        centerZ = 0;
    }
    if (camOK()) {
      	resetCamS = true; // pour une qutre fois
    }

}