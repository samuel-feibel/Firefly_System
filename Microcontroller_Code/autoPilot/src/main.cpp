// Includes
#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <SPI.h>
#include <ICM_20948.h>
#include <SparkFun_Ublox_Arduino_Library.h>
#include <SD.h>
#include <avr/wdt.h>

#include <RCTIMING_H.h>
#include <SERVOS_H.h>
#include <GPS_H.h>
#include <IMU_H.h>
#include <SD_H.h>
#include <HELPFULFUNCTIONS_H.h>
#include <STABILIZE_H.h>

// --- Constants --- //
#define pi 2.0 * asin(1.0)

// --- Settings --- //

unsigned long prevLoopTime = 0;
int prevAuxMode = 0;
bool card_detected;

void setup()
{
  // Critical Setup
  Serial.begin(115200);
  setup_Servos();
  setup_rcTiming();

  // Less Critical
  setupGPS();
  updateGPS();
  card_detected = setupSD();
  setup_IMU();
  pinMode(LED_BUILTIN, OUTPUT);

  // Last
  wdt_enable(WDTO_60MS); // This needs to be last
}

void loop()
{

  if ((millis() - prevLoopTime) > 39)
  {
    // Serial.print("Time: ");
    // Serial.println((millis() - prevLoopTime));
    prevLoopTime = millis();
    wdt_reset();

    // State Vector Initialize
    static double state[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    // Read Reciever
    static double receiverInput[4] = {0, 0, 0, 0};
    static double servoInput[4] = {0, 0, 0, 0};
    bool autoMode;
    int auxMode;
    getRCSignalAngle(&receiverInput[0], &autoMode, &auxMode);

    // Update Sensors
    updateGPS();
    updateIMU();

    // Update State Estimate

    // Mode Logic
    if (autoMode)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      stabilize(&receiverInput[0], &servoInput[0], &state[0]);
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
      copy(&servoInput[0], &receiverInput[0], 4);
    }

    // Write Data
    if (card_detected && (prevAuxMode != 2 && auxMode == 2))
    {
      openSD();
    }

    if (card_detected && (prevAuxMode == 2 && auxMode != 2))
    {
      closeSD();
    }
    prevAuxMode = auxMode;

    if (card_detected && auxMode == 2)
    {
      writeData(&state[0], &servoInput[0], &receiverInput[0], &autoMode, &auxMode);
    }

    // Debug Prints
    // Serial.println(getGPSYear());
    // printGPS();
    // printIMU();
    // Serial.println(receiverInput[1] );

  }
}