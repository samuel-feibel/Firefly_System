#ifndef ESTIMATESTATE_H
#define ESTIMATESTATE_H

#include <IMU.h>
#include <GPS.h>
#include <barometer.h>
#include <BasicLinearAlgebra.h>

using namespace BLA;
const int Ns = 10;

class stateEstimator
{
private:
    // Origin stuff
    float r0_ECEF[3];
    float NED_C_ECEF[9];
    float dhdp;
    float alt0;
    float p0;

    // Sensor objects
    wrapGPS &myWrapGPS;
    wrapIMU &myWrapIMU;
    wrapBarometer &myWrapBarometer;

    // Estimator Variables

    void LatLonAlt2NED_Fcn(float Lat, float Lon, float Alt, float r0_ECEF[3], float NED_C_ECEF[9], float *r_NED);

    void setAngle2Range(float *angle);

    void getMeasurementVector(float *Z, float *Z_input);

    void LatLonAlt2ECEF_Fcn(float Lat, float Lon, float Alt, float *r_ECEF);

    void TECEF2NED_Fcn(float r_ECEF[3], float *NED_C_ECEF);

    void f_Fcn(float *xhatk_u, float *uk, float *fdot);

    void predictState(float delt, float *xhatk_u, float *uk, Matrix<Ns> &xhatkp1_p);

public:
    stateEstimator(wrapGPS &_myWrapGPS, wrapIMU &_myWrapIMU, wrapBarometer &_mywrapBarometer);

    void debug();

    void setupR0ECEF();

    void setupP0();

    void step(float *xhatk_u, float delt);
};

#endif
