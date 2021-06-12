//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_LatLonAlt2NED_Fcn_mex.cpp
//
//  Code generation for function '_coder_LatLonAlt2NED_Fcn_mex'
//


// Include files
#include "_coder_LatLonAlt2NED_Fcn_mex.h"
#include "LatLonAlt2NED_Fcn.h"
#include "LatLonAlt2NED_Fcn_data.h"
#include "LatLonAlt2NED_Fcn_initialize.h"
#include "LatLonAlt2NED_Fcn_terminate.h"
#include "_coder_LatLonAlt2NED_Fcn_api.h"

// Function Declarations
MEXFUNCTION_LINKAGE void LatLonAlt2NED_Fcn_mexFunction(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[5]);

// Function Definitions
void LatLonAlt2NED_Fcn_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[5])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  st.tls = emlrtRootTLSGlobal;

  // Check for proper number of arguments.
  if (nrhs != 5) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 5, 4,
                        17, "LatLonAlt2NED_Fcn");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 17,
                        "LatLonAlt2NED_Fcn");
  }

  // Call the function.
  LatLonAlt2NED_Fcn_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  emlrtReturnArrays(1, plhs, &outputs[0]);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&LatLonAlt2NED_Fcn_atexit);

  // Module initialization.
  LatLonAlt2NED_Fcn_initialize();

  // Dispatch the entry-point.
  LatLonAlt2NED_Fcn_mexFunction(nlhs, plhs, nrhs, prhs);

  // Module termination.
  LatLonAlt2NED_Fcn_terminate();
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

// End of code generation (_coder_LatLonAlt2NED_Fcn_mex.cpp)
