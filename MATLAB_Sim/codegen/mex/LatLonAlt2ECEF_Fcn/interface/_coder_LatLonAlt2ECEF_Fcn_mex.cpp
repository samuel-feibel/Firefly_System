//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_LatLonAlt2ECEF_Fcn_mex.cpp
//
//  Code generation for function '_coder_LatLonAlt2ECEF_Fcn_mex'
//


// Include files
#include "_coder_LatLonAlt2ECEF_Fcn_mex.h"
#include "LatLonAlt2ECEF_Fcn.h"
#include "LatLonAlt2ECEF_Fcn_data.h"
#include "LatLonAlt2ECEF_Fcn_initialize.h"
#include "LatLonAlt2ECEF_Fcn_terminate.h"
#include "_coder_LatLonAlt2ECEF_Fcn_api.h"

// Function Declarations
MEXFUNCTION_LINKAGE void LatLonAlt2ECEF_Fcn_mexFunction(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[3]);

// Function Definitions
void LatLonAlt2ECEF_Fcn_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[3])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  st.tls = emlrtRootTLSGlobal;

  // Check for proper number of arguments.
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        18, "LatLonAlt2ECEF_Fcn");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 18,
                        "LatLonAlt2ECEF_Fcn");
  }

  // Call the function.
  LatLonAlt2ECEF_Fcn_api(prhs, nlhs, outputs);

  // Copy over outputs to the caller.
  emlrtReturnArrays(1, plhs, &outputs[0]);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&LatLonAlt2ECEF_Fcn_atexit);

  // Module initialization.
  LatLonAlt2ECEF_Fcn_initialize();

  // Dispatch the entry-point.
  LatLonAlt2ECEF_Fcn_mexFunction(nlhs, plhs, nrhs, prhs);

  // Module termination.
  LatLonAlt2ECEF_Fcn_terminate();
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

// End of code generation (_coder_LatLonAlt2ECEF_Fcn_mex.cpp)
