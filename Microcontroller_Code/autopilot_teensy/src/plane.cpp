
// Includes
#include <plane.h>
// using namespace BLA;
#include <example.pb.h>




// Stabilizer
plane::plane(): plane_buf(),
 mySensor(plane_buf.sensors)
{
  // --- Protobufs --- //

  // Sensors
  plane_buf.has_sensors = true;

}

void plane::setup()
{
  // Critical

  Serial.begin(115200);

  mySensor.setup();

  
  /*
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
*/
  // Last
  // wdt_enable(WDTO_60MS); // This needs to be last
  prevLoopTime = millis();
  prevAuxMode = 0;
}

void plane::loop()
{
  if ((millis() - prevLoopTime) > 500)
  {
    
    plane_buf.delt = (millis() - prevLoopTime) / 1000.0;
    prevLoopTime = millis();

    mySensor.update();

    //DEBUG
    // delt = .2;
    // Serial.print("Time: ");
    // Serial.println(delt);
    // wdt_reset();
  /*

    // Read Reciever
    static float receiverInput[4] = {0, 0, 0, 0};
    static float servoInput[4] = {0, 0, 0, 0};
    bool autoMode = 0;
    int auxMode = 0;

    // Update Sensors
    // mySensors.update(plane_buf.sensors);

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

*/

 // write data
  uint8_t packet_buffer[128];
  pb_ostream_t stream = pb_ostream_from_buffer(packet_buffer, sizeof(packet_buffer));

  bool status = pb_encode(&stream, PlaneBuf_fields, &plane_buf);
  int packet_length = stream.bytes_written;
  // Serial.println(packet_length);

  Serial.println(base64_encode(packet_buffer, packet_length).c_str());

}

}