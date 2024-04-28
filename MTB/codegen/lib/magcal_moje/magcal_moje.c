/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: magcal_moje.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

/* Include Files */
#include "magcal_moje.h"
#include "magcal_moje_data.h"
#include "magcal_moje_initialize.h"
#include "rt_nonfinite.h"
#include "sqrtm.h"
#include "svd.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double d;
  double d1;
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }
  return y;
}

/*
 * Arguments    : const double d[3000]
 *                creal_T Winv[9]
 *                double V[3]
 *                double *B
 * Return Type  : void
 */
void magcal_moje(const double d[3000], creal_T Winv[9], double V[3], double *B)
{
  static double b_d[10000];
  static const signed char iv[9] = {0, 1, 2, 1, 3, 4, 2, 4, 5};
  double U[10000];
  double b_V[100];
  double beta[10];
  double A[9];
  double x[9];
  double b_x[7];
  double dA;
  double det3root;
  double s;
  double smax;
  double y2n;
  int b_tmp;
  int i;
  int j;
  int jA;
  int jp1j;
  int mmj_tmp;
  int r2;
  int r3;
  signed char ipiv[3];
  boolean_T isodd;
  if (!isInitialized_magcal_moje) {
    magcal_moje_initialize();
  }
  for (i = 0; i < 1000; i++) {
    smax = d[i];
    s = 2.0 * smax;
    b_d[i] = smax * smax;
    det3root = d[i + 1000];
    b_d[i + 1000] = s * det3root;
    y2n = d[i + 2000];
    b_d[i + 2000] = s * y2n;
    b_d[i + 3000] = det3root * det3root;
    b_d[i + 4000] = 2.0 * det3root * y2n;
    b_d[i + 5000] = y2n * y2n;
    b_d[i + 6000] = smax;
    b_d[i + 7000] = det3root;
    b_d[i + 8000] = y2n;
    b_d[i + 9000] = 1.0;
  }
  /*  Use SVD to compute the eigenvalues and eigenvectors. */
  isodd = true;
  for (jA = 0; jA < 10000; jA++) {
    if (isodd) {
      smax = b_d[jA];
      if (rtIsInf(smax) || rtIsNaN(smax)) {
        isodd = false;
      }
    } else {
      isodd = false;
    }
  }
  if (isodd) {
    svd(b_d, U, beta, b_V);
  } else {
    for (i = 0; i < 100; i++) {
      b_V[i] = rtNaN;
    }
  }
  memcpy(&beta[0], &b_V[90], 10U * sizeof(double));
  /*  Solution has smallest eigenvalue. */
  for (i = 0; i < 3; i++) {
    A[3 * i] = b_V[iv[3 * i] + 90];
    jA = 3 * i + 1;
    A[jA] = b_V[iv[jA] + 90];
    jA = 3 * i + 2;
    A[jA] = b_V[iv[jA] + 90];
  }
  /* make symmetric */
  memcpy(&x[0], &A[0], 9U * sizeof(double));
  ipiv[0] = 1;
  ipiv[1] = 2;
  for (j = 0; j < 2; j++) {
    mmj_tmp = 1 - j;
    b_tmp = j << 2;
    jp1j = b_tmp + 2;
    r2 = 3 - j;
    r3 = 0;
    smax = fabs(x[b_tmp]);
    for (jA = 2; jA <= r2; jA++) {
      s = fabs(x[(b_tmp + jA) - 1]);
      if (s > smax) {
        r3 = jA - 1;
        smax = s;
      }
    }
    if (x[b_tmp + r3] != 0.0) {
      if (r3 != 0) {
        jA = j + r3;
        ipiv[j] = (signed char)(jA + 1);
        smax = x[j];
        x[j] = x[jA];
        x[jA] = smax;
        smax = x[j + 3];
        x[j + 3] = x[jA + 3];
        x[jA + 3] = smax;
        smax = x[j + 6];
        x[j + 6] = x[jA + 6];
        x[jA + 6] = smax;
      }
      i = (b_tmp - j) + 3;
      for (jA = jp1j; jA <= i; jA++) {
        x[jA - 1] /= x[b_tmp];
      }
    }
    jA = b_tmp;
    for (r2 = 0; r2 <= mmj_tmp; r2++) {
      smax = x[(b_tmp + r2 * 3) + 3];
      if (smax != 0.0) {
        i = jA + 5;
        r3 = (jA - j) + 6;
        for (jp1j = i; jp1j <= r3; jp1j++) {
          x[jp1j - 1] += x[((b_tmp + jp1j) - jA) - 4] * -smax;
        }
      }
      jA += 3;
    }
  }
  isodd = (ipiv[0] > 1);
  dA = x[0] * x[4] * x[8];
  if (ipiv[1] > 2) {
    isodd = !isodd;
  }
  if (isodd) {
    dA = -dA;
  }
  if (dA < 0.0) {
    for (i = 0; i < 9; i++) {
      A[i] = -A[i];
    }
    for (i = 0; i < 10; i++) {
      beta[i] = -b_V[i + 90];
    }
    dA = -dA;
    /* Compensate for -A. */
  }
  memcpy(&x[0], &A[0], 9U * sizeof(double));
  jA = 0;
  r2 = 1;
  r3 = 2;
  smax = fabs(A[0]);
  s = fabs(A[1]);
  if (s > smax) {
    smax = s;
    jA = 1;
    r2 = 0;
  }
  if (fabs(A[2]) > smax) {
    jA = 2;
    r2 = 1;
    r3 = 0;
  }
  x[r2] = A[r2] / A[jA];
  x[r3] /= x[jA];
  x[r2 + 3] -= x[r2] * x[jA + 3];
  x[r3 + 3] -= x[r3] * x[jA + 3];
  x[r2 + 6] -= x[r2] * x[jA + 6];
  x[r3 + 6] -= x[r3] * x[jA + 6];
  if (fabs(x[r3 + 3]) > fabs(x[r2 + 3])) {
    jp1j = r2;
    r2 = r3;
    r3 = jp1j;
  }
  x[r3 + 3] /= x[r2 + 3];
  x[r3 + 6] -= x[r3 + 3] * x[r2 + 6];
  smax = beta[jA + 6];
  V[1] = beta[r2 + 6] - smax * x[r2];
  V[2] = (beta[r3 + 6] - smax * x[r3]) - V[1] * x[r3 + 3];
  V[2] /= x[r3 + 6];
  V[0] = smax - V[2] * x[jA + 6];
  V[1] -= V[2] * x[r2 + 6];
  V[1] /= x[r2 + 3];
  V[0] -= V[1] * x[jA + 3];
  V[0] /= x[jA];
  V[0] *= -0.5;
  V[1] *= -0.5;
  V[2] *= -0.5;
  /* hard iron offset */
  b_x[0] = A[0] * V[0] * V[0];
  b_x[1] = 2.0 * A[1] * V[1] * V[0];
  b_x[2] = 2.0 * A[2] * V[2] * V[0];
  b_x[3] = V[1] * A[4] * V[1];
  b_x[4] = 2.0 * A[5] * V[1] * V[2];
  b_x[5] = V[2] * A[8] * V[2];
  b_x[6] = -beta[9];
  s = b_x[0];
  for (jA = 0; jA < 6; jA++) {
    s += b_x[jA + 1];
  }
  /*  We correct Winv and B by det(A) because we don't know which has the */
  /*  gain. By convention, normalize A. */
  det3root = rt_powd_snf(dA, 0.33333333333333331);
  if ((!rtIsInf(det3root)) && (!rtIsNaN(det3root)) && (dA != 0.0)) {
    y2n = rt_powd_snf(det3root, 3.0);
    smax = y2n - dA;
    if (smax != 0.0) {
      det3root -= smax / (3.0 * (y2n / det3root));
    }
  }
  for (i = 0; i < 9; i++) {
    A[i] /= det3root;
  }
  sqrtm(A, Winv);
  *B = sqrt(fabs(s)) / sqrt(det3root);
}

/*
 * File trailer for magcal_moje.c
 *
 * [EOF]
 */
