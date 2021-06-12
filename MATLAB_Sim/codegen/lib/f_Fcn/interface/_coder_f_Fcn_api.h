/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_Fcn_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 02-Jun-2021 15:49:07
 */

#ifndef _CODER_F_FCN_API_H
#define _CODER_F_FCN_API_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void f_Fcn(real_T t, real_T in2[16], real_T f[10]);
extern void f_Fcn_api(const mxArray * const prhs[2], int32_T nlhs, const mxArray
                      *plhs[1]);
extern void f_Fcn_atexit(void);
extern void f_Fcn_initialize(void);
extern void f_Fcn_terminate(void);
extern void f_Fcn_xil_shutdown(void);
extern void f_Fcn_xil_terminate(void);

#endif

/*
 * File trailer for _coder_f_Fcn_api.h
 *
 * [EOF]
 */
