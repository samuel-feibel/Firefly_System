/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_Fcn_info.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 02-Jun-2021 15:49:07
 */

/* Include Files */
#include "_coder_f_Fcn_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : const mxArray *
 */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char * data[9] = {
    "789ced5abd6fd3401c751105060a4c088901100b52a5b87cb464cd6713683e9a843669a9da8b7d6e0ece77eed92e090b1d410ccccc2c8c8c4c8891ff00c1ffc0"
    "c88eede45a27d472db4b8c4873526afff41abff77b173f5fae95a6f2852949922e39af5faf24e9da1dc91b33bdfa4ab794ce48fd63109fea1dcffb6a17e7635a",
    "3aebd53303bfffae775428b160dbea1604e870ff9d2ad51101c4aa750c28316852bc0b550fd1108635a4c3aabf28ba959ef541fb850bb9e7a916549e576d5d62"
    "2df34021f617fb7e7c0ae8f7ec11fd781ce0c7955ecdf1f5cc86fcc484cc944da0db106b10352196d354b175482c532e33fa0c2ace491631a8e1cecd6ac7b4a0",
    "2e1712b5a54472b38a7459dbcc2a24a6f7e9df12d43f1da87fdaab0dfa02b221f29d0be43be7d52ab59b181ef07d14e4cb05f2756b8eafe797eace14250c0323"
    "05588812935b5fb937776f0ec48061c816a5b849db32d4b18c5153d681854153a686297b46c5f4309f2e1f51b7ffe8d73d235df0ea0fbfdb1b6e1d151f1fa785",
    "af1d70bda37eeeae06f0f1cf1dc713f185255c59ed2c1aab71665aaaba9daaa0e4818e72084f980ec9571fd6e7a8afffbfdebf7b82ba6f84e8e6b84255871639"
    "0f4746008e213369236ce549d1792c30a4fcb3dcfd26c8d70ae99fe3c79b37b305185465cfb4de4f771a67bba7b3dc4679d0c6e872f9cd97874fddfab4e464d4",
    "7c51e5f2cb39033d36334a295d46d9d67c2d9e68ce9732e393cb9f03de7f541f9703aecf7de4f8b072f996862dbe16f5f7f15ab08f3b217d707c20a71dd1b893"
    "74beb7b04e550118b0ac4d14b73baecb10d475d9571fa68be35a8f77b30588ea04f8b0f2bb19c2cff1e3cfaffbfa2bb003fdec7ddd892c6f7e5c7c3fc9ef11f2",
    "4595dfd5e28252788921606bcb246de39c599f4f2e8e4f7e8febfd2d9ae7b743fae2f8609eef52a42618039d2c0696050922db7dbab64ea86b7004e9e283f37d"
    "15f46123848fe3c39adf43fcf3a636b29cf9f9b6e1f76fe47cbd715af8225b773fcadd4f3d31eafa72b3a426ea5aaed0d64bb9f1c96dd175773de0fadc478e0f",
    "6ddd4da85504c512cb3bb7fa366451ed3b2393002289e7ef49f73f44ff2ef02890af5b735c689e20764e64cfaaa8d7c9f6fbd793fde711f24595b72f56efce37"
    "d84a2ab3f62057683d2c961bf90aca8e4fdefeeff7f19ea0fe1b21fa393ed9879eec438bf0f1715af826fbd0c3b9feb8ac87f704fbb81ed207c70772daf43653",
    "621aa694f5f9ba25a8e7b8392d3a8f2b21fd737c48fb15b35de364cf38f7991b558e7c9fec2f8f942faa5c5e29eda46d965c4a27c8c24e230e775325ad3306ff"
    "b7f107cbedcda4", "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 10288U, &nameCaptureInfo);
  return nameCaptureInfo;
}

/*
 * Arguments    : void
 * Return Type  : mxArray *
 */
mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * epFieldName[6] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs", "FullPath", "TimeStamp" };

  mxArray *xInputs;
  const char * propFieldName[4] = { "Version", "ResolvedFunctions",
    "EntryPoints", "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 6, epFieldName);
  xInputs = emlrtCreateLogicalMatrix(1, 2);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("f_Fcn"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "/Users/samuelfeibel/Documents/Projects/Firefly System/MATLAB_Sim/f_Fcn.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (738309.65890046291));
  xResult = emlrtCreateStructMatrix(1, 1, 4, propFieldName);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.8.0.1359463 (R2020a) Update 1"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_f_Fcn_info.c
 *
 * [EOF]
 */
