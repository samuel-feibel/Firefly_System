#include <sensors.h>

Sensors::Sensors(SensorStruct &_sensor_Struct): 
sensor_struct(_sensor_Struct),
myWrapBarometer(sensor_struct.baro),
myWrapIMU(sensor_struct.IMU),
myWrapGPS(sensor_struct.GPS)
{
    sensor_struct.has_baro = true;
    sensor_struct.has_IMU = true;
    sensor_struct.has_GPS = true;
}


void Sensors::setup(){
    myWrapBarometer.setup();
    myWrapIMU.setup();
    myWrapGPS.setup();
}

void Sensors::update(){
    // Update Individual Sensors
    myWrapBarometer.update();
    myWrapIMU.update();
    myWrapGPS.update();

    // Update Measurement Vector
    copy(&sensor_struct.z_input[0], &sensor_struct.IMU.gyr[0], 3);
    copy(&sensor_struct.z_input[3], &sensor_struct.IMU.acc[0], 3);

    copy(&sensor_struct.z[0], &sensor_struct.IMU.rawMag[0], 3);
    copy(&sensor_struct.z[3], &sensor_struct.GPS.position_NED[0], 3);
    sensor_struct.z[6] = sensor_struct.baro.alt;
    copy(&sensor_struct.z[7], &sensor_struct.GPS.velocity_NED[0], 3);

    }