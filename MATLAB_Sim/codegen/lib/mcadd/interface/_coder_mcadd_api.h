/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_mcadd_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 02-Jun-2021 13:29:30
 */

#ifndef _CODER_MCADD_API_H
#define _CODER_MCADD_API_H

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
extern real_T mcadd(real_T u, real_T v);
extern void mcadd_api(const mxArray * const prhs[2], int32_T nlhs, const mxArray
                      *plhs[1]);
extern void mcadd_atexit(void);
extern void mcadd_initialize(void);
extern void mcadd_terminate(void);
extern void mcadd_xil_shutdown(void);
extern void mcadd_xil_terminate(void);

#endif

/*
 * File trailer for _coder_mcadd_api.h
 *
 * [EOF]
 */
