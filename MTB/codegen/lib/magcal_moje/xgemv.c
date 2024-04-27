/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgemv.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

/* Include Files */
#include "xgemv.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Declarations */
static int div_nde_s32_floor(int numerator);

/* Function Definitions */
/*
 * Arguments    : int numerator
 * Return Type  : int
 */
static int div_nde_s32_floor(int numerator)
{
  int i;
  if ((numerator < 0) && (numerator % 3 != 0)) {
    i = -1;
  } else {
    i = 0;
  }
  return numerator / 3 + i;
}

/*
 * Arguments    : int m
 *                int n
 *                const double A[9]
 *                int ia0
 *                const double x[9]
 *                int ix0
 *                double y[3]
 * Return Type  : void
 */
void xgemv(int m, int n, const double A[9], int ia0, const double x[9], int ix0,
           double y[3])
{
  double c;
  int i;
  int i1;
  int ia;
  int iac;
  if (n != 0) {
    i = (unsigned char)n;
    memset(&y[0], 0, (unsigned int)i * sizeof(double));
    i = ia0 + 3 * (n - 1);
    for (iac = ia0; iac <= i; iac += 3) {
      c = 0.0;
      i1 = (iac + m) - 1;
      for (ia = iac; ia <= i1; ia++) {
        c += A[ia - 1] * x[((ix0 + ia) - iac) - 1];
      }
      i1 = div_nde_s32_floor(iac - ia0);
      y[i1] += c;
    }
  }
}

/*
 * File trailer for xgemv.c
 *
 * [EOF]
 */
