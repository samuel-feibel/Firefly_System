//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  TECEF2NED_Fcn_terminate.cpp
//
//  Code generation for function 'TECEF2NED_Fcn_terminate'
//


// Include files
#include "TECEF2NED_Fcn_terminate.h"
#include "TECEF2NED_Fcn.h"
#include "TECEF2NED_Fcn_data.h"
#include "_coder_TECEF2NED_Fcn_mex.h"
#include "rt_nonfinite.h"

// Function Definitions
void TECEF2NED_Fcn_atexit()
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

void TECEF2NED_Fcn_terminate()
{
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

// End of code generation (TECEF2NED_Fcn_terminate.cpp)
