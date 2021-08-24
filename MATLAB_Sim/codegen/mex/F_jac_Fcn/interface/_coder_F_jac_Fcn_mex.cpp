//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_F_jac_Fcn_mex.cpp
//
//  Code generation for function '_coder_F_jac_Fcn_mex'
//


// Include files
#include "_coder_F_jac_Fcn_mex.h"
#include "F_jac_Fcn.h"
#include "F_jac_Fcn_data.h"
#include "F_jac_Fcn_initialize.h"
#include "F_jac_Fcn_terminate.h"
#include "_coder_F_jac_Fcn_api.h"

// Function Declarations
MEXFUNCTION_LINKAGE void F_jac_Fcn_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[2]);

// Function Definitions
void F_jac_Fcn_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs, const
  mxArray *prhs[2])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  st.tls = emlrtRootTLSGlobal;

  // Check for proper number of arguments.
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4, 9,
                        "F_jac_Fcn");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 9,
                        "F_jac_Fcn");
  }

  // Call the function.
  F_jac_Fcn_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  emlrtReturnArrays(1, plhs, &outputs[0]);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&F_jac_Fcn_atexit);

  // Module initialization.
  F_jac_Fcn_initialize();

  // Dispatch the entry-point.
  F_jac_Fcn_mexFunction(nlhs, plhs, nrhs, prhs);

  // Module termination.
  F_jac_Fcn_terminate();
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

// End of code generation (_coder_F_jac_Fcn_mex.cpp)
