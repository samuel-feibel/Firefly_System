#ifndef GPS_H
#define GPS_H

#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_Ublox_GPS
// protobufs
#include <pb.h>
#include <pb_encode.h>
#include <autopilot.pb.h>

class wrapGPS
{
private:
    // GPSStruct& GPS_struct;
    SFE_UBLOX_GPS myGPS;

public:
    // wrapGPS(GPSStruct &_GPS_struct);
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