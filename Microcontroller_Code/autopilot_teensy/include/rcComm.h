#ifndef RCCOMM_H
#define RCCOMM_H

#include <Arduino.h>
#include <pb_encode.h>
#include <pb.h>
#include <autopilot.pb.h>
#include <utils.h>

#define HWSERIAL Serial1

class rcComm
{
private:
    ModeStruct &mode_struct;
    ReceiverStruct &reciever_struct;
    ServosStruct &servo_struct;

    byte prevRCsignal[6];


public:
    rcComm(ModeStruct &_mode_struct, ReceiverStruct &_reciever_struct, ServosStruct &_servo_struct);

    void setup();

    void getRecieverSignals();

    void sendServoSignals();
};

#endif