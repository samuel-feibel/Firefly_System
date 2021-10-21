#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
// protobufs
#include <pb.h>
#include <pb_encode.h>
#include <autopilot.pb.h>

// Sensors
#include <barometer.h>
#include <IMU.h>
#include <GPS.h>

class Sensors
{
    private:
        SensorStruct& sensor_struct;
        wrapBarometer myWrapBarometer;
        wrapIMU myWrapIMU;
        wrapGPS myWrapGPS;
        
    public:
        Sensors(SensorStruct &_sensor_Struct);

        void setup(); 

        void update();

};

#endif