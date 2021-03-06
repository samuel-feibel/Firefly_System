/* RC Aircraft Autopilot
 * Written by Samuel Feibel
 *
 * TODO:
 * - Change pointers in estimator class to references
 * - consider implementation of some sort of array/vector/matrix object
 * - Run estimator and inverse
 * - Debug
*/

// Includes
#include <main.h>

using namespace BLA;

// --- Settings --- //

unsigned long prevLoopTime = 0;
int prevAuxMode = 0;
bool card_detected;

// --- Objects --- //

// Sensors
wrapGPS myWrapGPS;
wrapIMU myWrapIMU;
wrapBarometer myWrapBarometer;

// Estimator
stateEstimator myStateEstimator(myWrapGPS, myWrapIMU, myWrapBarometer);

// SD Card
wrapSD myWrapSD(myWrapGPS, myWrapIMU, myWrapBarometer);

// Stabilizer

void setup()
{
  // Critical Setup
  Serial.begin(115200);
  setup_Servos();
  setup_rcTiming();

  // Less Critical
  myWrapGPS.setup();
  myWrapGPS.update();
  card_detected = myWrapSD.setup();
  myWrapIMU.setup();
  myWrapBarometer.setup();
  pinMode(LED_BUILTIN, OUTPUT);
  // myStateEstimator.setupR0ECEF();
  myStateEstimator.setupP0();
  myStateEstimator.init();

  // Last
  // wdt_enable(WDTO_60MS); // This needs to be last
}

void loop()
{

  if ((millis() - prevLoopTime) > 100)
  {
    float delt = (millis() - prevLoopTime) / 1000.0;

    // Serial.print("Time: ");
    // Serial.println(delt);
    prevLoopTime = millis();
    wdt_reset();

    // Read Reciever
    static float receiverInput[4] = {0, 0, 0, 0};
    static float servoInput[4] = {0, 0, 0, 0};
    bool autoMode;
    int auxMode;
    getRCSignalAngle(&receiverInput[0], &autoMode, &auxMode);

    // Update Sensors
    myWrapGPS.update();
    myWrapIMU.update();
    myWrapBarometer.update();

    // Update State Estimate
    // myStateEstimator.init(); // THIS IS A DEBUG STEP
    // Matrix<Ns, 1> xhat = myStateEstimator.step(delt); // THIS IS A DEBUG STEP
    Matrix<Ns, 1> xhat;
    xhat.Fill(0);

    // Mode Logic
    if (autoMode)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      stabilize(&receiverInput[0], &servoInput[0], xhat);
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
      copy(&servoInput[0], &receiverInput[0], 4);
    }

    // Write Data
    if (card_detected && (prevAuxMode != 2 && auxMode == 2))
    {
      myWrapSD.open();
    }

    if (card_detected && (prevAuxMode == 2 && auxMode != 2))
    {
      myWrapSD.close();
    }
    prevAuxMode = auxMode;

    if (card_detected && auxMode == 2)
    {
      myWrapSD.writeData(xhat, &servoInput[0], &receiverInput[0], autoMode, auxMode);
    }

    // Debug Prints

    // Serial.println("here");
  }
}