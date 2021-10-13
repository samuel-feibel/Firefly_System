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
#include <pb_encode.h>
#include <autopilot.pb.h>
#include <base64.h>

class wrapSD{

    private:

    // File
    File myFile;

    void writeFormattedFloat(float val, uint8_t leading, uint8_t decimals);

    public:
    wrapSD();
    bool setup(PlaneBuf &plane_buf);
    void writeData(PlaneBuf &plane_buf);
    void open();
    void close();





};

#endif