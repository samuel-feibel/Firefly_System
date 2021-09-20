#include <Arduino.h>
#include <BasicLinearAlgebra.h>

using namespace BLA;

//  --- Stabilize --- //
void stabilize(float *receiverInput, float *servoInput, Matrix<10> &state)
{
    // Controls
    servoInput[0] = 0;  // Throttle
    servoInput[1] = 90; // Elevator
    servoInput[2] = 90; // Aileron
    servoInput[3] = 90; // Rudder

    // Actuate Measurements
}
