#include "./camera.h"



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




void Camera::resetSmart(float longitudeAim, float latitudeAim, float zoomAim, SwitchEtat toEtat)
{
    if (resetCamS) {
      	nbfoisResetCamSmart = TEMP_RESETCAM_SMART_PAUSE;
	stepLong = -(longitude-longitudeAim) / nbfoisResetCamSmart;
	stepLat = -(latitude-latitudeAim) / nbfoisResetCamSmart;
	stepZoom = -(zoom - zoomAim) / nbfoisResetCamSmart;
	stepCentreX = -centerX / nbfoisResetCamSmart;
	stepCentreZ = -centerZ / nbfoisResetCamSmart;
	resetCamS = false;
    }

    if (longitude != longitudeAim) {
        longitude += stepLong;
    }
    if (latitude != latitudeAim) {
        latitude += stepLat;
    }
    if (zoom != zoomAim) {
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
        longitude=longitudeAim;
        latitude=latitudeAim;
        zoom=zoomAim;
        centerX = 0;
        centerZ = 0;
    }
    if ((toEtat == TOMENU) && (camOKMenu())) {
      	resetCamS = true; // pour une qutre fois
    }
    if ((toEtat == TOGAME) && (camOKGame())) {
      	resetCamS = true; // pour une qutre fois
    }

}