//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  LatLonAlt2NED_Fcn.h
//
//  Code generation for function 'LatLonAlt2NED_Fcn'
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
#include "LatLonAlt2NED_Fcn_types.h"

// Function Declarations
CODEGEN_EXPORT_SYM void LatLonAlt2NED_Fcn(const emlrtStack *sp, real_T Lat,
  real_T Lon, real_T Alt, const real_T in4[3], const real_T in5[9], real_T
  r_NED[3]);

// End of code generation (LatLonAlt2NED_Fcn.h)
