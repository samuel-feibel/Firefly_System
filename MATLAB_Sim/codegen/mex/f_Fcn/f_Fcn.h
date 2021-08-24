//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  f_Fcn.h
//
//  Code generation for function 'f_Fcn'
//


#pragma once

// Include files
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "f_Fcn_types.h"

// Function Declarations
CODEGEN_EXPORT_SYM void f_Fcn(const emlrtStack *sp, real_T t, const real_T in2
  [10], const real_T in3[6], real_T f[10]);

// End of code generation (f_Fcn.h)
