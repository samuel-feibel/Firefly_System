//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  _coder_LatLonAlt2NED_Fcn_api.cpp
//
//  Code generation for function '_coder_LatLonAlt2NED_Fcn_api'
//


// Include files
#include "_coder_LatLonAlt2NED_Fcn_api.h"
#include "LatLonAlt2NED_Fcn.h"
#include "LatLonAlt2NED_Fcn_data.h"
#include "rt_nonfinite.h"

// Function Declarations
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *in4,
  const char_T *identifier))[3];
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3];
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *in5,
  const char_T *identifier))[9];
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *Lat, const
  char_T *identifier);
static const mxArray *emlrt_marshallOut(const real_T u[3]);
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[9];
static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[9];

// Function Definitions
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = g_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *in4,
  const char_T *identifier))[3]
{
  real_T (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char *>(identifier);
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(in4), &thisId);
  emlrtDestroyArray(&in4);
  return y;
}
  static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3]
{
  real_T (*y)[3];
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *in5,
  const char_T *identifier))[9]
{
  real_T (*y)[9];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char *>(identifier);
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(in5), &thisId);
  emlrtDestroyArray(&in5);
  return y;
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

static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[9]
{
  real_T (*y)[9];
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  real_T (*ret)[3];
  static const int32_T dims[1] = { 3 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[3])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[9]
{
  real_T (*ret)[9];
  static const int32_T dims[2] = { 3, 3 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[9])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void LatLonAlt2NED_Fcn_api(const mxArray * const prhs[5], int32_T, const mxArray
  *plhs[1])
{
  real_T (*r_NED)[3];
  real_T Lat;
  real_T Lon;
  real_T Alt;
  real_T (*in4)[3];
  real_T (*in5)[9];
  emlrtStack st = { NULL,              // site
    NULL,                              // tls
    NULL                               // prev
  };

  st.tls = emlrtRootTLSGlobal;
  r_NED = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));

  // Marshall function inputs
  Lat = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "Lat");
  Lon = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "Lon");
  Alt = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "Alt");
  in4 = c_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "in4");
  in5 = e_emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "in5");

  // Invoke the target function
  LatLonAlt2NED_Fcn(&st, Lat, Lon, Alt, *in4, *in5, *r_NED);

  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*r_NED);
}

// End of code generation (_coder_LatLonAlt2NED_Fcn_api.cpp)
