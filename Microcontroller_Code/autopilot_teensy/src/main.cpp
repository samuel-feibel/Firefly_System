/* RC Aircraft Autopilot
 * Written by Samuel Feibel
 *
 * TODO:
 * - Check all units and constants for errors
 * - figure out source of explosion at higher frequencies
*/

// Includes
#include <main.h>
#include <vector>
#include <string>
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

// Protobufs
Example exam = Example_init_zero;

void setup()
{
  // Critical Setup
  Serial.begin(115200);

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
  prevLoopTime = millis();
}

void loop()
{

  if ((millis() - prevLoopTime) > 500)
  {
    float delt = (millis() - prevLoopTime) / 1000.0;
    
    //DEBUG
    // delt = .2;
    // Serial.print("Time: ");
    // Serial.println(delt);
    prevLoopTime = millis();
    wdt_reset();

    // Read Reciever
    static float receiverInput[4] = {0, 0, 0, 0};
    static float servoInput[4] = {0, 0, 0, 0};
    bool autoMode = 0;
    int auxMode = 0;

    // Update Sensors
    myWrapGPS.update();
    myWrapIMU.update();
    myWrapBarometer.update();

    // Update State Estimate
    // myStateEstimator.init();                          // THIS IS A DEBUG STEP
    Matrix<Ns, 1> xhat = myStateEstimator.step(delt); 
    // Matrix<Ns, 1> xhat;
    // xhat.Fill(0);

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

    // DEBUG
    if (card_detected)
    {
      myWrapSD.open();
      myWrapSD.writeData(xhat, &servoInput[0], &receiverInput[0], autoMode, auxMode);
      myWrapSD.close();
    }

    exam.value = 15;

    uint8_t packet_buffer[64];
    pb_ostream_t stream = pb_ostream_from_buffer(packet_buffer, sizeof(packet_buffer));

    bool status = pb_encode(&stream, Example_fields, &exam);
    int packet_length = stream.bytes_written;

    Serial.println("here");
    Serial.println(base64_encode(packet_buffer, packet_length).c_str());

    // pb_ostream_s pb_out = as_pb_ostream(Serial);
    // bool status = pb_encode(&pb_out, Example_fields, &exam);

    // Serial.println(status);
    // pb_ostream_t stream = pb_ostream_from_buffer(packet_buffer,sizeof(packet_buffer));

    // int packet_length = stream.bytes_written;
    // Serial.println(stream.state);

    // Debug Prints
    // Serial << myWrapIMU.getRawmagX() << " " << myWrapIMU.getRawmagY() << " " << myWrapIMU.getRawmagZ() << " " << endl;
    // Serial << sqrt(myWrapIMU.getRawmagX() * myWrapIMU.getRawmagX() + myWrapIMU.getRawmagY() * myWrapIMU.getRawmagY() + myWrapIMU.getRawmagZ() * myWrapIMU.getRawmagZ() ) << endl;
    // Serial << sqrt(myWrapIMU.getmagX() * myWrapIMU.getmagX() + myWrapIMU.getmagY() * myWrapIMU.getmagY() + myWrapIMU.getmagZ() * myWrapIMU.getmagZ() ) << endl;
    // auto temp = xhat.Submatrix<3,1>(3,0);
    // Serial << temp << endl;
    // Serial.println("here");
  }
}