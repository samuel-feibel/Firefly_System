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
    xhat = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    P.Fill(0.0);
    P(0, 0) = 0.0;
    P(1, 1) = 0.0;
    P(2, 2) = 0.0;
    P(3, 3) = .1 * .1;
    P(4, 4) = .1 * .1;
    P(5, 5) = .1 * .1;
    P(6, 6) = .01 * .01;
    P(7, 7) = .01 * .01;
    P(8, 8) = .01 * .01;
    P(9, 9) = .01 * .01;
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
    float q1 = xhat(6);
    float q2 = xhat(7);
    float q3 = xhat(8);
    float q4 = xhat(9);

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
    float q1 = xhat(6);
    float q2 = xhat(7);
    float q3 = xhat(8);
    float q4 = xhat(9);
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
void stateEstimator::f_Fcn(Matrix<Ns> &xhat, Matrix<6> &uk, Matrix<Ns> &f)
{
    f.Fill(0.0);
    float u = xhat(3);
    float v = xhat(4);
    float w = xhat(5);
    float q1 = xhat(6);
    float q2 = xhat(7);
    float q3 = xhat(8);
    float q4 = xhat(9);
    float X = uk(0);
    float Y = uk(1);
    float Z = uk(2);
    float p = uk(3);
    float q = uk(4);
    float r = uk(5);

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
    f(0, 0) = u * (t2 + t5 + t12 + t13) + w * (t7 + t10) + v * (t6 - t11);
    f(1, 0) = -v * (t2 + t4 + t12 + t14) + u * (t6 + t11) - w * (t8 - t9);
    f(2, 0) = -w * (t2 + t3 + t13 + t14) + v * (t8 + t9) + u * (t7 - t10);
    f(3, 0) = X + q1 * q3 * (9.8E+1 / 5.0) - q2 * q4 * (9.8E+1 / 5.0);
    f(4, 0) = Y + q1 * q4 * (9.8E+1 / 5.0) + q2 * q3 * (9.8E+1 / 5.0);
    f(5, 0) = Z - t2 * (4.9E+1 / 5.0) - t3 * (4.9E+1 / 5.0) + t4 * (4.9E+1 / 5.0) + t5 * (4.9E+1 / 5.0);
    f(6, 0) = (p * q4) / 2.0 - (q * q3) / 2.0 + (q2 * r) / 2.0;
    f(7, 0) = (p * q3) / 2.0 + (q * q4) / 2.0 - (q1 * r) / 2.0;
    f(8, 0) = p * q2 * (-1.0 / 2.0) + (q * q1) / 2.0 + (q4 * r) / 2.0;
    f(9, 0) = p * q1 * (-1.0 / 2.0) - (q * q2) / 2.0 - (q3 * r) / 2.0;
}

// Continuous F Function
void stateEstimator::get_Phi(Matrix<Ns> &xhat, Matrix<6> &uk, float delt, Matrix<Ns, Ns> &Phi)
{
    float u = xhat(3);
    float v = xhat(4);
    float w = xhat(5);
    float q1 = xhat(6);
    float q2 = xhat(7);
    float q3 = xhat(8);
    float q4 = xhat(9);

    float p = uk(3);
    float q = uk(4);
    float r = uk(5);

    Phi.Fill(0.0);
    Phi(0, 0) = 1.0;
    Phi(0, 3) = delt * (q1 * q1 - q2 * q2 - q3 * q3 + q4 * q4);
    Phi(0, 4) = delt * (q1 * q2 * 2.0 - q3 * q4 * 2.0);
    Phi(0, 5) = delt * (q1 * q3 * 2.0 + q2 * q4 * 2.0);
    Phi(0, 6) = delt * (q1 * u * 2.0 + q2 * v * 2.0 + q3 * w * 2.0);
    Phi(0, 7) = delt * (q2 * u * -2.0 + q1 * v * 2.0 + q4 * w * 2.0);
    Phi(0, 8) = -delt * (q3 * u * 2.0 + q4 * v * 2.0 - q1 * w * 2.0);
    Phi(0, 9) = delt * (q4 * u * 2.0 - q3 * v * 2.0 + q2 * w * 2.0);
    Phi(1, 1) = 1.0;
    Phi(1, 3) = delt * (q1 * q2 * 2.0 + q3 * q4 * 2.0);
    Phi(1, 4) = -delt * (q1 * q1 - q2 * q2 + q3 * q3 - q4 * q4);
    Phi(1, 5) = -delt * (q1 * q4 * 2.0 - q2 * q3 * 2.0);
    Phi(1, 6) = -delt * (q2 * u * -2.0 + q1 * v * 2.0 + q4 * w * 2.0);
    Phi(1, 7) = delt * (q1 * u * 2.0 + q2 * v * 2.0 + q3 * w * 2.0);
    Phi(1, 8) = delt * (q4 * u * 2.0 - q3 * v * 2.0 + q2 * w * 2.0);
    Phi(1, 9) = delt * (q3 * u * 2.0 + q4 * v * 2.0 - q1 * w * 2.0);
    Phi(2, 2) = 1.0;
    Phi(2, 3) = delt * (q1 * q3 * 2.0 - q2 * q4 * 2.0);
    Phi(2, 4) = delt * (q1 * q4 * 2.0 + q2 * q3 * 2.0);
    Phi(2, 5) = -delt * (q1 * q1 + q2 * q2 - q3 * q3 - q4 * q4);
    Phi(2, 6) = delt * (q3 * u * 2.0 + q4 * v * 2.0 - q1 * w * 2.0);
    Phi(2, 7) = -delt * (q4 * u * 2.0 - q3 * v * 2.0 + q2 * w * 2.0);
    Phi(2, 8) = delt * (q1 * u * 2.0 + q2 * v * 2.0 + q3 * w * 2.0);
    Phi(2, 9) = delt * (q2 * u * -2.0 + q1 * v * 2.0 + q4 * w * 2.0);
    Phi(3, 3) = 1.0;
    Phi(3, 6) = delt * q3 * (9.8E+1 / 5.0);
    Phi(3, 7) = delt * q4 * (-9.8E+1 / 5.0);
    Phi(3, 8) = delt * q1 * (9.8E+1 / 5.0);
    Phi(3, 9) = delt * q2 * (-9.8E+1 / 5.0);
    Phi(4, 4) = 1.0;
    Phi(4, 6) = delt * q4 * (9.8E+1 / 5.0);
    Phi(4, 7) = delt * q3 * (9.8E+1 / 5.0);
    Phi(4, 8) = delt * q2 * (9.8E+1 / 5.0);
    Phi(4, 9) = delt * q1 * (9.8E+1 / 5.0);
    Phi(5, 5) = 1.0;
    Phi(5, 6) = delt * q1 * (-9.8E+1 / 5.0);
    Phi(5, 7) = delt * q2 * (-9.8E+1 / 5.0);
    Phi(5, 8) = delt * q3 * (9.8E+1 / 5.0);
    Phi(5, 9) = delt * q4 * (9.8E+1 / 5.0);
    Phi(6, 6) = 1.0;
    Phi(6, 7) = (delt * r) / 2.0;
    Phi(6, 8) = delt * q * (-1.0 / 2.0);
    Phi(6, 9) = (delt * p) / 2.0;
    Phi(7, 6) = delt * r * (-1.0 / 2.0);
    Phi(7, 7) = 1.0;
    Phi(7, 8) = (delt * p) / 2.0;
    Phi(7, 9) = (delt * q) / 2.0;
    Phi(8, 6) = (delt * q) / 2.0;
    Phi(8, 7) = delt * p * (-1.0 / 2.0);
    Phi(8, 8) = 1.0;
    Phi(8, 9) = (delt * r) / 2.0;
    Phi(9, 6) = delt * p * (-1.0 / 2.0);
    Phi(9, 7) = delt * q * (-1.0 / 2.0);
    Phi(9, 8) = delt * r * (-1.0 / 2.0);
    Phi(9, 9) = 1.0;
}

void stateEstimator::get_Q(float dT, Matrix<6, 6> &Q)
{
    Q.Fill(0.0);
    Q(0, 0) = pow(dT * 8.055656553821564E-2 + 2.236262379681608, 2.0) / 100;
    Q(1, 1) = pow(dT * 8.602270870712547E-2 + 1.313070372031577, 2.0) / 100;
    Q(2, 2) = pow(dT * 2.831314927881532E-1 + 4.820209694184105, 2.0) / 100;
    Q(3, 3) = pow(dT * 3.985940620834597E-3 - 1.126812513616809E-2, 2.0);
    Q(4, 4) = pow(dT * 3.401197824382432E-3 - 1.311015844382992E-2, 2.0);
    Q(5, 5) = pow(dT * 2.00959903402234E-3 - 1.447906471632683E-2, 2.0);
}

void stateEstimator::get_H_jac(Matrix<Ns> &xhat, Matrix<9, Ns> &H_jac)
{
    float u = xhat(3);
    float v = xhat(4);
    float w = xhat(5);
    float q1 = xhat(6);
    float q2 = xhat(7);
    float q3 = xhat(8);
    float q4 = xhat(9);

    H_jac.Fill(0.0);
    float t2 = fabs(u);
    float t3 = fabs(v);
    float t4 = fabs(w);
    float t5 = q1 * q1;
    float t6 = q2 * q2;
    float t7 = q3 * q3;
    float t8 = q4 * q4;
    float t12 = magVec0(0) * q1 * 2.0;
    float t13 = magVec0(0) * q2 * 2.0;
    float t14 = magVec0(1) * q1 * 2.0;
    float t15 = magVec0(0) * q3 * 2.0;
    float t16 = magVec0(1) * q2 * 2.0;
    float t17 = magVec0(2) * q1 * 2.0;
    float t18 = magVec0(0) * q4 * 2.0;
    float t19 = magVec0(1) * q3 * 2.0;
    float t20 = magVec0(2) * q2 * 2.0;
    float t21 = magVec0(1) * q4 * 2.0;
    float t22 = magVec0(2) * q3 * 2.0;
    float t23 = magVec0(2) * q4 * 2.0;
    float t24 = q1 * q2 * 2.0;
    float t25 = q1 * q3 * 2.0;
    float t26 = q1 * q4 * 2.0;
    float t27 = q2 * q3 * 2.0;
    float t28 = q2 * q4 * 2.0;
    float t29 = q3 * q4 * 2.0;
    float t30 = q1 * u * 2.0;
    float t31 = q2 * u * 2.0;
    float t32 = q3 * u * 2.0;
    float t33 = q4 * u * 2.0;
    float t34 = q1 * v * 2.0;
    float t35 = q2 * v * 2.0;
    float t36 = q3 * v * 2.0;
    float t37 = q4 * v * 2.0;
    float t38 = q1 * w * 2.0;
    float t39 = q2 * w * 2.0;
    float t40 = q3 * w * 2.0;
    float t41 = q4 * w * 2.0;
    float t9 = t2 * t2;
    float t10 = t3 * t3;
    float t11 = t4 * t4;
    float t42 = -t14;
    float t43 = -t15;
    float t44 = -t20;
    float t45 = -t27;
    float t46 = -t29;
    float t47 = -t31;
    float t48 = -t36;
    float t49 = -t38;
    float t50 = -t6;
    float t51 = -t7;
    float t52 = -t8;
    float t53 = t24 + t29;
    float t54 = t25 + t28;
    float t62 = t12 + t16 + t22;
    float t63 = t30 + t35 + t40;
    float t55 = t24 + t46;
    float t56 = t26 + t45;
    float t57 = t53 * u;
    float t58 = t54 * w;
    float t61 = t9 + t10 + t11;
    float t65 = t13 + t23 + t42;
    float t66 = t17 + t21 + t43;
    float t67 = t18 + t19 + t44;
    float t68 = t34 + t41 + t47;
    float t69 = t32 + t37 + t49;
    float t70 = t33 + t39 + t48;
    float t72 = t5 + t8 + t50 + t51;
    float t73 = t5 + t7 + t50 + t52;
    float t59 = t55 * v;
    float t60 = t56 * w;
    float t64 = -t57;
    float t71 = 1.0 / sqrt(t61);
    float t74 = t72 * u;
    float t75 = t73 * v;
    float t76 = t58 + t59 + t74;
    float t77 = t60 + t64 + t75;
    float t78 = t76 * t76;
    float t79 = 1.0 / t76;
    float t81 = t77 * t77;
    float t80 = 1.0 / t78;
    float t82 = t78 + t81;
    float t83 = 1.0 / t82;
    H_jac(0, 0) = 1.0;
    H_jac(1, 1) = 1.0;
    H_jac(2, 2) = 1.0;
    H_jac(3, 3) = t2 * t71 * ((u / fabs(u)));
    H_jac(3, 4) = t3 * t71 * ((v / fabs(v)));
    H_jac(3, 5) = t4 * t71 * ((w / fabs(w)));
    H_jac(4, 6) = t62;
    H_jac(4, 7) = -t13 + t14 - t23;
    H_jac(4, 8) = t66;
    H_jac(4, 9) = t67;
    H_jac(5, 6) = t65;
    H_jac(5, 7) = t62;
    H_jac(5, 8) = -t18 - t19 + t20;
    H_jac(5, 9) = t66;
    H_jac(6, 6) = t15 - t17 - t21;
    H_jac(6, 7) = t67;
    H_jac(6, 8) = t62;
    H_jac(6, 9) = t65;
    H_jac(7, 3) = t78 * t83 * (t53 * t79 + t72 * t77 * t80);
    H_jac(7, 4) = -t78 * t83 * (t73 * t79 - t55 * t77 * t80);
    H_jac(7, 5) = -t78 * t83 * (t56 * t79 - t54 * t77 * t80);
    H_jac(7, 6) = -t78 * t83 * (t68 * t79 - t63 * t77 * t80);
    H_jac(7, 7) = t78 * t83 * (t63 * t79 + t68 * t77 * t80);
    H_jac(7, 8) = t78 * t83 * (t70 * t79 - t69 * t77 * t80);
    H_jac(7, 9) = t78 * t83 * (t69 * t79 + t70 * t77 * t80);
    H_jac(8, 2) = 1.0;
}

void stateEstimator::get_G_jac(Matrix<Ns> &xhat, Matrix<Ns, 6> &G_jac)
{
    float q1 = xhat(6);
    float q2 = xhat(7);
    float q3 = xhat(8);
    float q4 = xhat(9);
    G_jac.Fill(0.0);
    G_jac(3, 0) = 1.0;
    G_jac(4, 1) = 1.0;
    G_jac(5, 2) = 1.0;
    G_jac(6, 3) = q4 / 2.0;
    G_jac(6, 4) = q3 * (-1.0 / 2.0);
    G_jac(6, 5) = q2 / 2.0;
    G_jac(7, 3) = q3 / 2.0;
    G_jac(7, 4) = q4 / 2.0;
    G_jac(7, 5) = q1 * (-1.0 / 2.0);
    G_jac(8, 3) = q2 * (-1.0 / 2.0);
    G_jac(8, 4) = q1 / 2.0;
    G_jac(8, 5) = q4 / 2.0;
    G_jac(9, 3) = q1 * (-1.0 / 2.0);
    G_jac(9, 4) = q2 * (-1.0 / 2.0);
    G_jac(9, 5) = q3 * (-1.0 / 2.0);
}

void stateEstimator::get_R(float dT, Matrix<9, 9> &R)
{
    R.Fill(0.0);
    R(0, 0) = 1; //2.5E+1 / 2.0;
    R(1, 1) = 1; //2.5E+1 / 2.0;
    R(2, 2) = 1.0E+2;
    R(3, 3) = 1E-2;
    R(4, 4) = 100;           //pow(dT * 4.698552240547276E-3 + 6.495281709453083E-1, 2.0);
    R(5, 5) = 100;           //pow(dT * 1.373789489995686E-3 + 7.878470583458638E-1, 2.0);
    R(6, 6) = 100;           //pow(dT * 2.990748419728659E-3 + 6.606739589323193E-1, 2.0);
    R(7, 7) = (M_PI * M_PI); // / 3.6E+3;
    R(8, 8) = 4.0E-4;
}

void stateEstimator::h_fcn(Matrix<Ns> &xhat, Matrix<Nm> &h)
{
    h(0, 0) = xhat(0);
    h(1, 0) = xhat(1);
    h(2, 0) = xhat(2);
    auto velVec = xhat.Submatrix<3, 1>(3, 1);
    h(3, 0) = norm3(velVec);
    Matrix<3, 3> I_C_B;
    get_I_C_B(xhat, I_C_B);
    h.Submatrix<3, 1>(4, 1) = (~I_C_B) * magVec0;
    Matrix<3, 1> v_I = I_C_B * velVec;
    h(7, 0) = atan2(v_I(2), v_I(1));
    h(8, 0) = xhat(2);
}

// Predict State
void stateEstimator::predictState(float delt, Matrix<Ns> &xhat, Matrix<6> &uk)
{
    Matrix<Ns> f;
    f_Fcn(xhat, uk, f);

    for (int i = 0; i < Ns; i++)
    {
        xhat(i) = xhat(i) + delt * f(i);
    }
}

void stateEstimator::timeUpdate(float delt, Matrix<6> &Z_input)
{


    // Predict State
    predictState(delt, xhat, Z_input); // xhatkp1_p

    // Normalize Quaternion
    auto quat = xhat.Submatrix<4, 1>(6, 0);
    float quatMag = sqrt(quat(0) * quat(0) + quat(1) * quat(1) + quat(2) * quat(2) + quat(3) * quat(3));
    for (int i = 0; i < quat.Rows; i++)
    {
        quat(i) = quat(i) / quatMag;
    }

    // // DEBUG
    // quat(0) = 0;
    // quat(1) = 0;
    // quat(2) = 0;
    // quat(3) = 1;
    // Predict Covariance

    // F
    Matrix<Ns, Ns> Phi;
    get_Phi(xhat, Z_input, delt, Phi);

    // Q
    Matrix<6, 6> Q;
    get_Q(90.0, Q);

    // G
    Matrix<Ns, 6> G;
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
}

void stateEstimator::measurementUpdate(Matrix<9> &Z)
{

    // Kalman Gain

    // H
    Matrix<9, Ns> H_jac;
    get_H_jac(xhat, H_jac);

    // R
    Matrix<9, 9> R;
    get_R(90, R);

    Matrix<Nm, Nm> invDenom = H_jac * P * (~H_jac) + R;

    Invert(invDenom);

    Matrix<Ns, Nm> K = P * (~H_jac) * invDenom;

    // h
    Matrix<Nm> h;
    h_fcn(xhat, h);

    // residual
    Matrix<Nm> res = Z - h;
    float res_heading = res(8);
    setAngle2Range(res_heading);
    res(8) = res_heading;


    // DEBUG
    // auto subK_ref = K.Submatrix<4, 3>(1, 4);
    // Matrix<4,3> subK = subK_ref;
    // Serial << subK << endl;
    // K.Fill(0.0);
    // K.Submatrix<4, 3>(1, 4) = subK;

    // Update Step
    xhat = xhat + K * res; // xhatkp1_u

    // Debug Check for NaN
    /*
  auto debugVar = xhat;
  Serial << debugVar << endl;
  for (int i = 0; i < debugVar.Rows; i++ )
  {
    for (int j = 0; j < debugVar.Cols; j++)
    {
      if (isnan(debugVar(i, j)))
      {
        Serial << debugVar << endl;
        delay(1000);
      }
    }
  }
  */

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
    Z(0) = 0.0; Z(1) = 0.0; Z(2) = 0.0;
    Z(3) = 0.0;

    // Z_input(0) = 0.0001;
    // Z_input(1) = 0.0001;
    // Z_input(2) = -9.8101;

    // --- Time Update --- //
    timeUpdate(delt, Z_input);


    // --- Measurement Update --- //
    measurementUpdate(Z);


    // Matrix<3> eulerAngles;
    // quat2euler(xhat,eulerAngles);
    // for (int i=0; i < eulerAngles.Rows; i++){eulerAngles(i) = eulerAngles(i) * 180/M_PI;}
    // Serial << eulerAngles << endl;

    // Convert Outputs
    BLAMatrix2array(&stateEstimator_struct.xhat[0], xhat);
    BLAMatrix2arrayDiag(&stateEstimator_struct.P[0], P);
}