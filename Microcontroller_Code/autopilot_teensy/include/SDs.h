#ifndef SD_H
#define SD_H
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>                           //Needed for I2C to GPS
#include <GPS.h>
#include <barometer.h>
#include <IMU.h>
#include <BasicLinearAlgebra.h>

class wrapSD{

    private:

    // File
    File myFile;

    // Sensor objects
    wrapGPS &myWrapGPS;
    wrapIMU &myWrapIMU;
    wrapBarometer &myWrapBarometer;

    void writeFormattedFloat(float val, uint8_t leading, uint8_t decimals);

    public:
    wrapSD(wrapGPS &_myWrapGPS, wrapIMU &_myWrapIMU, wrapBarometer &_mywrapBarometer);
    bool setup();
    void writeData(BLA::Matrix<10,1> &xhat, float *servoInput, float *receiverInput, bool &autoMode, int &auxMode);
    void open();
    void close();





};

#endif