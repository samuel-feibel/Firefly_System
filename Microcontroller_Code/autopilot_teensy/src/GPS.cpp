#include <Arduino.h>
#include <Wire.h> //Needed for I2C to GPS
#include "GPS.h"

// Class wrapGPS

wrapGPS::wrapGPS(GPSStruct &_GPS_struct) : GPS_struct(_GPS_struct)
{
}

void wrapGPS::print()
{

    if (1) //(myGPS.getPVT())
    {

        long latitude = myGPS.getLatitude();
        Serial.print(F("Lat: "));
        Serial.print(latitude);

        long longitude = myGPS.getLongitude();
        Serial.print(F(" Long: "));
        Serial.print(longitude);
        Serial.print(F(" (degrees * 10^-7)"));

        long altitude = myGPS.getAltitude();
        Serial.print(F(" Alt: "));
        Serial.print(altitude);
        Serial.print(F(" (mm)"));

        byte SIV = myGPS.getSIV();
        Serial.print(F(" SIV: "));
        Serial.print(SIV);

        long heading = myGPS.getHeading();
        Serial.print(F(" Heading: "));
        Serial.print(heading);

        Serial.println();
    }
    else
    {
        Serial.println("Data Not ready");
    }
}

void wrapGPS::setup()
{

    Wire.begin();

    bool initialized = false;
    while (!initialized)
    {
        // Serial.print("Setting up GPS...");
        if (myGPS.begin() == false) //Connect to the Ublox module using Wire port
        {
            // Serial.println(F("Failed, retrying"));
            delay(500);
        }
        else
        {
            initialized = true;
            // Serial.println(F("Success!"));
        }
    }

    myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)

    //myGPS.enableDebugging(); //Enable debug messages over Serial (default)

    myGPS.setNavigationFrequency(10); //Set output to 10 times a second
    myGPS.setAutoPVT(true);           //Tell the GPS to "send" each solution and the lib not to update stale data implicitly

    myGPS.saveConfiguration(); //Save the current settings to flash and BBR



}

void wrapGPS::update()
{
    myGPS.getPVT();
    // Serial.println(myGPS.getSIV());

    // Add to Struct

    // START WITH TIME DATA
    GPS_struct.year = myGPS.getYear();
    GPS_struct.month = myGPS.getMonth();
    GPS_struct.day = myGPS.getDay();
    GPS_struct.hour = myGPS.getHour();
    GPS_struct.minute = myGPS.getMinute();
    GPS_struct.second = myGPS.getSecond();
    GPS_struct.msec = myGPS.getMillisecond();

    GPS_struct.lat = myGPS.getLatitude() * 1E-7;
    GPS_struct.lon = myGPS.getLongitude() * 1E-7;
    GPS_struct.alt = myGPS.getAltitude() * 1E-3;
    GPS_struct.groundSpeed = myGPS.getGroundSpeed() * 1E-3;
    GPS_struct.heading = myGPS.getHeading() * 1E-5 * M_PI / 180;
    GPS_struct.SIV = myGPS.getSIV();

    // Calculate NED
    Matrix <3> r_NED;
    LatLonAlt2NED_Fcn(GPS_struct.lat,GPS_struct.lon, GPS_struct.alt,NED_C_ECEF0, r_NED);
    for (int i = 1; i < 3; i++)
    {
        GPS_struct.position_NED[i] = r_NED(i);
    }

    // Set origin for linearization
    if ( (GPS_struct.SIV > 2) && hasLinearized==0){
        LatLonAlt2ECEF_Fcn(GPS_struct.lat, GPS_struct.lon, GPS_struct.alt, r0_ECEF);
        TECEF2NED_Fcn(r0_ECEF, NED_C_ECEF0);
        hasLinearized = 1;
    }
    
    // GPS_struct.hasLinearized = hasLinearized;    can remove hasLinearized with this addition
    
}

void wrapGPS::LatLonAlt2NED_Fcn(float lat, float lon, float alt, Matrix<3,3> &NED_C_ECEF, Matrix<3> &r_NED)
{
    Matrix<3> r_ECEF;
    LatLonAlt2ECEF_Fcn(lat, lon, alt, r_ECEF);
    r_NED = NED_C_ECEF * (r_ECEF - r0_ECEF);
}

void wrapGPS::LatLonAlt2ECEF_Fcn(float Lat, float Lon, float Alt, Matrix<3> &r_ECEF)
{

    Lat = Lat * M_PI / 180.0;
    Lon = Lon * M_PI / 180.0;
    float a = 6378137.0;      // m
    float b = 6356752.314245; // m
    float cosLat = cos(Lat);
    float sinLat = sin(Lat);
    float cosLon = cos(Lon);
    float sinLon = sin(Lon);
    float a2 = a * a;
    float denom = sqrt(a * a * cosLat * cosLat + b * b * sinLat * sinLat);
    float N = a2 / denom;

    r_ECEF = {(N + Alt) * cosLat * cosLon,
              (N + Alt) * cosLat * sinLon,
              ((b * b) * N / (a * a) + Alt) * sinLat};
}

void wrapGPS::TECEF2NED_Fcn(Matrix<3> &r_ECEF, Matrix<3,3> &NED_C_ECEF)
{
    float phi = asin(r_ECEF(2) / norm3(r_ECEF));
    float lambda = atan2(r_ECEF(1), r_ECEF(0));

    NED_C_ECEF = {-sin(phi) * cos(lambda), -sin(lambda), -cos(phi) * cos(lambda),
                  -sin(phi) * sin(lambda), cos(lambda), -cos(phi) * sin(lambda),
                  cos(phi), 0, -sin(phi)};
}