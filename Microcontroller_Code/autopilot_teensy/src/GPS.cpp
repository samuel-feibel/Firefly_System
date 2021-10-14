#include <Arduino.h>
#include <Wire.h> //Needed for I2C to GPS
#include "GPS.h"

// Class wrapGPS

wrapGPS::wrapGPS(GPSStruct &_GPS_struct): GPS_struct(_GPS_struct)
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

    // Add to Struct

    // START WITH TIME DATA

    GPS_struct.lat = myGPS.getLatitude() * 1E-7;
    GPS_struct.lon = myGPS.getLongitude() * 1E-7;
    GPS_struct.alt = myGPS.getAltitude() * 1E-3;
    GPS_struct.groundSpeed = myGPS.getGroundSpeed() * 1E-3;
    GPS_struct.heading = myGPS.getHeading() * 1E-5 * M_PI / 180;
    GPS_struct.SIV = myGPS.getSIV();

    // Calculate NED
}

// Get Relevant Outputs
long wrapGPS::getYear()
{
    return myGPS.getYear();
}
long wrapGPS::getMonth()
{
    return myGPS.getMonth();
}
long wrapGPS::getDay()
{
    return myGPS.getDay();
}
int wrapGPS::getHour()
{
    return myGPS.getHour();
}
int wrapGPS::getMinute()
{
    return myGPS.getMinute();
}
int wrapGPS::getSecond()
{
    return myGPS.getSecond();
}
int wrapGPS::getMillisecond()
{
    return myGPS.getMillisecond();
}
long wrapGPS::getLatitude()
{
    return myGPS.getLatitude();
}
long wrapGPS::getLongitude()
{
    return myGPS.getLongitude();
}
long wrapGPS::getAltitude()
{
    return myGPS.getAltitude();
}
byte wrapGPS::getSIV()
{
    return myGPS.getSIV();
}
long wrapGPS::getHeading()
{
    return myGPS.getHeading();
}
long wrapGPS::getGroundSpeed()
{
    return myGPS.getGroundSpeed();
}
long wrapGPS::getPDOP()
{
    return myGPS.getPDOP();
}
