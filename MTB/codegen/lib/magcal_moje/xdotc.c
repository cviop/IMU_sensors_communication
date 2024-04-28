/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xdotc.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

/* Include Files */
#include "xdotc.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : int n
 *                const double x[100]
 *                int ix0
 *                const double y[100]
 *                int iy0
 * Return Type  : double
 */
double b_xdotc(int n, const double x[100], int ix0, const double y[100],
               int iy0)
{
  double d;
  int i;
  int k;
  d = 0.0;
  i = (unsigned char)n;
  for (k = 0; k < i; k++) {
    d += x[(ix0 + k) - 1] * y[(iy0 + k) - 1];
  }
  return d;
}

/*
 * Arguments    : int n
 *                const double x[10000]
 *                int ix0
 *                const double y[10000]
 *                int iy0
 * Return Type  : double
 */
double xdotc(int n, const double x[10000], int ix0, const double y[10000],
             int iy0)
{
  double d;
  int i;
  int k;
  d = 0.0;
  i = (unsigned short)n;
  for (k = 0; k < i; k++) {
    d += x[(ix0 + k) - 1] * y[(iy0 + k) - 1];
  }
  return d;
}

/*
 * File trailer for xdotc.c
 *
 * [EOF]
 */
