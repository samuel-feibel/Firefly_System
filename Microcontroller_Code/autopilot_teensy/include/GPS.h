#ifndef GPS_H
#define GPS_H

#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_Ublox_GPS
#include <Arduino.h>
#include <BasicLinearAlgebra.h>
#include <utils.h>

// protobufs
#include <pb.h>
#include <pb_encode.h>
#include <autopilot.pb.h>

using namespace BLA;

class wrapGPS
{
private:
    GPSStruct& GPS_struct;
    SFE_UBLOX_GPS myGPS;
    Matrix<3,3> NED_C_ECEF0;
    Matrix<3> r0_ECEF;

    bool hasLinearized = 0;

    void LatLonAlt2ECEF_Fcn(float Lat, float Lon, float Alt, Matrix<3> &r_ECEF);

    void LatLonAlt2NED_Fcn(float lat, float lon, float alt, Matrix<3,3> &NED_C_ECEF, Matrix<3> &r_NED);

    void TECEF2NED_Fcn(Matrix<3> &r_ECEF, Matrix<3,3> &NED_C_ECEF);

public:
    wrapGPS(GPSStruct &_GPS_struct);

    void setup();
    void update();
    void print();

};

#endif