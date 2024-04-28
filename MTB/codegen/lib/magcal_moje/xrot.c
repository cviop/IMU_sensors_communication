/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xrot.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

/* Include Files */
#include "xrot.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : double x[10000]
 *                int ix0
 *                int iy0
 *                double c
 *                double s
 * Return Type  : void
 */
void b_xrot(double x[10000], int ix0, int iy0, double c, double s)
{
  double b_temp_tmp;
  double temp_tmp;
  int b_temp_tmp_tmp;
  int k;
  int temp_tmp_tmp;
  for (k = 0; k < 1000; k++) {
    temp_tmp_tmp = (iy0 + k) - 1;
    temp_tmp = x[temp_tmp_tmp];
    b_temp_tmp_tmp = (ix0 + k) - 1;
    b_temp_tmp = x[b_temp_tmp_tmp];
    x[temp_tmp_tmp] = c * temp_tmp - s * b_temp_tmp;
    x[b_temp_tmp_tmp] = c * b_temp_tmp + s * temp_tmp;
  }
}

/*
 * Arguments    : int n
 *                double x[9]
 *                int ix0
 *                int iy0
 *                double c
 *                double s
 * Return Type  : void
 */
void c_xrot(int n, double x[9], int ix0, int iy0, double c, double s)
{
  double b_temp_tmp;
  double temp_tmp;
  int b_temp_tmp_tmp;
  int i;
  int k;
  int temp_tmp_tmp;
  if (n >= 1) {
    i = (unsigned char)n;
    for (k = 0; k < i; k++) {
      temp_tmp_tmp = (iy0 + k) - 1;
      temp_tmp = x[temp_tmp_tmp];
      b_temp_tmp_tmp = (ix0 + k) - 1;
      b_temp_tmp = x[b_temp_tmp_tmp];
      x[temp_tmp_tmp] = c * temp_tmp - s * b_temp_tmp;
      x[b_temp_tmp_tmp] = c * b_temp_tmp + s * temp_tmp;
    }
  }
}

/*
 * Arguments    : double x[100]
 *                int ix0
 *                int iy0
 *                double c
 *                double s
 * Return Type  : void
 */
void xrot(double x[100], int ix0, int iy0, double c, double s)
{
  double b_temp_tmp;
  double temp_tmp;
  int b_temp_tmp_tmp;
  int k;
  int temp_tmp_tmp;
  for (k = 0; k < 10; k++) {
    temp_tmp_tmp = (iy0 + k) - 1;
    temp_tmp = x[temp_tmp_tmp];
    b_temp_tmp_tmp = (ix0 + k) - 1;
    b_temp_tmp = x[b_temp_tmp_tmp];
    x[temp_tmp_tmp] = c * temp_tmp - s * b_temp_tmp;
    x[b_temp_tmp_tmp] = c * b_temp_tmp + s * temp_tmp;
  }
}

/*
 * File trailer for xrot.c
 *
 * [EOF]
 */
