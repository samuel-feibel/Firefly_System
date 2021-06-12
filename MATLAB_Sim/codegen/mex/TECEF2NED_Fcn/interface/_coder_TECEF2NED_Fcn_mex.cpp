//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_TECEF2NED_Fcn_mex.cpp
//
//  Code generation for function '_coder_TECEF2NED_Fcn_mex'
//


// Include files
#include "_coder_TECEF2NED_Fcn_mex.h"
#include "TECEF2NED_Fcn.h"
#include "TECEF2NED_Fcn_data.h"
#include "TECEF2NED_Fcn_initialize.h"
#include "TECEF2NED_Fcn_terminate.h"
#include "_coder_TECEF2NED_Fcn_api.h"

// Function Declarations
MEXFUNCTION_LINKAGE void TECEF2NED_Fcn_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[1]);

// Function Definitions
void TECEF2NED_Fcn_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[1])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  st.tls = emlrtRootTLSGlobal;

  // Check for proper number of arguments.
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        13, "TECEF2NED_Fcn");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 13,
                        "TECEF2NED_Fcn");
  }

  // Call the function.
  TECEF2NED_Fcn_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  emlrtReturnArrays(1, plhs, &outputs[0]);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&TECEF2NED_Fcn_atexit);

  // Module initialization.
  TECEF2NED_Fcn_initialize();

  // Dispatch the entry-point.
  TECEF2NED_Fcn_mexFunction(nlhs, plhs, nrhs, prhs);

  // Module termination.
  TECEF2NED_Fcn_terminate();
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

// End of code generation (_coder_TECEF2NED_Fcn_mex.cpp)
