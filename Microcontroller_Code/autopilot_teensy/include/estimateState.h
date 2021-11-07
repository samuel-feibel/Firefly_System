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
const int Ns = 13;
const int Ninput = 3;
const int Nm = 6;
const Matrix<3, 1> magVec0 = {-10.732501411437989, 13.064998292922974, 35.80500106811523};

class stateEstimator
{
private:

    // Protobuf
    StateEstimatorStruct &stateEstimator_struct;

    // Estimator Variables
    Matrix<Ns, 1> xhat;
    Matrix<Ns, Ns> P;

    void setAngle2Range(float &angle);

    void quat2euler(Matrix<Ns, 1> &xhat, Matrix<3, 1> &eulerAngles);

    void get_I_C_B(Matrix<Ns, 1> &xhat, Matrix<3, 3> &I_C_B);

    void f_Fcn(Matrix<Ns> &fxhatk_u, Matrix<Ninput> &uk, Matrix<Ns> &f);

    void get_Phi(Matrix<Ns> &xhatk_u, Matrix<Ninput> &uk, float delt, Matrix<Ns, Ns> &Phi);

    void get_Q(Matrix<Ninput, Ninput> &Q);

    void get_R(Matrix<Nm, Nm> &R);

    void get_H_jac(Matrix<Ns> &xhat, Matrix<Nm, Ns> &H_jac);

    void get_G_jac(Matrix<Ns> &xhat, Matrix<Ns, Ninput> &G_jac);

    void h_fcn(Matrix<Ns> &xhat, Matrix<Nm> &h);

    void predictState(float delt, Matrix<Ns> &xhat, Matrix<Ninput> &uk);

    void timeUpdate(float delt, Matrix<Ninput> &Z_input);

    void measurementUpdate(Matrix<Nm> &Z);

public:
    stateEstimator(StateEstimatorStruct &_stateEstimator_struct);

    void init();

    void debug();

    void step(float &delt, float *z_input_arr, float *z_arr);
};

#endif
