#ifndef GPS_H
#define GPS_H

#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_Ublox_GPS

class wrapGPS
{
private:
    SFE_UBLOX_GPS myGPS;

public:
    wrapGPS();

    void setup();
    void update();
    void print();

    // Get Relevant Outputs
    long getYear();
    long getMonth();
    long getDay();
    int getHour();
    int getMinute();
    int getSecond();
    int getMillisecond();
    long getLatitude();
    long getLongitude();
    long getAltitude();
    byte getSIV();
    long getHeading();
    long getGroundSpeed();
    long getPDOP();
};

#endif