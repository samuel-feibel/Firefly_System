#include <sensors.h>

Sensors::Sensors(SensorStruct &_sensor_Struct): 
sensor_struct(_sensor_Struct),
myWrapBarometer(sensor_struct.baro),
myWrapIMU(sensor_struct.IMU)
myWrapGPS(sensor_struct.GPS)
{
    sensor_struct.has_baro = true;
    sensor_struct.has_IMU = true;
    sensor_struct.has_GPS = true;
}


void Sensors::setup(){
    myWrapBarometer.setup();
    myWrapIMU.setup();
}

void Sensors::update(){
    myWrapBarometer.update();
    myWrapIMU.update();
}