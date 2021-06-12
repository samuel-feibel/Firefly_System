//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_LatLonAlt2ECEF_Fcn_api.cpp
//
//  Code generation for function '_coder_LatLonAlt2ECEF_Fcn_api'
//


// Include files
#include "_coder_LatLonAlt2ECEF_Fcn_api.h"
#include "LatLonAlt2ECEF_Fcn.h"
#include "LatLonAlt2ECEF_Fcn_data.h"
#include "rt_nonfinite.h"

// Function Declarations
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *Lat, const
  char_T *identifier);
static const mxArray *emlrt_marshallOut(const real_T u[3]);

// Function Definitions
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *Lat, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char *>(identifier);
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(Lat), &thisId);
  emlrtDestroyArray(&Lat);
  return y;
}

static const mxArray *emlrt_marshallOut(const real_T u[3])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[1] = { 0 };

  static const int32_T iv1[1] = { 3 };

  y = NULL;
  m = emlrtCreateNumericArray(1, &iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, *(int32_T (*)[1])&iv1[0], 1);
  emlrtAssign(&y, m);
  return y;
}

void LatLonAlt2ECEF_Fcn_api(const mxArray * const prhs[3], int32_T, const
  mxArray *plhs[1])
{
  real_T (*r0_ECEF)[3];
  real_T Lat;
  real_T Lon;
  real_T Alt;
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  st.tls = emlrtRootTLSGlobal;
  r0_ECEF = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));

  // Marshall function inputs
  Lat = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "Lat");
  Lon = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "Lon");
  Alt = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "Alt");

  // Invoke the target function
  LatLonAlt2ECEF_Fcn(&st, Lat, Lon, Alt, *r0_ECEF);

  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*r0_ECEF);
}

// End of code generation (_coder_LatLonAlt2ECEF_Fcn_api.cpp)
