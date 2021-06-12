//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  LatLonAlt2ECEF_Fcn.h
//
//  Code generation for function 'LatLonAlt2ECEF_Fcn'
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
#include "LatLonAlt2ECEF_Fcn_types.h"

// Function Declarations
CODEGEN_EXPORT_SYM void LatLonAlt2ECEF_Fcn(const emlrtStack *sp, real_T Lat,
  real_T Lon, real_T Alt, real_T r0_ECEF[3]);

// End of code generation (LatLonAlt2ECEF_Fcn.h)
