//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_LatLonAlt2NED_Fcn_mex.h
//
//  Code generation for function '_coder_LatLonAlt2NED_Fcn_mex'
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
MEXFUNCTION_LINKAGE void LatLonAlt2NED_Fcn_mexFunction(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[5]);
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
  const mxArray *prhs[]);
emlrtCTX mexFunctionCreateRootTLS();

// End of code generation (_coder_LatLonAlt2NED_Fcn_mex.h)
