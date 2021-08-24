//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  getF_stateparam_terminate.cpp
//
//  Code generation for function 'getF_stateparam_terminate'
//


// Include files
#include "getF_stateparam_terminate.h"
#include "_coder_getF_stateparam_mex.h"
#include "getF_stateparam.h"
#include "getF_stateparam_data.h"
#include "rt_nonfinite.h"

// Function Definitions
void getF_stateparam_atexit()
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

void getF_stateparam_terminate()
{
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

// End of code generation (getF_stateparam_terminate.cpp)
