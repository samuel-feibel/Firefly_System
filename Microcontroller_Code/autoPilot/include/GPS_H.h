#ifndef GPS_H
#define GPS_H

void setupGPS();

void updateGPS();

void printGPS();

// Get Relevant Outputs
long getGPSYear();
long getGPSMonth();
long getGPSDay();
int getGPSHour();
int getGPSMinute();
int getGPSSecond();
int getGPSMillisecond();
long getGPSLatitude();
long getGPSLongitude();
long getGPSAltitude();
byte getGPSSIV();
long getGPSHeading();
long getGPSGroundSpeed();
long getGPSPDOP();

#endif