/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xrot.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

#ifndef XROT_H
#define XROT_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_xrot(double x[10000], int ix0, int iy0, double c, double s);

void c_xrot(int n, double x[9], int ix0, int iy0, double c, double s);

void xrot(double x[100], int ix0, int iy0, double c, double s);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for xrot.h
 *
 * [EOF]
 */
