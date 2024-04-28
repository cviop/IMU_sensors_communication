/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: svd.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

/* Include Files */
#include "svd.h"
#include "rt_nonfinite.h"
#include "xaxpy.h"
#include "xdotc.h"
#include "xnrm2.h"
#include "xrot.h"
#include "xrotg.h"
#include "xswap.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double A[10000]
 *                double U[10000]
 *                double s[10]
 *                double V[100]
 * Return Type  : void
 */
void svd(const double A[10000], double U[10000], double s[10], double V[100])
{
  double b_A[10000];
  double work[1000];
  double Vf[100];
  double b_s[10];
  double e[10];
  double b;
  double nrm;
  double rt;
  double scale;
  double sm;
  double snorm;
  double sqds;
  int ii;
  int jj;
  int k;
  int m;
  int q;
  int qjj;
  int qp1;
  int qp1jj;
  int qq;
  boolean_T apply_transform;
  boolean_T exitg1;
  memcpy(&b_A[0], &A[0], 10000U * sizeof(double));
  memset(&b_s[0], 0, 10U * sizeof(double));
  memset(&e[0], 0, 10U * sizeof(double));
  memset(&work[0], 0, 1000U * sizeof(double));
  memset(&U[0], 0, 10000U * sizeof(double));
  memset(&Vf[0], 0, 100U * sizeof(double));
  for (q = 0; q < 10; q++) {
    qp1 = q + 2;
    qp1jj = q + 1000 * q;
    qq = qp1jj + 1;
    apply_transform = false;
    nrm = xnrm2(1000 - q, b_A, qp1jj + 1);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qp1jj] < 0.0) {
        nrm = -nrm;
      }
      b_s[q] = nrm;
      if (fabs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        qjj = (qp1jj - q) + 1000;
        for (k = qq; k <= qjj; k++) {
          b_A[k - 1] *= nrm;
        }
      } else {
        qjj = (qp1jj - q) + 1000;
        for (k = qq; k <= qjj; k++) {
          b_A[k - 1] /= b_s[q];
        }
      }
      b_A[qp1jj]++;
      b_s[q] = -b_s[q];
    } else {
      b_s[q] = 0.0;
    }
    for (jj = qp1; jj < 11; jj++) {
      qjj = q + 1000 * (jj - 1);
      if (apply_transform) {
        xaxpy(1000 - q,
              -(xdotc(1000 - q, b_A, qp1jj + 1, b_A, qjj + 1) / b_A[qp1jj]),
              qp1jj + 1, b_A, qjj + 1);
      }
      e[jj - 1] = b_A[qjj];
    }
    for (ii = q + 1; ii < 1001; ii++) {
      qjj = (ii + 1000 * q) - 1;
      U[qjj] = b_A[qjj];
    }
    if (q + 1 <= 8) {
      nrm = b_xnrm2(9 - q, e, q + 2);
      if (nrm == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -nrm;
        } else {
          e[q] = nrm;
        }
        nrm = e[q];
        if (fabs(e[q]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[q];
          for (k = qp1; k < 11; k++) {
            e[k - 1] *= nrm;
          }
        } else {
          for (k = qp1; k < 11; k++) {
            e[k - 1] /= nrm;
          }
        }
        e[q + 1]++;
        e[q] = -e[q];
        for (ii = qp1; ii < 1001; ii++) {
          work[ii - 1] = 0.0;
        }
        for (jj = qp1; jj < 11; jj++) {
          b_xaxpy(999 - q, e[jj - 1], b_A, (q + 1000 * (jj - 1)) + 2, work,
                  q + 2);
        }
        for (jj = qp1; jj < 11; jj++) {
          c_xaxpy(999 - q, -e[jj - 1] / e[q + 1], work, q + 2, b_A,
                  (q + 1000 * (jj - 1)) + 2);
        }
      }
      for (ii = qp1; ii < 11; ii++) {
        Vf[(ii + 10 * q) - 1] = e[ii - 1];
      }
    }
  }
  m = 8;
  e[8] = b_A[9008];
  e[9] = 0.0;
  for (q = 9; q >= 0; q--) {
    qp1 = q + 2;
    qq = q + 1000 * q;
    if (b_s[q] != 0.0) {
      for (jj = qp1; jj < 11; jj++) {
        qjj = (q + 1000 * (jj - 1)) + 1;
        xaxpy(1000 - q, -(xdotc(1000 - q, U, qq + 1, U, qjj) / U[qq]), qq + 1,
              U, qjj);
      }
      for (ii = q + 1; ii < 1001; ii++) {
        qjj = (ii + 1000 * q) - 1;
        U[qjj] = -U[qjj];
      }
      U[qq]++;
      for (ii = 0; ii < q; ii++) {
        U[ii + 1000 * q] = 0.0;
      }
    } else {
      memset(&U[q * 1000], 0, 1000U * sizeof(double));
      U[qq] = 1.0;
    }
  }
  for (q = 9; q >= 0; q--) {
    if ((q + 1 <= 8) && (e[q] != 0.0)) {
      qp1 = q + 2;
      qjj = (q + 10 * q) + 2;
      for (jj = qp1; jj < 11; jj++) {
        qp1jj = (q + 10 * (jj - 1)) + 2;
        d_xaxpy(9 - q, -(b_xdotc(9 - q, Vf, qjj, Vf, qp1jj) / Vf[qjj - 1]), qjj,
                Vf, qp1jj);
      }
    }
    memset(&Vf[q * 10], 0, 10U * sizeof(double));
    Vf[q + 10 * q] = 1.0;
  }
  qq = 0;
  snorm = 0.0;
  for (q = 0; q < 10; q++) {
    nrm = b_s[q];
    if (nrm != 0.0) {
      rt = fabs(nrm);
      nrm /= rt;
      b_s[q] = rt;
      if (q + 1 < 10) {
        e[q] /= nrm;
      }
      qp1jj = 1000 * q;
      qjj = qp1jj + 1000;
      for (k = qp1jj + 1; k <= qjj; k++) {
        U[k - 1] *= nrm;
      }
    }
    if (q + 1 < 10) {
      nrm = e[q];
      if (nrm != 0.0) {
        rt = fabs(nrm);
        nrm = rt / nrm;
        e[q] = rt;
        b_s[q + 1] *= nrm;
        qp1jj = 10 * (q + 1);
        qjj = qp1jj + 10;
        for (k = qp1jj + 1; k <= qjj; k++) {
          Vf[k - 1] *= nrm;
        }
      }
    }
    nrm = fabs(b_s[q]);
    rt = fabs(e[q]);
    if ((nrm >= rt) || rtIsNaN(rt)) {
      rt = nrm;
    }
    if ((!(snorm >= rt)) && (!rtIsNaN(rt))) {
      snorm = rt;
    }
  }
  while ((m + 2 > 0) && (qq < 75)) {
    jj = m + 1;
    ii = m + 1;
    exitg1 = false;
    while (!(exitg1 || (ii == 0))) {
      nrm = fabs(e[ii - 1]);
      if ((nrm <=
           2.2204460492503131E-16 * (fabs(b_s[ii - 1]) + fabs(b_s[ii]))) ||
          (nrm <= 1.0020841800044864E-292) ||
          ((qq > 20) && (nrm <= 2.2204460492503131E-16 * snorm))) {
        e[ii - 1] = 0.0;
        exitg1 = true;
      } else {
        ii--;
      }
    }
    if (ii == m + 1) {
      qjj = 4;
    } else {
      qp1jj = m + 2;
      qjj = m + 2;
      exitg1 = false;
      while ((!exitg1) && (qjj >= ii)) {
        qp1jj = qjj;
        if (qjj == ii) {
          exitg1 = true;
        } else {
          nrm = 0.0;
          if (qjj < m + 2) {
            nrm = fabs(e[qjj - 1]);
          }
          if (qjj > ii + 1) {
            nrm += fabs(e[qjj - 2]);
          }
          rt = fabs(b_s[qjj - 1]);
          if ((rt <= 2.2204460492503131E-16 * nrm) ||
              (rt <= 1.0020841800044864E-292)) {
            b_s[qjj - 1] = 0.0;
            exitg1 = true;
          } else {
            qjj--;
          }
        }
      }
      if (qp1jj == ii) {
        qjj = 3;
      } else if (qp1jj == m + 2) {
        qjj = 1;
      } else {
        qjj = 2;
        ii = qp1jj;
      }
    }
    switch (qjj) {
    case 1:
      rt = e[m];
      e[m] = 0.0;
      for (k = jj; k >= ii + 1; k--) {
        sm = xrotg(&b_s[k - 1], &rt, &sqds);
        if (k > ii + 1) {
          b = e[k - 2];
          rt = -sqds * b;
          e[k - 2] = b * sm;
        }
        xrot(Vf, 10 * (k - 1) + 1, 10 * (m + 1) + 1, sm, sqds);
      }
      break;
    case 2:
      rt = e[ii - 1];
      e[ii - 1] = 0.0;
      for (k = ii + 1; k <= m + 2; k++) {
        sm = xrotg(&b_s[k - 1], &rt, &sqds);
        b = e[k - 1];
        rt = -sqds * b;
        e[k - 1] = b * sm;
        b_xrot(U, 1000 * (k - 1) + 1, 1000 * (ii - 1) + 1, sm, sqds);
      }
      break;
    case 3:
      nrm = b_s[m + 1];
      scale = fabs(nrm);
      rt = fabs(b_s[m]);
      if ((!(scale >= rt)) && (!rtIsNaN(rt))) {
        scale = rt;
      }
      rt = fabs(e[m]);
      if ((!(scale >= rt)) && (!rtIsNaN(rt))) {
        scale = rt;
      }
      rt = fabs(b_s[ii]);
      if ((!(scale >= rt)) && (!rtIsNaN(rt))) {
        scale = rt;
      }
      rt = fabs(e[ii]);
      if ((!(scale >= rt)) && (!rtIsNaN(rt))) {
        scale = rt;
      }
      sm = nrm / scale;
      nrm = b_s[m] / scale;
      rt = e[m] / scale;
      sqds = b_s[ii] / scale;
      b = ((nrm + sm) * (nrm - sm) + rt * rt) / 2.0;
      nrm = sm * rt;
      nrm *= nrm;
      if ((b != 0.0) || (nrm != 0.0)) {
        rt = sqrt(b * b + nrm);
        if (b < 0.0) {
          rt = -rt;
        }
        rt = nrm / (b + rt);
      } else {
        rt = 0.0;
      }
      rt += (sqds + sm) * (sqds - sm);
      nrm = sqds * (e[ii] / scale);
      for (k = ii + 1; k <= jj; k++) {
        sm = xrotg(&rt, &nrm, &sqds);
        if (k > ii + 1) {
          e[k - 2] = rt;
        }
        nrm = e[k - 1];
        b = b_s[k - 1];
        e[k - 1] = sm * nrm - sqds * b;
        rt = sqds * b_s[k];
        b_s[k] *= sm;
        xrot(Vf, 10 * (k - 1) + 1, 10 * k + 1, sm, sqds);
        b_s[k - 1] = sm * b + sqds * nrm;
        sm = xrotg(&b_s[k - 1], &rt, &sqds);
        b = e[k - 1];
        rt = sm * b + sqds * b_s[k];
        b_s[k] = -sqds * b + sm * b_s[k];
        nrm = sqds * e[k];
        e[k] *= sm;
        b_xrot(U, 1000 * (k - 1) + 1, 1000 * k + 1, sm, sqds);
      }
      e[m] = rt;
      qq++;
      break;
    default:
      if (b_s[ii] < 0.0) {
        b_s[ii] = -b_s[ii];
        qp1jj = 10 * ii;
        qjj = qp1jj + 10;
        for (k = qp1jj + 1; k <= qjj; k++) {
          Vf[k - 1] = -Vf[k - 1];
        }
      }
      qp1 = ii + 1;
      while ((ii + 1 < 10) && (b_s[ii] < b_s[qp1])) {
        rt = b_s[ii];
        b_s[ii] = b_s[qp1];
        b_s[qp1] = rt;
        xswap(Vf, 10 * ii + 1, 10 * (ii + 1) + 1);
        b_xswap(U, 1000 * ii + 1, 1000 * (ii + 1) + 1);
        ii = qp1;
        qp1++;
      }
      qq = 0;
      m--;
      break;
    }
  }
  for (k = 0; k < 10; k++) {
    s[k] = b_s[k];
    memcpy(&V[k * 10], &Vf[k * 10], 10U * sizeof(double));
  }
}

/*
 * File trailer for svd.c
 *
 * [EOF]
 */
