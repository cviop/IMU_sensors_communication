/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_magcal_moje_api.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

#ifndef _CODER_MAGCAL_MOJE_API_H
#define _CODER_MAGCAL_MOJE_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void magcal_moje(real_T d[3000], creal_T Winv[9], real_T V[3], real_T *B);

void magcal_moje_api(const mxArray *prhs, int32_T nlhs, const mxArray *plhs[3]);

void magcal_moje_atexit(void);

void magcal_moje_initialize(void);

void magcal_moje_terminate(void);

void magcal_moje_xil_shutdown(void);

void magcal_moje_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_magcal_moje_api.h
 *
 * [EOF]
 */
