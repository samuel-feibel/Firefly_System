#ifndef ESTIMATESTATE_H
#define ESTIMATESTATE_H

#include <Arduino.h>
#include <math.h>
#include <utils.h>
#include <BasicLinearAlgebra.h>
#include <Streaming.h>
#include <pb_encode.h>
#include <pb.h>
#include <autopilot.pb.h>

using namespace BLA;
const int Ns = 10;
const int Ninput = 6;
const int Nm = 9;
const Matrix<3, 1> magVec0 = {17.1864, 3.8436, 35.9023};

class stateEstimator
{
private:

    // Protobuf
    StateEstimatorStruct &stateEstimator_struct;

    // Estimator Variables
    Matrix<Ns, 1> xhat;
    Matrix<Ns, Ns> P;
    Matrix<Ns, 6> G;

    void setAngle2Range(float &angle);

    void quat2euler(Matrix<Ns, 1> &xhat, Matrix<3, 1> &eulerAngles);

    void get_I_C_B(Matrix<Ns, 1> &xhat, Matrix<3, 3> &I_C_B);

    void f_Fcn(Matrix<Ns> &fxhatk_u, Matrix<6> &uk, Matrix<Ns> &f);

    void get_Phi(Matrix<Ns> &xhatk_u, Matrix<6> &uk, float delt, Matrix<Ns, Ns> &Phi);

    void get_Q(float dT, Matrix<6, 6> &Q);

    void get_R(float dT, Matrix<9, 9> &R);

    void get_H_jac(Matrix<Ns> &xhat, Matrix<9, Ns> &H_jac);

    void get_G_jac(Matrix<Ns> &xhat, Matrix<Ns, 6> &G_jac);

    void h_fcn(Matrix<Ns> &xhat, Matrix<Nm> &h);

    void predictState(float delt, Matrix<Ns> &xhat, Matrix<6> &uk);

    void timeUpdate(float delt, Matrix<6> &Z_input);

    void measurementUpdate(Matrix<9> &Z);

public:
    stateEstimator(StateEstimatorStruct &_stateEstimator_struct);

    void init();

    void debug();

    void step(float &delt, float *z_input_arr, float *z_arr);
};

#endif
