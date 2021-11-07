#include <estimateState.h>

stateEstimator::stateEstimator(StateEstimatorStruct &_stateEstimator_struct) : stateEstimator_struct(_stateEstimator_struct)
{
}

void stateEstimator::debug()
{
}

void stateEstimator::init()
{
    // State and Covariance
    xhat = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    P.Fill(0.0);
    P(0, 0) = .01 * .01;
    P(1, 1) = .01 * .01;
    P(2, 2) = .01 * .01;
    P(3, 3) = .01 * .01;
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
    float u = xhat(7);
    float v = xhat(8);
    float w = xhat(9);
    float ax = xhat(10);
    float ay = xhat(11);
    float az = xhat(12);

    float p = uk(0);
    float q = uk(1);
    float r = uk(2);

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
    f(4, 0) = u * (t2 + t5 + t12 + t13) + w * (t7 + t10) + v * (t6 - t11);
    f(5, 0) = -v * (t2 + t4 + t12 + t14) + u * (t6 + t11) - w * (t8 - t9);
    f(6, 0) = -w * (t2 + t3 + t13 + t14) + v * (t8 + t9) + u * (t7 - t10);
    f(7, 0) = ax;
    f(8, 0) = ay;
    f(9, 0) = az;
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
    float u = xhat(7);
    float v = xhat(8);
    float w = xhat(9);
    float ax = xhat(10);
    float ay = xhat(11);
    float az = xhat(12);

    float p = uk(0);
    float q = uk(1);
    float r = uk(2);
    Phi.Fill(0.0);

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
    float t12 = q1 * u * 2.0;
    float t13 = q2 * u * 2.0;
    float t14 = q3 * u * 2.0;
    float t15 = q4 * u * 2.0;
    float t16 = q1 * v * 2.0;
    float t17 = q2 * v * 2.0;
    float t18 = q3 * v * 2.0;
    float t19 = q4 * v * 2.0;
    float t20 = q1 * w * 2.0;
    float t21 = q2 * w * 2.0;
    float t22 = q3 * w * 2.0;
    float t23 = q4 * w * 2.0;
    float t30 = (delt * p) / 2.0;
    float t31 = (delt * q) / 2.0;
    float t32 = (delt * r) / 2.0;
    float t24 = -t13;
    float t25 = -t18;
    float t26 = -t20;
    float t27 = -t3;
    float t28 = -t4;
    float t29 = -t5;
    float t33 = -t30;
    float t34 = -t31;
    float t35 = -t32;
    float t36 = t12 + t17 + t22;
    float t37 = t16 + t23 + t24;
    float t38 = t14 + t19 + t26;
    float t39 = t15 + t21 + t25;
    float t40 = delt * t36;
    float t41 = delt * t37;
    float t42 = delt * t38;
    float t43 = delt * t39;
    Phi(0, 0) = 1.0;
    Phi(0, 1) = t32;
    Phi(0, 2) = t34;
    Phi(0, 3) = t30;
    Phi(1, 0) = t35;
    Phi(1, 1) = 1.0;
    Phi(1, 2) = t30;
    Phi(1, 3) = t31;
    Phi(2, 0) = t31;
    Phi(2, 1) = t33;
    Phi(2, 2) = 1.0;
    Phi(2, 3) = t32;
    Phi(3, 0) = t33;
    Phi(3, 1) = t34;
    Phi(3, 2) = t35;
    Phi(3, 3) = 1.0;
    Phi(4, 0) = t40;
    Phi(4, 1) = t41;
    Phi(4, 2) = -t42;
    Phi(4, 3) = t43;
    Phi(4, 4) = 1.0;
    Phi(4, 7) = delt * (t2 + t5 + t27 + t28);
    Phi(4, 8) = delt * (t6 - t11);
    Phi(4, 9) = delt * (t7 + t10);
    Phi(5, 0) = -t41;
    Phi(5, 1) = t40;
    Phi(5, 2) = t43;
    Phi(5, 3) = t42;
    Phi(5, 5) = 1.0;
    Phi(5, 7) = delt * (t6 + t11);
    Phi(5, 8) = -delt * (t2 + t4 + t27 + t29);
    Phi(5, 9) = -delt * (t8 - t9);
    Phi(6, 0) = t42;
    Phi(6, 1) = -t43;
    Phi(6, 2) = t40;
    Phi(6, 3) = t41;
    Phi(6, 6) = 1.0;
    Phi(6, 7) = delt * (t7 - t10);
    Phi(6, 8) = delt * (t8 + t9);
    Phi(6, 9) = -delt * (t2 + t3 + t28 + t29);
    Phi(7, 7) = 1.0;
    Phi(7, 10) = delt;
    Phi(8, 8) = 1.0;
    Phi(8, 11) = delt;
    Phi(9, 9) = 1.0;
    Phi(9, 12) = delt;
    Phi(10, 10) = 1.0;
    Phi(11, 11) = 1.0;
    Phi(12, 12) = 1.0;
}

void stateEstimator::get_Q(Matrix<Ninput, Ninput> &Q)
{
    float gyrR[3] = {0.0189845388442364, 0.020660226476864607, 0.02769334420437668};
    Q.Fill(0.0);
    Q(0, 0) = gyrR[0] * gyrR[0];
    Q(1, 1) = gyrR[1] * gyrR[1];
    Q(2, 2) = gyrR[2] * gyrR[2];
}

void stateEstimator::get_R(Matrix<Nm, Nm> &R)
{
    float magR[3] = {0.7356117692017315, 0.6273443875505387, 0.7582585400442549};
    float accR[3] = {0.1, 0.1, 0.1};
    R.Fill(0.0);
    R(0, 0) = magR[0] * magR[0];
    R(1, 1) = magR[1] * magR[1];
    R(2, 2) = magR[2] * magR[2];
    R(3, 3) = accR[0] * accR[0];
    R(4, 4) = accR[1] * accR[1];
    R(5, 5) = accR[2] * accR[2];
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
    float u = xhat(7);
    float v = xhat(8);
    float w = xhat(9);
    float ax = xhat(10);
    float ay = xhat(11);
    float az = xhat(12);

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
    float t17 = q1 * (9.8E+1 / 5.0);
    float t18 = q2 * (9.8E+1 / 5.0);
    float t19 = q3 * (9.8E+1 / 5.0);
    float t20 = q4 * (9.8E+1 / 5.0);
    float t14 = -t4;
    float t15 = -t5;
    float t16 = -t10;
    float t21 = -t17;
    float t22 = -t19;
    float t23 = -t20;
    float t24 = t2 + t6 + t12;
    float t25 = t3 + t13 + t14;
    float t26 = t7 + t11 + t15;
    float t27 = t8 + t9 + t16;
    H_jac(0, 0) = t24;
    H_jac(0, 1) = -t3 + t4 - t13;
    H_jac(0, 2) = t26;
    H_jac(0, 3) = t27;
    H_jac(1, 0) = t25;
    H_jac(1, 1) = t24;
    H_jac(1, 2) = -t8 - t9 + t10;
    H_jac(1, 3) = t26;
    H_jac(2, 0) = t5 - t7 - t11;
    H_jac(2, 1) = t27;
    H_jac(2, 2) = t24;
    H_jac(2, 3) = t25;
    H_jac(3, 0) = t22;
    H_jac(3, 1) = t20;
    H_jac(3, 2) = t21;
    H_jac(3, 3) = t18;
    H_jac(3, 10) = 1.0;
    H_jac(4, 0) = t23;
    H_jac(4, 1) = t22;
    H_jac(4, 2) = -t18;
    H_jac(4, 3) = t21;
    H_jac(4, 11) = 1.0;
    H_jac(5, 0) = t17;
    H_jac(5, 1) = t18;
    H_jac(5, 2) = t22;
    H_jac(5, 3) = t23;
    H_jac(5, 12) = 1.0;
}

void stateEstimator::get_G_jac(Matrix<Ns> &xhat, Matrix<Ns, Ninput> &G_jac)
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
    float t2 = q1 / 2.0;
    float t3 = q2 / 2.0;
    float t4 = q3 / 2.0;
    float t5 = q4 / 2.0;
    float t6 = -t2;
    float t7 = -t3;
    float t8 = -t4;
    G_jac(0, 0) = t5;
    G_jac(0, 1) = t8;
    G_jac(0, 2) = t3;
    G_jac(1, 0) = t4;
    G_jac(1, 1) = t5;
    G_jac(1, 2) = t6;
    G_jac(2, 0) = t7;
    G_jac(2, 1) = t2;
    G_jac(2, 2) = t5;
    G_jac(3, 0) = t6;
    G_jac(3, 1) = t7;
    G_jac(3, 2) = t8;
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
    float u = xhat(7);
    float v = xhat(8);
    float w = xhat(9);
    float ax = xhat(10);
    float ay = xhat(11);
    float az = xhat(12);
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
    h(0, 0) = magVec0(1) * (t6 + t11) + magVec0(2) * (t7 - t10) + magVec0(0) * (t2 + t5 + t12 + t13);
    h(1, 0) = magVec0(2) * (t8 + t9) + magVec0(0) * (t6 - t11) - magVec0(1) * (t2 + t4 + t12 + t14);
    h(2, 0) = magVec0(0) * (t7 + t10) - magVec0(1) * (t8 - t9) - magVec0(2) * (t2 + t3 + t13 + t14);
    h(3, 0) = ax - q1 * q3 * (9.8E+1 / 5.0) + q2 * q4 * (9.8E+1 / 5.0);
    h(4, 0) = ay - q1 * q4 * (9.8E+1 / 5.0) - q2 * q3 * (9.8E+1 / 5.0);
    h(5, 0) = az + t2 * (4.9E+1 / 5.0) + t3 * (4.9E+1 / 5.0) - t4 * (4.9E+1 / 5.0) - t5 * (4.9E+1 / 5.0);
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
    Matrix<Ninput, Ninput> Q;
    get_Q(Q);

    // G
    Matrix<Ns, Ninput> G;
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
    // Z_input(0) = 0; Z_input(1) = 0.1745; Z_input(2) = 0.0873;
    // Z(0) = -15.7394; Z(1) = 14.3489; Z(2) = 33.8268;
    // Z(3) = 1.7104; Z(4) = -0.0746; Z(5) = -9.7440;
    // delt = 1;

    // --- Time Update --- //
    timeUpdate(delt, Z_input);

    // --- Measurement Update --- //
    measurementUpdate(Z);

    // auto temp = P;
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