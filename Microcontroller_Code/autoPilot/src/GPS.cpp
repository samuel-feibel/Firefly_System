#include <Arduino.h>
#include <Wire.h>                           //Needed for I2C to GPS
#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_Ublox_GPS

SFE_UBLOX_GPS myGPS;

void printGPS()
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

void setupGPS()
{

    Wire.begin();

    bool initialized = false;
    while (!initialized)
    {
        Serial.print("Setting up GPS...");
        if (myGPS.begin() == false) //Connect to the Ublox module using Wire port
        {
            Serial.println(F("Failed, retrying"));
            delay(500);
        }
        else
        {
            initialized = true;
            Serial.println(F("Success!"));
        }
    }

    myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)

    //myGPS.enableDebugging(); //Enable debug messages over Serial (default)

    myGPS.setNavigationFrequency(10); //Set output to 10 times a second
    myGPS.setAutoPVT(true);           //Tell the GPS to "send" each solution and the lib not to update stale data implicitly

    myGPS.saveConfiguration(); //Save the current settings to flash and BBR
}

void updateGPS()
{
    myGPS.getPVT();
    //  Serial.print(" GPS Available: ");
    //  Serial.print(myGPS.getPVT());
}

// Get Relevant Outputs
long getGPSYear()
{
    return myGPS.getYear();
}
long getGPSMonth()
{
    return myGPS.getMonth();
}
long getGPSDay()
{
    return myGPS.getDay();
}
int getGPSHour()
{
    return myGPS.getHour();
}
int getGPSMinute()
{
    return myGPS.getMinute();
}
int getGPSSecond()
{
    return myGPS.getSecond();
}
int getGPSMillisecond()
{
    return myGPS.getMillisecond();
}
long getGPSLatitude()
{
    return myGPS.getLatitude();
}
long getGPSLongitude()
{
    return myGPS.getLongitude();
}
long getGPSAltitude()
{
    return myGPS.getAltitude();
}
byte getGPSSIV()
{
    return myGPS.getSIV();
}
long getGPSHeading()
{
    return myGPS.getHeading();
}
long getGPSGroundSpeed()
{
    return myGPS.getGroundSpeed();
}
long getGPSPDOP()
{
    return myGPS.getPDOP();
}