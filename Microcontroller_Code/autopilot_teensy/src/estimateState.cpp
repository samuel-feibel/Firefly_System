#include <estimateState.h>

stateEstimator::stateEstimator(StateEstimatorStruct &_stateEstimator_struct) : stateEstimator_struct(_stateEstimator_struct)
{
}

void stateEstimator::debug()
{
}

void stateEstimator::init()
{
    // User Inputs
    const float quatInitCov = 0.5;
    const float magBiasInitCov = 1;

    // State and Covariance
    xhat = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, -18.075002670288086, -12.075000762939453, 2.9250011444091797}; // uT

    P.Fill(0.0);
    P(0, 0) = quatInitCov * quatInitCov;
    P(1, 1) = quatInitCov * quatInitCov;
    P(2, 2) = quatInitCov * quatInitCov;
    P(3, 3) = quatInitCov * quatInitCov;
    P(10, 10) = magBiasInitCov * magBiasInitCov;
    P(11, 11) = magBiasInitCov * magBiasInitCov;
    P(12, 12) = magBiasInitCov * magBiasInitCov;
}

void stateEstimator::setAngle2Range(float &angle)
{

    if (angle > M_PI)
    {
        angle = angle - 2.0 * M_PI;
    }
}

// Continuous F Function
void stateEstimator::quat2euler(Matrix<Ns, 1> &xhat, Matrix<3, 1> &eulerAngles)
{
    float q1 = xhat(0);
    float q2 = xhat(1);
    float q3 = xhat(2);
    float q4 = xhat(3);

    eulerAngles.Fill(0.0);

    float t2 = q2 * q2;
    float t3 = t2 * 2.0;
    float t4 = -t3;
    eulerAngles(0, 0) = atan2(q1 * q4 * 2.0 + q2 * q3 * 2.0, t4 - (q1 * q1) * 2.0 + 1.0);
    float temp = asin(q1 * q3 * 2.0 + q2 * q4 * 2.0);
    if (temp > 1.0)
    {
        temp = 1.0;
    }
    if (temp < -1.0)
    {
        temp = -1.0;
    }
    eulerAngles(1, 0) = temp;
    eulerAngles(2, 0) = atan2(q1 * q2 * 2.0 + q3 * q4 * 2.0, t4 - (q3 * q3) * 2.0 + 1.0);
}

void stateEstimator::get_I_C_B(Matrix<Ns, 1> &xhat, Matrix<3, 3> &I_C_B)
{
    I_C_B.Fill(0.0);
    float q1 = xhat(0);
    float q2 = xhat(1);
    float q3 = xhat(2);
    float q4 = xhat(3);
    I_C_B(0, 0) = q1 * q1 - q2 * q2 - q3 * q3 + q4 * q4;
    I_C_B(0, 1) = q1 * q2 * 2.0 - q3 * q4 * 2.0;
    I_C_B(0, 2) = q1 * q3 * 2.0 + q2 * q4 * 2.0;
    I_C_B(1, 0) = q1 * q2 * 2.0 + q3 * q4 * 2.0;
    I_C_B(1, 1) = -q1 * q1 + q2 * q2 - q3 * q3 + q4 * q4;
    I_C_B(1, 2) = q1 * q4 * -2.0 + q2 * q3 * 2.0;
    I_C_B(2, 0) = q1 * q3 * 2.0 - q2 * q4 * 2.0;
    I_C_B(2, 1) = q1 * q4 * 2.0 + q2 * q3 * 2.0;
    I_C_B(2, 2) = -q1 * q1 - q2 * q2 + q3 * q3 + q4 * q4;
}

// Continuous Dynamics Function
void stateEstimator::f_Fcn(Matrix<Ns> &xhat, Matrix<Ninput> &uk, Matrix<Ns> &f)
{
    f.Fill(0.0);
    float q1 = xhat(0);
    float q2 = xhat(1);
    float q3 = xhat(2);
    float q4 = xhat(3);
    float N = xhat(4);
    float E = xhat(5);
    float D = xhat(6);
    float vN = xhat(7);
    float vE = xhat(8);
    float vD = xhat(9);
    float mag_bias_x = xhat(10);
    float mag_bias_y = xhat(11);
    float mag_bias_z = xhat(12);

    float p = uk(0);
    float q = uk(1);
    float r = uk(2);
    float fx = uk(3);
    float fy = uk(4);
    float fz = uk(5);

    float t2 = q1 * q1;
    float t3 = q2 * q2;
    float t4 = q3 * q3;
    float t5 = q4 * q4;
    float t6 = q1 * q2 * 2.0;
    float t7 = q1 * q3 * 2.0;
    float t8 = q1 * q4 * 2.0;
    float t9 = q2 * q3 * 2.0;
    float t10 = q2 * q4 * 2.0;
    float t11 = q3 * q4 * 2.0;
    float t12 = -t3;
    float t13 = -t4;
    float t14 = -t5;
    f(0, 0) = (p * q4) / 2.0 - (q * q3) / 2.0 + (q2 * r) / 2.0;
    f(1, 0) = (p * q3) / 2.0 + (q * q4) / 2.0 - (q1 * r) / 2.0;
    f(2, 0) = p * q2 * (-1.0 / 2.0) + (q * q1) / 2.0 + (q4 * r) / 2.0;
    f(3, 0) = p * q1 * (-1.0 / 2.0) - (q * q2) / 2.0 - (q3 * r) / 2.0;
    f(4, 0) = vN;
    f(5, 0) = vE;
    f(6, 0) = vD;
    f(7, 0) = -gravVec0(0) + fz * (t7 + t10) + fy * (t6 - t11) + fx * (t2 + t5 + t12 + t13);
    f(8, 0) = -gravVec0(1) + fx * (t6 + t11) - fz * (t8 - t9) - fy * (t2 + t4 + t12 + t14);
    f(9, 0) = -gravVec0(2) + fy * (t8 + t9) + fx * (t7 - t10) - fz * (t2 + t3 + t13 + t14);
}

// Continuous F Function
void stateEstimator::get_Phi(Matrix<Ns> &xhat, Matrix<Ninput> &uk, float delt, Matrix<Ns, Ns> &Phi)
{
    float q1 = xhat(0);
    float q2 = xhat(1);
    float q3 = xhat(2);
    float q4 = xhat(3);
    float N = xhat(4);
    float E = xhat(5);
    float D = xhat(6);
    float vN = xhat(7);
    float vE = xhat(8);
    float vD = xhat(9);
    float mag_bias_x = xhat(10);
    float mag_bias_y = xhat(11);
    float mag_bias_z = xhat(12);

    float p = uk(0);
    float q = uk(1);
    float r = uk(2);
    float fx = uk(3);
    float fy = uk(4);
    float fz = uk(5);
    Phi.Fill(0.0);
    float t2 = fx * q1 * 2.0;
    float t3 = fx * q2 * 2.0;
    float t4 = fx * q3 * 2.0;
    float t5 = fx * q4 * 2.0;
    float t6 = fy * q1 * 2.0;
    float t7 = fy * q2 * 2.0;
    float t8 = fy * q3 * 2.0;
    float t9 = fy * q4 * 2.0;
    float t10 = fz * q1 * 2.0;
    float t11 = fz * q2 * 2.0;
    float t12 = fz * q3 * 2.0;
    float t13 = fz * q4 * 2.0;
    float t17 = (delt * p) / 2.0;
    float t18 = (delt * q) / 2.0;
    float t19 = (delt * r) / 2.0;
    float t14 = -t3;
    float t15 = -t8;
    float t16 = -t10;
    float t20 = -t17;
    float t21 = -t18;
    float t22 = -t19;
    float t23 = t2 + t7 + t12;
    float t24 = t6 + t13 + t14;
    float t25 = t4 + t9 + t16;
    float t26 = t5 + t11 + t15;
    float t27 = delt * t23;
    float t28 = delt * t24;
    float t29 = delt * t25;
    float t30 = delt * t26;
    Phi(0, 0) = 1.0;
    Phi(0, 1) = t19;
    Phi(0, 2) = t21;
    Phi(0, 3) = t17;
    Phi(1, 0) = t22;
    Phi(1, 1) = 1.0;
    Phi(1, 2) = t17;
    Phi(1, 3) = t18;
    Phi(2, 0) = t18;
    Phi(2, 1) = t20;
    Phi(2, 2) = 1.0;
    Phi(2, 3) = t19;
    Phi(3, 0) = t20;
    Phi(3, 1) = t21;
    Phi(3, 2) = t22;
    Phi(3, 3) = 1.0;
    Phi(4, 4) = 1.0;
    Phi(4, 7) = delt;
    Phi(5, 5) = 1.0;
    Phi(5, 8) = delt;
    Phi(6, 6) = 1.0;
    Phi(6, 9) = delt;
    Phi(7, 0) = t27;
    Phi(7, 1) = t28;
    Phi(7, 2) = -t29;
    Phi(7, 3) = t30;
    Phi(7, 7) = 1.0;
    Phi(8, 0) = -t28;
    Phi(8, 1) = t27;
    Phi(8, 2) = t30;
    Phi(8, 3) = t29;
    Phi(8, 8) = 1.0;
    Phi(9, 0) = t29;
    Phi(9, 1) = -t30;
    Phi(9, 2) = t27;
    Phi(9, 3) = t28;
    Phi(9, 9) = 1.0;
    Phi(10, 10) = 1.0;
    Phi(11, 11) = 1.0;
    Phi(12, 12) = 1.0;
}

void stateEstimator::get_Q(Matrix<nNoise, nNoise> &Q)
{
    float gyrR[3] = {0.0189845388442364, 0.020660226476864607, 0.02769334420437668};
    float accR[3] = {0.06622349896195277, 0.08050395576102345, 0.053307049839142584};
    Q.Fill(0.0);
    Q(0, 0) = gyrR[0] * gyrR[0];
    Q(1, 1) = gyrR[1] * gyrR[1];
    Q(2, 2) = gyrR[2] * gyrR[2];
    Q(3, 3) = accR[0] * accR[0];
    Q(4, 4) = accR[1] * accR[1];
    Q(5, 5) = accR[2] * accR[2];
}

void stateEstimator::get_R(Matrix<Nm, Nm> &R)
{
    float magR[3] = {0.7356117692017315, 0.6273443875505387, 0.7582585400442549};
    float GPS_posR[3] = {1, 1, 5};
    float baro_altR = 0.1;
    float GPS_velR[3] = {0.05, 0.05, 0.5};

    R.Fill(0.0);
    R(0, 0) = magR[0] * magR[0];
    R(1, 1) = magR[1] * magR[1];
    R(2, 2) = magR[2] * magR[2];
    R(3, 3) = GPS_posR[0] * GPS_posR[0];
    R(4, 4) = GPS_posR[1] * GPS_posR[1];
    R(5, 5) = GPS_posR[2] * GPS_posR[2];
    R(6, 6) = baro_altR * baro_altR;
    R(7, 7) = GPS_velR[0] * GPS_velR[0];
    R(8, 8) = GPS_velR[1] * GPS_velR[1];
    R(9, 9) = GPS_velR[2] * GPS_velR[2];
}

void stateEstimator::get_H_jac(Matrix<Ns> &xhat, Matrix<Nm, Ns> &H_jac)
{
    float q1 = xhat(0);
    float q2 = xhat(1);
    float q3 = xhat(2);
    float q4 = xhat(3);
    float N = xhat(4);
    float E = xhat(5);
    float D = xhat(6);
    float vN = xhat(7);
    float vE = xhat(8);
    float vD = xhat(9);
    float mag_bias_x = xhat(10);
    float mag_bias_y = xhat(11);
    float mag_bias_z = xhat(12);

    H_jac.Fill(0.0);
    float t2 = magVec0(0) * q1 * 2.0;
    float t3 = magVec0(0) * q2 * 2.0;
    float t4 = magVec0(1) * q1 * 2.0;
    float t5 = magVec0(0) * q3 * 2.0;
    float t6 = magVec0(1) * q2 * 2.0;
    float t7 = magVec0(2) * q1 * 2.0;
    float t8 = magVec0(0) * q4 * 2.0;
    float t9 = magVec0(1) * q3 * 2.0;
    float t10 = magVec0(2) * q2 * 2.0;
    float t11 = magVec0(1) * q4 * 2.0;
    float t12 = magVec0(2) * q3 * 2.0;
    float t13 = magVec0(2) * q4 * 2.0;
    float t14 = -t4;
    float t15 = -t5;
    float t16 = -t10;
    float t17 = t2 + t6 + t12;
    float t18 = t3 + t13 + t14;
    float t19 = t7 + t11 + t15;
    float t20 = t8 + t9 + t16;
    H_jac(0, 0) = t17;
    H_jac(0, 1) = -t3 + t4 - t13;
    H_jac(0, 2) = t19;
    H_jac(0, 3) = t20;
    H_jac(0, 10) = -1.0;
    H_jac(1, 0) = t18;
    H_jac(1, 1) = t17;
    H_jac(1, 2) = -t8 - t9 + t10;
    H_jac(1, 3) = t19;
    H_jac(1, 11) = -1.0;
    H_jac(2, 0) = t5 - t7 - t11;
    H_jac(2, 1) = t20;
    H_jac(2, 2) = t17;
    H_jac(2, 3) = t18;
    H_jac(2, 12) = -1.0;
    H_jac(3, 4) = 1.0;
    H_jac(4, 5) = 1.0;
    H_jac(5, 6) = 1.0;
    H_jac(6, 6) = 1.0;
    H_jac(7, 7) = 1.0;
    H_jac(8, 8) = 1.0;
    H_jac(9, 9) = 1.0;
}

void stateEstimator::get_G_jac(Matrix<Ns> &xhat, Matrix<Ns, nNoise> &G_jac)
{
    float q1 = xhat(0);
    float q2 = xhat(1);
    float q3 = xhat(2);
    float q4 = xhat(3);
    float N = xhat(4);
    float E = xhat(5);
    float D = xhat(6);
    float u = xhat(7);
    float v = xhat(8);
    float w = xhat(9);
    float ax = xhat(10);
    float ay = xhat(11);
    float az = xhat(12);

    G_jac.Fill(0.0);
    float t2 = q1 * q1;
    float t3 = q2 * q2;
    float t4 = q3 * q3;
    float t5 = q4 * q4;
    float t6 = q1 * q2 * 2.0;
    float t7 = q1 * q3 * 2.0;
    float t8 = q1 * q4 * 2.0;
    float t9 = q2 * q3 * 2.0;
    float t10 = q2 * q4 * 2.0;
    float t11 = q3 * q4 * 2.0;
    float t12 = q1 / 2.0;
    float t13 = q2 / 2.0;
    float t14 = q3 / 2.0;
    float t15 = q4 / 2.0;
    float t16 = -t2;
    float t17 = -t3;
    float t18 = -t4;
    float t19 = -t12;
    float t20 = -t13;
    float t21 = -t14;
    G_jac(0, 0) = t15;
    G_jac(0, 1) = t21;
    G_jac(0, 2) = t13;
    G_jac(1, 0) = t14;
    G_jac(1, 1) = t15;
    G_jac(1, 2) = t19;
    G_jac(2, 0) = t20;
    G_jac(2, 1) = t12;
    G_jac(2, 2) = t15;
    G_jac(3, 0) = t19;
    G_jac(3, 1) = t20;
    G_jac(3, 2) = t21;
    G_jac(7, 3) = t2 + t5 + t17 + t18;
    G_jac(7, 4) = t6 - t11;
    G_jac(7, 5) = t7 + t10;
    G_jac(8, 3) = t6 + t11;
    G_jac(8, 4) = t3 + t5 + t16 + t18;
    G_jac(8, 5) = -t8 + t9;
    G_jac(9, 3) = t7 - t10;
    G_jac(9, 4) = t8 + t9;
    G_jac(9, 5) = t4 + t5 + t16 + t17;
    G_jac(10, 6) = 1.0;
    G_jac(11, 7) = 1.0;
    G_jac(12, 8) = 1.0;
}

void stateEstimator::h_fcn(Matrix<Ns> &xhat, Matrix<Nm> &h)
{
    float q1 = xhat(0);
    float q2 = xhat(1);
    float q3 = xhat(2);
    float q4 = xhat(3);
    float N = xhat(4);
    float E = xhat(5);
    float D = xhat(6);
    float vN = xhat(7);
    float vE = xhat(8);
    float vD = xhat(9);
    float mag_bias_x = xhat(10);
    float mag_bias_y = xhat(11);
    float mag_bias_z = xhat(12);

    h.Fill(0.0);
    float t2 = q1 * q1;
    float t3 = q2 * q2;
    float t4 = q3 * q3;
    float t5 = q4 * q4;
    float t6 = q1 * q2 * 2.0;
    float t7 = q1 * q3 * 2.0;
    float t8 = q1 * q4 * 2.0;
    float t9 = q2 * q3 * 2.0;
    float t10 = q2 * q4 * 2.0;
    float t11 = q3 * q4 * 2.0;
    float t12 = -t3;
    float t13 = -t4;
    float t14 = -t5;
    h(0, 0) = -mag_bias_x + magVec0(1) * (t6 + t11) + magVec0(2) * (t7 - t10) + magVec0(0) * (t2 + t5 + t12 + t13);
    h(1, 0) = -mag_bias_y + magVec0(2) * (t8 + t9) + magVec0(0) * (t6 - t11) - magVec0(1) * (t2 + t4 + t12 + t14);
    h(2, 0) = -mag_bias_z + magVec0(0) * (t7 + t10) - magVec0(1) * (t8 - t9) - magVec0(2) * (t2 + t3 + t13 + t14);
    h(3, 0) = N;
    h(4, 0) = E;
    h(5, 0) = D;
    h(6, 0) = D;
    h(7, 0) = vN;
    h(8, 0) = vE;
    h(9, 0) = vD;
}

// Predict State
void stateEstimator::predictState(float delt, Matrix<Ns> &xhat, Matrix<Ninput> &uk)
{
    Matrix<Ns> f;
    f_Fcn(xhat, uk, f);

    for (int i = 0; i < Ns; i++)
    {
        xhat(i) = xhat(i) + delt * f(i);
    }
}

void stateEstimator::timeUpdate(float delt, Matrix<Ninput> &Z_input)
{
    // F
    Matrix<Ns, Ns> Phi;
    get_Phi(xhat, Z_input, delt, Phi);

    // Q
    Matrix<nNoise, nNoise> Q;
    get_Q(Q);

    // G
    Matrix<Ns, nNoise> G;
    get_G_jac(xhat, G);

    // I
    Matrix<Ns, Ns> deltI;
    deltI.Fill(0.0);
    float delt2 = delt * delt;
    for (int i = 0; i < Ns; i++)
    {
        deltI(i, i) = delt2;
    }

    P = Phi * P * (~Phi) + G * Q * (~G) * deltI;

    // Predict State
    predictState(delt, xhat, Z_input); // xhatkp1_p

    // Normalize Quaternion
    auto quat = xhat.Submatrix<4, 1>(0, 0);
    float quatMag = sqrt(quat(0) * quat(0) + quat(1) * quat(1) + quat(2) * quat(2) + quat(3) * quat(3));
    for (int i = 0; i < quat.Rows; i++)
    {
        quat(i) = quat(i) / quatMag;
    }
}

void stateEstimator::measurementUpdate(Matrix<Nm> &Z)
{

    // Kalman Gain

    // H
    Matrix<Nm, Ns> H_jac;
    get_H_jac(xhat, H_jac);

    // R
    Matrix<Nm, Nm> R;
    get_R(R);

    Matrix<Nm, Nm> invDenom = H_jac * P * (~H_jac) + R;

    Invert(invDenom);

    Matrix<Ns, Nm> K = P * (~H_jac) * invDenom;

    // h
    Matrix<Nm> h;
    h_fcn(xhat, h);

    // residual
    Matrix<Nm> res = Z - h;

    // Update Step
    xhat = xhat + K * res; // xhatkp1_u

    // Normalize Quaternion
    auto quat = xhat.Submatrix<4, 1>(0, 0);
    float quatMag = sqrt(quat(0) * quat(0) + quat(1) * quat(1) + quat(2) * quat(2) + quat(3) * quat(3));
    for (int i = 0; i < quat.Rows; i++)
    {
        quat(i) = quat(i) / quatMag;
    }

    Matrix<Ns, Ns> Is;
    Is.Fill(0.0);
    for (int i = 0; i < Ns; i++)
    {
        Is(i, i) = 1.0;
    }

    Matrix<Ns, Ns> ImKH = (Is - K * H_jac);
    P = ImKH * P * (~ImKH) + K * R * (~K);

    
}

// --- estimateState --- //
void stateEstimator::step(float &delt, float *z_input_arr, float *z_arr)
{
    // Get Measurement vector
    Matrix<Nm> Z;
    Matrix<Ninput> Z_input;
    array2BLAMatrix(Z_input, &z_input_arr[0]);
    array2BLAMatrix(Z, &z_arr[0]);

    // DEBUG
    // Z_input(0) = -0.0024; Z_input(1) = -0.0525; Z_input(2) = 0.0949;
    // Z_input(3) = 2.7752; Z_input(4) = -1.5171; Z_input(5) = -9.3514;
    // Z(0) = 22.7761; Z(1) = 18.2120; Z(2) = 47.8942;
    // Z(3) = -0.8284; Z(4) = 0.5358; Z(5) = 0.5473;
    // Z(6) = -0.1122; Z(7) = 0.0023; Z(8) = 0.9381; Z(9) = 0.3191;
    // delt = 1;

    // --- Time Update --- //
    timeUpdate(delt, Z_input);

    // --- Measurement Update --- //
    measurementUpdate(Z);

    // auto temp = xhat;
    // for (int rw = 0; rw < temp.Rows; rw++){
    //     for (int cl = 0; cl < temp.Cols; cl++){
    //         Serial.print(temp(rw,cl),8);
    //         Serial.print(", ");
    //     }
    //     Serial.println("");
    // }
    // Serial.println("");

    Matrix<3> eulerAngles;
    quat2euler(xhat, eulerAngles);
    for (int i = 0; i < eulerAngles.Rows; i++)
    {
        eulerAngles(i) = eulerAngles(i) * 180 / M_PI;
    }
    // Serial << eulerAngles << endl;

    // Serial << xhat << endl;

    // Convert Outputs
    BLAMatrix2array(&stateEstimator_struct.xhat[0], xhat);
    BLAMatrix2arrayDiag(&stateEstimator_struct.P[0], P);
}