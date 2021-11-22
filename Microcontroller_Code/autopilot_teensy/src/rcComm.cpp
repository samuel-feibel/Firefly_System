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

    // Correct for some errors in transmitted signals
    for (int i = 0; i < 6; i++)
    {
        if (buf[i] > 180)
        {
            buf[i] = prevRCsignal[i];
        }
        prevRCsignal[i] = buf[i];
    }

    // Copy receiver vals
    copy(&reciever_struct.rcVals[0], &buf[0], 6);

    // Set Modes
    mode_struct.autoMode = (buf[4] > 90);

    if (buf[4] > 138)
    {
        mode_struct.auxMode = 1;
    }
    else if (buf[4] > 48)
    {
        mode_struct.auxMode = 2;
    }
    else
    {
        mode_struct.auxMode = 3;
    }
}

void rcComm::sendServoSignals()
{
    servo_struct.servoVals[0] = 20;
    servo_struct.servoVals[1] = 20;
    servo_struct.servoVals[2] = 20;
    servo_struct.servoVals[3] = 20;
    servo_struct.servoVals[4] = 20;
    servo_struct.servoVals[5] = 20;
    
    byte servoSignals[7];
    copy(&servoSignals[0], &servo_struct.servoVals[0], 6);

    // Transfer Data
    servoSignals[6] = 200;
    HWSERIAL.write(servoSignals, 7);
}