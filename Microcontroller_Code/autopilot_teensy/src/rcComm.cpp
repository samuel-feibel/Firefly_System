#include <rcComm.h>

rcComm::rcComm(ModeStruct &_mode_struct, ReceiverStruct &_reciever_struct, ServosStruct &_servo_struct) : mode_struct(_mode_struct),
                                                                                                          reciever_struct(_reciever_struct),
                                                                                                          servo_struct(_servo_struct)
{
}

void rcComm::setup()
{
    HWSERIAL.begin(9600);
}

void rcComm::getRecieverSignals()
{
    byte buf[6];
    // put your main code here, to run repeatedly:
    while (HWSERIAL.available() > 6)
    {

        HWSERIAL.readBytesUntil(200, buf, 8);
    }

    for (int i=0; i<6; i++){
        Serial.print(buf[i]);
        Serial.print(",");
    }
    Serial.println("");

    copy(&servo_struct.servoVals[0], &buf[0], 6);

    // Some logic HERE
    mode_struct.autoMode = int(buf[4]);
    mode_struct.auxMode = int(buf[5]);
}