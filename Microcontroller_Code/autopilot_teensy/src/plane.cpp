
// Includes
#include <plane.h>

plane::plane() : plane_buf(), mySensor(plane_buf.sensors), myStateEstimator(plane_buf.stateEstimator), myWrapSD(plane_buf) //, myRcComm(plane_buf.mode,plane_buf.reciever,plane_buf.servos)
{
  // --- Protobufs --- //

  // Sensors
  plane_buf.has_sensors = true;

  // State Estimator
  plane_buf.has_stateEstimator = true;
}

void plane::setup()
{
  // Critical
  Serial.begin(115200);
  // myRcComm.setup();

  // Less Critical

  mySensor.setup();
  mySensor.update();
  while (plane_buf.sensors.GPS.hasLinearized==0 || plane_buf.sensors.baro.hasLinearized==0)
  {
    delay(500);
    mySensor.update();
  }
  myStateEstimator.init();
  card_detected = myWrapSD.setup();

  prevLoopTime = millis();
  prevSerLoopTime = millis();  

  // Last
  // wdt_enable(WDTO_60MS); // This needs to be last

}


void plane::loop()
{

  if ((millis() - prevLoopTime) > 100)
  {

    plane_buf.delt = (millis() - prevLoopTime) / 1000.0;
    prevLoopTime = millis();
    plane_buf.mcTime = millis() / 1000.0;

    // Update Sensors
    mySensor.update();

    // Read Reciever
    
    // myRcComm.getRecieverSignals();


    // Update State Estimate
    myStateEstimator.step(plane_buf.delt, &plane_buf.sensors.z_input[0], &plane_buf.sensors.z[0]);

    // DEBUG
    if (card_detected)
    {
      myWrapSD.writeData();
    }

    /*
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



*/
  }

  if (millis() - prevSerLoopTime > 500)
  {

    prevSerLoopTime = millis();
    // write data
    uint8_t packet_buffer[512];
    pb_ostream_t stream = pb_ostream_from_buffer(packet_buffer, sizeof(packet_buffer));

    bool status = pb_encode(&stream, PlaneBuf_fields, &plane_buf);
    int packet_length = stream.bytes_written;

    // Serial.println(base64_encode(packet_buffer, packet_length).c_str());
    // Serial.println(plane_buf.reciever.rcVals[0]);
    Serial.println("here");
  }
}