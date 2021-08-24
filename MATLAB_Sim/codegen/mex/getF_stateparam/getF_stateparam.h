//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  getF_stateparam.h
//
//  Code generation for function 'getF_stateparam'
//


#pragma once

// Include files
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "getF_stateparam_types.h"

// Function Declarations
CODEGEN_EXPORT_SYM void getF_stateparam(const emlrtStack *sp, const real_T Xk[10],
  const real_T cntrl[6], real_T delt, real_T F[100]);

// End of code generation (getF_stateparam.h)
