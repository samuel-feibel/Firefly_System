#include <SDs.h>

#define outputProtoBuf 0
#define sigFigs 7

wrapSD::wrapSD(PlaneBuf &_plane_buf) : plane_buf(_plane_buf) {}

void wrapSD::writeFormattedFloat(float val, uint8_t leading, uint8_t decimals)
{
  float aval = abs(val);
  if (val < 0)
  {
    myFile.print("-");
  }
  else
  {
    myFile.print(" ");
  }
  for (uint8_t indi = 0; indi < leading; indi++)
  {
    uint32_t tenpow = 0;
    if (indi < (leading - 1))
    {
      tenpow = 1;
    }
    for (uint8_t c = 0; c < (leading - 1 - indi); c++)
    {
      tenpow *= 10;
    }
    if (aval < tenpow)
    {
      myFile.print("0");
    }
    else
    {
      break;
    }
  }
  if (val < 0)
  {
    myFile.print(-val, decimals);
  }
  else
  {
    myFile.print(val, decimals);
  }
}

void wrapSD::writeVec(float *vec, int size)
{
  for (int i = 0; i < size; i++)
  {
    myFile.print(*vec, sigFigs);
    myFile.print(", ");
    ++vec;
  }
}
bool wrapSD::setup()
{
  //Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.

  if (!SD.begin(BUILTIN_SDCARD))
  {
    // Serial.println("No SD card detected");
    return 0;
  }
  // Serial.println("Setting up SD card...Success");

  if (!outputProtoBuf)
  {
    // First Log Entry
    myFile = SD.open("dataLog.txt", FILE_WRITE);
    myFile.println("================================ Starting Log Protobuf =================================");
    myFile.print("Current Time: ");
    myFile.print(plane_buf.sensors.GPS.year);
    myFile.print("-");
    myFile.print(plane_buf.sensors.GPS.month);
    myFile.print("-");
    myFile.print(plane_buf.sensors.GPS.day);
    myFile.print(" ");
    myFile.print(plane_buf.sensors.GPS.hour);
    myFile.print(":");
    myFile.print(plane_buf.sensors.GPS.minute);
    myFile.print(":");
    myFile.print(plane_buf.sensors.GPS.second);
    myFile.println("");
    // Data Type Header
    myFile.print("Time (ms), ");
    myFile.print("Acc x (m/s^2), ");
    myFile.print("Acc y (m/s^2), ");
    myFile.print("Acc z (m/s^2), ");
    myFile.print("Gyr (rad/s) x, ");
    myFile.print("Gyr (rad/s) y, ");
    myFile.print("Gyr (rad/s) z, ");
    myFile.print("Mag (uT) x, ");
    myFile.print("Mag (uT) y, ");
    myFile.print("Mag (uT) z, ");
    myFile.print("rawGyr (deg/s) x, ");
    myFile.print("rawGyr (deg/s) y, ");
    myFile.print("rawGyr (deg/s) z, ");
    myFile.print("rawMag (uT) x, ");
    myFile.print("rawMag (uT) y, ");
    myFile.print("rawMag (uT) z, ");
    myFile.print("Tmp (C), ");
    myFile.print("Lat, ");
    myFile.print("Lon, ");
    myFile.print("Alt (mm), ");
    myFile.print("Speed (mm/s), ");
    myFile.print("Heading (degrees * 10^-5), ");
    myFile.print("pDOP, ");
    myFile.print("SIV, ");
    myFile.print("N_GPS, ");
    myFile.print("E_GPS, ");
    myFile.print("D_GPS, ");
    myFile.print("Pressure (hPa), ");
    myFile.print("Alt_baro, ");
    myFile.print("Reciever Throttle Val (0-180), ");
    myFile.print("Reciever Aileron Servo (deg), ");
    myFile.print("Reciever Elevator Servo (deg), ");
    myFile.print("Reciever Rudder Servo (deg), ");
    myFile.print("Auto Mode (deg), ");
    myFile.print("Aux Mode, ");
    myFile.print("N_est, ");
    myFile.print("E_est, ");
    myFile.print("D_est, ");
    myFile.print("u_est, ");
    myFile.print("v_est, ");
    myFile.print("w_est, ");
    myFile.print("q1_est, ");
    myFile.print("q2_est, ");
    myFile.print("q3_est, ");
    myFile.print("q4_est, ");
    myFile.print("Servo Throttle Val (0-180), ");
    myFile.print("Servo Aileron Servo (deg), ");
    myFile.print("Servo Elevator Servo (deg), ");
    myFile.print("Servo Rudder Servo (deg)");

    // close file
    myFile.println("");
    myFile.close();
  }

  return 1;
}

void wrapSD::writeData()
{

  if (myFile)
  {
    if (outputProtoBuf)
    {
      // write data
      uint8_t packet_buffer[512];
      pb_ostream_t stream = pb_ostream_from_buffer(packet_buffer, sizeof(packet_buffer));

      bool status = pb_encode(&stream, PlaneBuf_fields, &plane_buf);
      int packet_length = stream.bytes_written;
      // Serial.println(packet_length);

      myFile.println(base64_encode(packet_buffer, packet_length).c_str());
    }
    else
    {
      // --- IMU --- //
      myFile.print(plane_buf.mcTime, sigFigs);
      myFile.print(", ");
      writeVec(&plane_buf.sensors.IMU.acc[0], 3);
      writeVec(&plane_buf.sensors.IMU.gyr[0], 3);
      writeVec(&plane_buf.sensors.IMU.mag[0], 3);
      writeVec(&plane_buf.sensors.IMU.rawGyr[0], 3);
      writeVec(&plane_buf.sensors.IMU.rawMag[0], 3);
      myFile.print(plane_buf.sensors.baro.temperature, sigFigs);
      myFile.print(", ");
      // -- GPS --- //
      myFile.print(plane_buf.sensors.GPS.lat, sigFigs);
      myFile.print(", ");
      myFile.print(plane_buf.sensors.GPS.lon, sigFigs);
      myFile.print(", ");
      myFile.print(plane_buf.sensors.GPS.alt, sigFigs);
      myFile.print(", ");
      myFile.print(plane_buf.sensors.GPS.groundSpeed, sigFigs);
      myFile.print(", ");
      myFile.print(plane_buf.sensors.GPS.heading, sigFigs);
      myFile.print(", ");
      myFile.print(0.00); // PDOP is null
      myFile.print(", ");
      myFile.print(plane_buf.sensors.GPS.SIV);
      myFile.print(", ");
      writeVec(&plane_buf.sensors.GPS.position_NED[0], 3);
      // -- Barometer --//
      myFile.print(plane_buf.sensors.baro.pressure, sigFigs);
      myFile.print(", ");
      myFile.print(plane_buf.sensors.baro.alt, sigFigs);
      myFile.print(", ");
      // -- Receiver Inputs --- //
      myFile.print(0);
      myFile.print(", ");
      myFile.print(0);
      myFile.print(", ");
      myFile.print(0);
      myFile.print(", ");
      myFile.print(0);
      myFile.print(", ");
      myFile.print(0);
      myFile.print(", ");
      myFile.print(0);
      myFile.print(", ");
      // -- States --- //
      writeVec(&plane_buf.stateEstimator.xhat[0], 10);
      // -- Servo Inputs --- //
      myFile.print(0);
      myFile.print(", ");
      myFile.print(0);
      myFile.print(", ");
      myFile.print(0);
      myFile.print(", ");
      myFile.print(0);
      myFile.println("");
    }
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void wrapSD::open()
{
  myFile = SD.open("dataLog.txt", FILE_WRITE);
}

void wrapSD::close()
{
  myFile.close();
}
