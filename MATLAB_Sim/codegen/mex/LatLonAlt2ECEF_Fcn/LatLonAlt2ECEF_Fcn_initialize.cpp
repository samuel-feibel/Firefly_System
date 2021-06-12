//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  LatLonAlt2ECEF_Fcn_initialize.cpp
//
//  Code generation for function 'LatLonAlt2ECEF_Fcn_initialize'
//


// Include files
#include "LatLonAlt2ECEF_Fcn_initialize.h"
#include "LatLonAlt2ECEF_Fcn.h"
#include "LatLonAlt2ECEF_Fcn_data.h"
#include "_coder_LatLonAlt2ECEF_Fcn_mex.h"
#include "rt_nonfinite.h"

// Variable Definitions
static const volatile char_T *emlrtBreakCheckR2012bFlagVar = NULL;

// Function Definitions
void LatLonAlt2ECEF_Fcn_initialize()
{
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

// End of code generation (LatLonAlt2ECEF_Fcn_initialize.cpp)
