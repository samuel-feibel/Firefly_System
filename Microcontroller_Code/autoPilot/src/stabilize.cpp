#include <Arduino.h>
#include <servos.h>

//  --- Stabilize --- //
void stabilize(float *receiverInput, float *servoInput, float *state)
{
    // Controls
    servoInput[0] = 0;  // Throttle
    servoInput[1] = 90; // Elevator
    servoInput[2] = 90; // Aileron
    servoInput[3] = 90; // Rudder

    // Actuate Measurements
    writeServosAngle(&servoInput[0]);
}
