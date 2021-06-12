//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  TECEF2NED_Fcn.h
//
//  Code generation for function 'TECEF2NED_Fcn'
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
#include "TECEF2NED_Fcn_types.h"

// Function Declarations
CODEGEN_EXPORT_SYM void TECEF2NED_Fcn(const emlrtStack *sp, const real_T in1[3],
  real_T NED_C_ECEF[9]);

// End of code generation (TECEF2NED_Fcn.h)
