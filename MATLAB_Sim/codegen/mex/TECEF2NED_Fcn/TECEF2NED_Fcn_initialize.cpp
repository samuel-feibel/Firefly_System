//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  TECEF2NED_Fcn_initialize.cpp
//
//  Code generation for function 'TECEF2NED_Fcn_initialize'
//


// Include files
#include "TECEF2NED_Fcn_initialize.h"
#include "TECEF2NED_Fcn.h"
#include "TECEF2NED_Fcn_data.h"
#include "_coder_TECEF2NED_Fcn_mex.h"
#include "rt_nonfinite.h"

// Variable Definitions
static const volatile char_T *emlrtBreakCheckR2012bFlagVar = NULL;

// Function Definitions
void TECEF2NED_Fcn_initialize()
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

// End of code generation (TECEF2NED_Fcn_initialize.cpp)
