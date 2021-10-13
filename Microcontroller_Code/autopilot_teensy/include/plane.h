#ifndef PLANE_H
#define PLANE_H

// Includes
#include <Arduino.h>
// #include <Wire.h>
// #include <SPI.h>
// #include <SD.h>
// #include <avr/wdt.h>
// #include <math.h>
// #include <BasicLinearAlgebra.h>
// #include <Streaming.h>
// #include <base64.h>
// #include <GPS.h>
// #include <IMU.h>
// #include <barometer.h>
// #include <SDs.h>
#include <sensors.h>
// #include <utils.h>
// #include <stabilize.h>
// #include <test.h>
// #include <estimateState.h>
#include <pb_encode.h>
#include <pb.h>
#include <autopilot.pb.h>
#include <base64.h>

// Protobufs

class plane
{
private:
    PlaneBuf plane_buf;
    Sensors mySensor(SensorStruct);
    // Objects
    // wrapSD myWrapSD;
    // Sensors mySensors;
    // stateEstimator myStateEstimator;

    // --- Settings --- //

    unsigned long prevLoopTime;
    int prevAuxMode;
    bool card_detected;

public:
    plane();
    void setup();
    void loop();
};

#endif