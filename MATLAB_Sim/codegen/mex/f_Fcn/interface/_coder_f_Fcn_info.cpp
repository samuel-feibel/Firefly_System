/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_f_Fcn_info.cpp
 *
 * Code generation for function '_coder_f_Fcn_info'
 *
 */

/* Include files */
#include "_coder_f_Fcn_info.h"
#include "emlrt.h"
#include "rt_nonfinite.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo();

/* Function Definitions */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo()
{
  const mxArray *nameCaptureInfo;
  const char * data[9] = {
    "789ced5acd53d3401c0d8ea807114e8e331ed4f1c20c330da220d77eda02fda0e5a3a80c6c930d5dddecc64d022d1739e278f0ccd98b478f9e1c8ffe078efc1f"
    "de4dd22e844a26e0b6716cbb3325f9cda379eff7b679d92e4823b9fc882449b79cd7f15b49ba33297963ac5d4fb44ae98a747674e223ede3755fede27c8c4a57",
    "bd7aace3f73fb48f0a25166c58ad82001d9ebc53a53a2280582b4d034a0c9a14ef42d5433484e10ad261c55f14dc4acff8a093c285dcf3641d2aaf2bb62eb1ba"
    "79aa10fb8b133f3e07f47bf5827e2c06f831d1ae39fe22bd29af9a9099b209741b620da21ac4728a2ab60e8965ca25465f41c539c9200635dcbc5f699a16d4e5",
    "7c7c65299ed8aa205dd6b6320a89e967f46f0bea1f0dd43fead506dd83ac8b7cd702f9ae79b54aed1a86a77c9f04f9b2817cad9ae32f724b55678ae286819102"
    "2c4489c9ad2fcf4ccf4c8318300cd9a214d76843863a9631aac93ab030a8c9d43065cfa8981ee6d3f80575fb8f7edd63d20daffef8abb1e9d651f1f131287c8d",
    "80eb5df473773b808f7fee381e9f9f5bc2e5f5e633637d9e9996aaee24cb2871aaa314c213a643f2d5e7f5d9ebebffaff7ef81a0ee7b21ba39ae50d5a145cec3"
    "91118063c84cd8085b3952701e0b0c29ff2c77bf0bf2d543fae7f8e5e6cdac030655d933adfdd39dc6a9d6e914b751eeb431ba5c7ef7f5e94bb71e949c8c9a2f",
    "aa5cde9f36d0a299568aa912cad46757e6e3b5d962ba7f72f94bc0fb2feae372c0f5b98f1cef562e3fd0b0c5d7a2fe3e0e05fb980ce983e31d39ed88c6cd84f3"
    "bd85352b0ac080656ca2b8dd715d86a0ae715f7d9e2e8e6b6ddead3a20aa13e0ddcaef5a083fc72f3fbfeeeb8fc00ef4b3fd7527b2bcf979f36898df3de48b2a",
    "bf2b853925bf8f2160cf9749cac659b33a9b78d63ff9ddaff7b7689e3f0ce98be39d79be4b911a670c34331858162488ec9cd1b5fd97ba3a47902e3e38df3741"
    "1f3643f838deadf93dc73f6f6a23cb99e3f71b7eff7aced71e83c217d9ba7b21fb38b96a54f5e55a518d57b56cbea117b3fd93dba2ebee6ac0f5b98f1cefdaba",
    "9b50ab000a4596736ef51dc8a2da774626014412cfdfbfddff10fdbbc042205fabe6b8d03c41ec9cc89e5551af93eda3c3e1fe730ff9a2cadbbdf547b31b6c2d"
    "997efe249baf3f2d9436726594e99fbcfddfefe30341fdf742f4737cb80f3ddc8716e1e36350f886fbd0ddb97ebfac870f04fbb81bd207c73b72daf43653621a",
    "a6949df1755b50cf65735a741ed742fae77897f62ba65ac6c99e71ee3337aa1cf931dc5fee295f54b9bc567c93b25962291527736f36e6e16eb2a835fbe0ff36"
    "7e03e53cb1bc", "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 10288U, &nameCaptureInfo);
  return nameCaptureInfo;
}

mxArray *emlrtMexFcnProperties()
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * epFieldName[6] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs", "FullPath", "TimeStamp" };

  mxArray *xInputs;
  const char * propFieldName[4] = { "Version", "ResolvedFunctions",
    "EntryPoints", "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 6, epFieldName);
  xInputs = emlrtCreateLogicalMatrix(1, 3);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("f_Fcn"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(3.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "/Users/samuelfeibel/Documents/Projects/Firefly System/MATLAB_Sim/f_Fcn.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (738384.63744212966));
  xResult = emlrtCreateStructMatrix(1, 1, 4, propFieldName);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.8.0.1359463 (R2020a) Update 1"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_f_Fcn_info.cpp) */
