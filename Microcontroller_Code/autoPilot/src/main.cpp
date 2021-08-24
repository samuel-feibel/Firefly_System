// Includes
#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <SPI.h>
#include <ICM_20948.h>
#include <SparkFun_Ublox_Arduino_Library.h>
#include <SD.h>
#include <avr/wdt.h>
#include <math.h>
#include <BasicLinearAlgebra.h>

#include <RCTIMING_H.h>
#include <SERVOS_H.h>
#include <GPS_H.h>
#include <IMU_H.h>
#include <barometer.h>
#include <SD_H.h>
#include <HELPFULFUNCTIONS_H.h>
#include <STABILIZE_H.h>
#include <test.h>
#include <mcadd.h>
#include <estimateState.h>


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
  setup_Barometer();
  pinMode(LED_BUILTIN, OUTPUT);
  setupR0ECEF();
  setupP0();

  // Last
  // wdt_enable(WDTO_60MS); // This needs to be last
}

void loop()
{

  if (millis() - prevLoopTime > 999){
    double delt = (millis() - prevLoopTime)/1000.0;
    
    // Serial.print("Time: ");
    // Serial.println(delt);
    prevLoopTime = millis();
    wdt_reset();

    // State Vector Initialize
    static double xhat[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};

    // Read Reciever
    static double receiverInput[4] = {0, 0, 0, 0};
    static double servoInput[4] = {0, 0, 0, 0};
    bool autoMode;
    int auxMode;
    getRCSignalAngle(&receiverInput[0], &autoMode, &auxMode);

    // Update Sensors
    updateGPS();
    updateIMU();
    updateBarometer();

    // Update State Estimate
    estimateState(&xhat[0], delt);
    

    // Mode Logic
    if (autoMode)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      stabilize(&receiverInput[0], &servoInput[0], &xhat[0]);
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
      writeData(&xhat[0], &servoInput[0], &receiverInput[0], &autoMode, &auxMode);
    }

    // Debug Prints
    // Serial.println(volume(3.0,3.0,3.0));
    // double magX = getIMUmagX();
    // double magY = getIMUmagY();
    // double magZ = getIMUmagZ();
    // Serial.println(sqrt(magX*magX+magY*magY+magZ*magZ));
    // Serial.println(getGPSYear());
    // printGPS();
    // printIMU();
    // Serial.println(receiverInput[1] );
    // Serial.println(getGPSSIV());
    // Serial.println(autoMode);
    // Serial.println(mcadd(1,1));
    // double Lat = getGPSLatitude();
    // double Lon = getGPSLongitude();
    // double Alt = getGPSAltitude();
    // Serial.print(Lat);
    // Serial.print(" ");
    // Serial.print(Lon);
    // Serial.print(" ");
    // Serial.println(Alt);
  }
}