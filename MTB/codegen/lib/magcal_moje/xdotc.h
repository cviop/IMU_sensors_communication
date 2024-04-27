/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xdotc.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

#ifndef XDOTC_H
#define XDOTC_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double b_xdotc(int n, const double x[100], int ix0, const double y[100],
               int iy0);

double xdotc(int n, const double x[10000], int ix0, const double y[10000],
             int iy0);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for xdotc.h
 *
 * [EOF]
 */
