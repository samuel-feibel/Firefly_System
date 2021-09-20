#ifndef ESTIMATESTATE_H
#define ESTIMATESTATE_H

#include <IMU.h>
#include <GPS.h>
#include <barometer.h>
#include <BasicLinearAlgebra.h>

using namespace BLA;
const int Ns = 10;
const int Nm = 9;

class stateEstimator
{
private:
    // Origin stuff
    Matrix<3> r0_ECEF;
    Matrix<3,3>  NED_C_ECEF;
    float dhdp;
    float alt0;
    float p0;

    // Sensor objects
    wrapGPS &myWrapGPS;
    wrapIMU &myWrapIMU;
    wrapBarometer &myWrapBarometer;

    // Estimator Variables
    Matrix<Ns,1> xhat;
    Matrix<Ns,Ns> P;
    Matrix <Ns,6> G;


    void LatLonAlt2ECEF_Fcn(float Lat, float Lon, float Alt, Matrix<3> &r_ECEF);

    void LatLonAlt2NED_Fcn(float Lat, float Lon, float Alt, Matrix<3> &r_NED);

    void setAngle2Range(float &angle);

    void getMeasurementVector(Matrix<9> &Z, Matrix<6> &Z_input);

    void TECEF2NED_Fcn(Matrix<3> &r_ECEF);

    void f_Fcn(Matrix<Ns> &fxhatk_u, Matrix<6> &uk, Matrix<Ns> &fdot);

    void get_F_jac(Matrix<Ns> &xhatk_u, Matrix<6> &uk, Matrix<Ns,Ns> &F_jac);

    void get_Q(float dT, Matrix<6,6> &Q);

    void get_R(float dT, Matrix<9, 9> &R);

    void get_H_jac(Matrix<Ns> &xhat, Matrix<9, Ns> &H_jac);

    void h_fcn(Matrix<Ns> &xhat, Matrix<Nm> &h);

    void predictState(float delt, Matrix<Ns> &xhat, Matrix<6> &uk);

    void timeUpdate(float delt, Matrix<6> &Z_input);

    void measurementUpdate(Matrix<9> &Z);
    
public:
    stateEstimator(wrapGPS &_myWrapGPS, wrapIMU &_myWrapIMU, wrapBarometer &_mywrapBarometer);

    void init();

    void debug();

    void setupR0ECEF();

    void setupP0();

    Matrix<Ns> step(float delt);
};

#endif


