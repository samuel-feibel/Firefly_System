//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  F_jac_Fcn.cpp
//
//  Code generation for function 'F_jac_Fcn'
//


// Include files
#include "F_jac_Fcn.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
void F_jac_Fcn(const emlrtStack *, const real_T in1[10], const real_T in2[6],
               real_T F[100])
{
  real_T t2;
  real_T t3;
  real_T t4;
  real_T t5;
  real_T t6;
  real_T t7;
  real_T t8;
  real_T t9;
  real_T t10;
  real_T t11;
  real_T t13;
  real_T t14;
  real_T t15;
  real_T t16;
  real_T t18;
  real_T t19;
  real_T t20;
  real_T t21;
  real_T t23;
  real_T t27;
  real_T t28;
  real_T t29;
  real_T t36;
  real_T t37;
  real_T t38;
  real_T t39;
  real_T t41;
  real_T t42;
  real_T t43;
  real_T t44;

  // F_JAC_FCN
  //     F = F_JAC_FCN(IN1,IN2)
  //     This function was generated by the Symbolic Math Toolbox version 8.5.
  //     23-Jul-2021 11:41:29
  t2 = in1[6] * in1[6];
  t3 = in1[7] * in1[7];
  t4 = in1[8] * in1[8];
  t5 = in1[9] * in1[9];
  t6 = in1[6] * in1[7] * 2.0;
  t7 = in1[6] * in1[8] * 2.0;
  t8 = in1[6] * in1[9] * 2.0;
  t9 = in1[7] * in1[8] * 2.0;
  t10 = in1[7] * in1[9] * 2.0;
  t11 = in1[8] * in1[9] * 2.0;
  t13 = in1[7] * in1[3] * 2.0;
  t14 = in1[8] * in1[3] * 2.0;
  t15 = in1[9] * in1[3] * 2.0;
  t16 = in1[6] * in1[4] * 2.0;
  t18 = in1[8] * in1[4] * 2.0;
  t19 = in1[9] * in1[4] * 2.0;
  t20 = in1[6] * in1[5] * 2.0;
  t21 = in1[7] * in1[5] * 2.0;
  t23 = in1[9] * in1[5] * 2.0;
  t27 = in2[3] / 2.0;
  t28 = in2[4] / 2.0;
  t29 = in2[5] / 2.0;
  t36 = in1[6] * 19.6;
  t37 = in1[7] * 19.6;
  t38 = in1[8] * 19.6;
  t39 = in1[9] * 19.6;
  t41 = (in1[6] * in1[3] * 2.0 + in1[7] * in1[4] * 2.0) + in1[8] * in1[5] * 2.0;
  t42 = (t16 + t23) + -t13;
  t43 = (t14 + t19) + -t20;
  t44 = (t15 + t21) + -t18;
  memset(&F[0], 0, 30U * sizeof(real_T));
  F[30] = ((t2 + t5) + -t3) + -t4;
  F[31] = t6 + t11;
  F[32] = t7 - t10;
  F[33] = 0.0;
  F[34] = 0.0;
  F[35] = 0.0;
  F[36] = 0.0;
  F[37] = 0.0;
  F[38] = 0.0;
  F[39] = 0.0;
  F[40] = t6 - t11;
  F[41] = ((t3 + t5) + -t2) + -t4;
  F[42] = t8 + t9;
  F[43] = 0.0;
  F[44] = 0.0;
  F[45] = 0.0;
  F[46] = 0.0;
  F[47] = 0.0;
  F[48] = 0.0;
  F[49] = 0.0;
  F[50] = t7 + t10;
  F[51] = -t8 + t9;
  F[52] = ((t4 + t5) + -t2) + -t3;
  F[53] = 0.0;
  F[54] = 0.0;
  F[55] = 0.0;
  F[56] = 0.0;
  F[57] = 0.0;
  F[58] = 0.0;
  F[59] = 0.0;
  F[60] = t41;
  F[61] = (t13 - t16) - t23;
  F[62] = t43;
  F[63] = t38;
  F[64] = t39;
  F[65] = -t36;
  F[66] = 0.0;
  F[67] = -t29;
  F[68] = t28;
  F[69] = -t27;
  F[70] = t42;
  F[71] = t41;
  F[72] = (-t15 + t18) - t21;
  F[73] = -t39;
  F[74] = t38;
  F[75] = -t37;
  F[76] = t29;
  F[77] = 0.0;
  F[78] = -t27;
  F[79] = -t28;
  F[80] = (-t14 - t19) + t20;
  F[81] = t44;
  F[82] = t41;
  F[83] = t36;
  F[84] = t37;
  F[85] = t38;
  F[86] = -t28;
  F[87] = t27;
  F[88] = 0.0;
  F[89] = -t29;
  F[90] = t44;
  F[91] = t43;
  F[92] = t42;
  F[93] = -t37;
  F[94] = t36;
  F[95] = t39;
  F[96] = t27;
  F[97] = t28;
  F[98] = t29;
  F[99] = 0.0;
}

// End of code generation (F_jac_Fcn.cpp)
