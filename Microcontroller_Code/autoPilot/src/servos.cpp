#include <Arduino.h>
#include <Servo.h>
#include <rcTiming.h>

// --- Servo Limits --- //
#define THROTTLE_MIN 0
#define THROTTLE_MAX 180
#define THROTTLE_MID (THROTTLE_MIN + THROTTLE_MAX) / 2
#define ELEVATOR_MIN 0
#define ELEVATOR_MAX 180
#define ELEVATOR_MID (ELEVATOR_MIN + ELEVATOR_MAX) / 2
#define AILERON_MIN 00
#define AILERON_MAX 180
#define AILERON_MID (AILERON_MIN + AILERON_MAX) / 2
#define RUDDER_MIN 0
#define RUDDER_MAX 180
#define RUDDER_MID (RUDDER_MIN + RUDDER_MAX) / 2

// --- Switch Thresholds ---//
#define AUXMODE_LOW 1300
#define AUXMODE_HIGH 1700
#define AUTOMODE_MID 1500

// --- Pin Outs --- //
#define THROTTLE_OUT_PIN 7
#define AILERON_OUT_PIN 6
#define ELEVATOR_OUT_PIN 5
#define RUDDER_OUT_PIN 4

#define PWM_MAX 1900
#define PWM_MIN 1100

Servo rudderServo;
Servo elevatorServo;
Servo aileronServo;

static float pwm_map(volatile unsigned long pwm_onTime, int ANGLE_MAX, int ANGLE_MIN)
{
  float Angle = float((ANGLE_MAX - ANGLE_MIN) * (float(pwm_onTime) - PWM_MIN) / (PWM_MAX - PWM_MIN) + ANGLE_MIN);
  if (Angle < ANGLE_MIN)
  {
    Angle = ANGLE_MIN;
  }
  else if (Angle > ANGLE_MAX)
  {
    Angle = ANGLE_MAX;
  }
  return Angle;
}

static void pwm_limit(float *angle, int ANGLE_MAX, int ANGLE_MIN)
{
  if (*angle < ANGLE_MIN)
  {
    *angle = ANGLE_MIN;
  }
  else if (*angle > ANGLE_MAX)
  {
    *angle = ANGLE_MAX;
  }
}

void setup_Servos()
{
  rudderServo.attach(RUDDER_OUT_PIN);
  elevatorServo.attach(ELEVATOR_OUT_PIN);
  aileronServo.attach(AILERON_OUT_PIN);
}

void writeServosAngle(float *inputAngle)
{

  pwm_limit(&inputAngle[1], AILERON_MAX, AILERON_MIN);
  pwm_limit(&inputAngle[2], ELEVATOR_MAX, ELEVATOR_MIN);
  pwm_limit(&inputAngle[3], RUDDER_MAX, RUDDER_MIN);

  elevatorServo.write(inputAngle[1]);
  aileronServo.write(inputAngle[2]);
  rudderServo.write(inputAngle[3]);
}

void writeServosPWM(volatile unsigned long *inputPWM)
{
  elevatorServo.write(pwm_map(inputPWM[1], AILERON_MAX, AILERON_MIN));
  aileronServo.write(pwm_map(inputPWM[2], ELEVATOR_MAX, ELEVATOR_MIN));
  rudderServo.write(pwm_map(inputPWM[3], RUDDER_MAX, RUDDER_MIN));
}

void getRCSignalAngle(float *recieverInput, bool *autoMode, int *auxMode)
{
  unsigned long rcT[6];
  getRCSignalPWM(&rcT[0]);

  // Calculate Reciever Inputs
  recieverInput[0] = pwm_map(rcT[0], THROTTLE_MAX, THROTTLE_MIN);
  recieverInput[1] = pwm_map(rcT[1], ELEVATOR_MAX, ELEVATOR_MIN);
  recieverInput[2] = pwm_map(rcT[2], AILERON_MAX, AILERON_MIN);
  recieverInput[3] = pwm_map(rcT[3], RUDDER_MAX, RUDDER_MIN);
  *autoMode = (rcT[4] > AUTOMODE_MID);
  if (rcT[5] > AUXMODE_HIGH)
  {
    *auxMode = 2;
  }
  else if (rcT[5] > AUXMODE_LOW)
  {
    *auxMode = 1;
  }
  else
  {
    *auxMode = 0;
  }
}