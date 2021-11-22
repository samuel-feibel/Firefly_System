#ifndef PLANE_H
#define PLANE_H

// Includes
#include <Arduino.h>
#include <SDs.h>
#include <sensors.h>
// #include <stabilize.h>
#include <estimateState.h>
#include <pb_encode.h>
#include <pb.h>
#include <autopilot.pb.h>
#include <base64.h>
#include <rcComm.h>


// Protobufs

class plane
{
private:
    PlaneBuf plane_buf;
    Sensors mySensor;
    stateEstimator myStateEstimator;
    wrapSD myWrapSD; 
    rcComm myRcComm;

    // --- Settings --- //

    unsigned long prevLoopTime;
    unsigned long prevSerLoopTime;
    int prevAuxMode;
    bool card_detected;


public:
    plane();
    void setup();
    void loop();
};

#endif