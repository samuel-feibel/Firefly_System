//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  LatLonAlt2ECEF_Fcn_terminate.cpp
//
//  Code generation for function 'LatLonAlt2ECEF_Fcn_terminate'
//


// Include files
#include "LatLonAlt2ECEF_Fcn_terminate.h"
#include "LatLonAlt2ECEF_Fcn.h"
#include "LatLonAlt2ECEF_Fcn_data.h"
#include "_coder_LatLonAlt2ECEF_Fcn_mex.h"
#include "rt_nonfinite.h"

// Function Definitions
void LatLonAlt2ECEF_Fcn_atexit()
{
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void LatLonAlt2ECEF_Fcn_terminate()
{
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

// End of code generation (LatLonAlt2ECEF_Fcn_terminate.cpp)
