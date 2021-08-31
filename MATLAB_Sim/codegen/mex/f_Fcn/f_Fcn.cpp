//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  f_Fcn.cpp
//
//  Code generation for function 'f_Fcn'
//


// Include files
#include "f_Fcn.h"
#include "rt_nonfinite.h"

// Function Definitions
void f_Fcn(const emlrtStack *, real_T, const real_T in2[10], const real_T in3[6],
           real_T f[10])
{
  real_T t2;
  real_T t3;
  real_T t4;
  real_T t5;
  real_T t6;
  real_T t7_tmp;
  real_T t7;
  real_T t8_tmp;
  real_T t8;
  real_T t9_tmp;
  real_T t9;
  real_T t10_tmp;
  real_T t10;
  real_T t11;

  // F_FCN
  //     F = F_FCN(T,IN2,IN3)
  //     This function was generated by the Symbolic Math Toolbox version 8.5.
  //     16-Aug-2021 15:17:55
  t2 = in2[6] * in2[6];
  t3 = in2[7] * in2[7];
  t4 = in2[8] * in2[8];
  t5 = in2[9] * in2[9];
  t6 = in2[6] * in2[7] * 2.0;
  t7_tmp = in2[6] * in2[8];
  t7 = t7_tmp * 2.0;
  t8_tmp = in2[6] * in2[9];
  t8 = t8_tmp * 2.0;
  t9_tmp = in2[7] * in2[8];
  t9 = t9_tmp * 2.0;
  t10_tmp = in2[7] * in2[9];
  t10 = t10_tmp * 2.0;
  t11 = in2[8] * in2[9] * 2.0;
  f[0] = (in2[3] * (((t2 + t5) + -t3) + -t4) + in2[5] * (t7 + t10)) + in2[4] *
    (t6 - t11);
  f[1] = (-in2[4] * (((t2 + t4) + -t3) + -t5) + in2[3] * (t6 + t11)) - in2[5] *
    (t8 - t9);
  f[2] = (-in2[5] * (((t2 + t3) + -t4) + -t5) + in2[4] * (t8 + t9)) + in2[3] *
    (t7 - t10);
  f[3] = (in3[0] + t7_tmp * 19.6) - t10_tmp * 19.6;
  f[4] = (in3[1] + t8_tmp * 19.6) + t9_tmp * 19.6;
  f[5] = (((in3[2] - t2 * 9.8) - t3 * 9.8) + t4 * 9.8) + t5 * 9.8;
  f[6] = (in3[3] * in2[9] / 2.0 - in3[4] * in2[8] / 2.0) + in2[7] * in3[5] / 2.0;
  f[7] = (in3[3] * in2[8] / 2.0 + in3[4] * in2[9] / 2.0) - in2[6] * in3[5] / 2.0;
  f[8] = (in3[3] * in2[7] * -0.5 + in3[4] * in2[6] / 2.0) + in2[9] * in3[5] /
    2.0;
  f[9] = (in3[3] * in2[6] * -0.5 - in3[4] * in2[7] / 2.0) - in2[8] * in3[5] /
    2.0;
}

// End of code generation (f_Fcn.cpp)