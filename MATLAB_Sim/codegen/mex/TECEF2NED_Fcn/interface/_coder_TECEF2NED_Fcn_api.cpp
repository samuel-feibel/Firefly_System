//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_TECEF2NED_Fcn_api.cpp
//
//  Code generation for function '_coder_TECEF2NED_Fcn_api'
//


// Include files
#include "_coder_TECEF2NED_Fcn_api.h"
#include "TECEF2NED_Fcn.h"
#include "TECEF2NED_Fcn_data.h"
#include "rt_nonfinite.h"

// Function Declarations
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3];
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *in1, const
  char_T *identifier))[3];
static const mxArray *emlrt_marshallOut(const real_T u[9]);

// Function Definitions
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3]
{
  real_T (*y)[3];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  real_T (*ret)[3];
  static const int32_T dims[1] = { 3 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[3])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *in1, const
  char_T *identifier))[3]
{
  real_T (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char *>(identifier);
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(in1), &thisId);
  emlrtDestroyArray(&in1);
  return y;
}
  static const mxArray *emlrt_marshallOut(const real_T u[9])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 0, 0 };

  static const int32_T iv1[2] = { 3, 3 };

  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, *(int32_T (*)[2])&iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

void TECEF2NED_Fcn_api(const mxArray * const prhs[1], int32_T, const mxArray
  *plhs[1])
{
  real_T (*NED_C_ECEF)[9];
  real_T (*in1)[3];
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  st.tls = emlrtRootTLSGlobal;
  NED_C_ECEF = (real_T (*)[9])mxMalloc(sizeof(real_T [9]));

  // Marshall function inputs
  in1 = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "in1");

  // Invoke the target function
  TECEF2NED_Fcn(&st, *in1, *NED_C_ECEF);

  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*NED_C_ECEF);
}

// End of code generation (_coder_TECEF2NED_Fcn_api.cpp)
