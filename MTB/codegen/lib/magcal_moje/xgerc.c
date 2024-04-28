/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgerc.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

/* Include Files */
#include "xgerc.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : int m
 *                int n
 *                double alpha1
 *                int ix0
 *                const double y[3]
 *                double A[9]
 *                int ia0
 * Return Type  : void
 */
void xgerc(int m, int n, double alpha1, int ix0, const double y[3], double A[9],
           int ia0)
{
  double temp;
  int i;
  int i1;
  int ijA;
  int j;
  int jA;
  if (!(alpha1 == 0.0)) {
    jA = ia0;
    i = (unsigned char)n;
    for (j = 0; j < i; j++) {
      temp = y[j];
      if (temp != 0.0) {
        temp *= alpha1;
        i1 = m + jA;
        for (ijA = jA; ijA < i1; ijA++) {
          A[ijA - 1] += A[((ix0 + ijA) - jA) - 1] * temp;
        }
      }
      jA += 3;
    }
  }
}

/*
 * File trailer for xgerc.c
 *
 * [EOF]
 */
