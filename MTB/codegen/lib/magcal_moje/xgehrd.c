/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgehrd.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

/* Include Files */
#include "xgehrd.h"
#include "magcal_moje_rtwutil.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include "xgerc.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double a[9]
 *                double tau[2]
 * Return Type  : void
 */
void xgehrd(double a[9], double tau[2])
{
  double work[3];
  double alpha1_tmp;
  double beta1;
  double xnorm;
  int alpha1_tmp_tmp;
  int b_i;
  int c_i;
  int exitg1;
  int i;
  int i1;
  int ia;
  int in;
  int iv0_tmp;
  int ix0;
  int k;
  int knt;
  int lastc;
  int lastv;
  boolean_T exitg2;
  work[0] = 0.0;
  work[1] = 0.0;
  work[2] = 0.0;
  for (i = 0; i < 2; i++) {
    b_i = i * 3 + 2;
    in = (i + 1) * 3;
    alpha1_tmp_tmp = (i + 3 * i) + 1;
    alpha1_tmp = a[alpha1_tmp_tmp];
    ix0 = b_i + 1;
    tau[i] = 0.0;
    xnorm = 0.0;
    if (1 - i >= 1) {
      xnorm = fabs(a[b_i]);
    }
    if (xnorm != 0.0) {
      beta1 = rt_hypotd_snf(alpha1_tmp, xnorm);
      if (alpha1_tmp >= 0.0) {
        beta1 = -beta1;
      }
      if (fabs(beta1) < 1.0020841800044864E-292) {
        knt = 0;
        c_i = (b_i - i) + 1;
        do {
          knt++;
          for (k = ix0; k <= c_i; k++) {
            a[k - 1] *= 9.9792015476736E+291;
          }
          beta1 *= 9.9792015476736E+291;
          alpha1_tmp *= 9.9792015476736E+291;
        } while ((fabs(beta1) < 1.0020841800044864E-292) && (knt < 20));
        xnorm = 0.0;
        if (1 - i >= 1) {
          xnorm = fabs(a[b_i]);
        }
        beta1 = rt_hypotd_snf(alpha1_tmp, xnorm);
        if (alpha1_tmp >= 0.0) {
          beta1 = -beta1;
        }
        tau[i] = (beta1 - alpha1_tmp) / beta1;
        xnorm = 1.0 / (alpha1_tmp - beta1);
        for (k = ix0; k <= c_i; k++) {
          a[k - 1] *= xnorm;
        }
        for (k = 0; k < knt; k++) {
          beta1 *= 1.0020841800044864E-292;
        }
        alpha1_tmp = beta1;
      } else {
        tau[i] = (beta1 - alpha1_tmp) / beta1;
        xnorm = 1.0 / (alpha1_tmp - beta1);
        c_i = (b_i - i) + 1;
        for (k = ix0; k <= c_i; k++) {
          a[k - 1] *= xnorm;
        }
        alpha1_tmp = beta1;
      }
    }
    a[alpha1_tmp_tmp] = 1.0;
    iv0_tmp = i + b_i;
    k = in + 1;
    if (tau[i] != 0.0) {
      lastv = 1 - i;
      b_i = iv0_tmp - i;
      while ((lastv + 1 > 0) && (a[b_i] == 0.0)) {
        lastv--;
        b_i--;
      }
      lastc = 3;
      exitg2 = false;
      while ((!exitg2) && (lastc > 0)) {
        b_i = in + lastc;
        ia = b_i;
        do {
          exitg1 = 0;
          if (ia <= b_i + lastv * 3) {
            if (a[ia - 1] != 0.0) {
              exitg1 = 1;
            } else {
              ia += 3;
            }
          } else {
            lastc--;
            exitg1 = 2;
          }
        } while (exitg1 == 0);
        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    } else {
      lastv = -1;
      lastc = 0;
    }
    if (lastv + 1 > 0) {
      if (lastc != 0) {
        memset(&work[0], 0, (unsigned int)lastc * sizeof(double));
        b_i = iv0_tmp - 1;
        c_i = (in + 3 * lastv) + 1;
        for (knt = k; knt <= c_i; knt += 3) {
          i1 = (knt + lastc) - 1;
          for (ia = knt; ia <= i1; ia++) {
            ix0 = ia - knt;
            work[ix0] += a[ia - 1] * a[b_i];
          }
          b_i++;
        }
      }
      if (!(-tau[i] == 0.0)) {
        b_i = in;
        for (ix0 = 0; ix0 <= lastv; ix0++) {
          xnorm = a[(iv0_tmp + ix0) - 1];
          if (xnorm != 0.0) {
            xnorm *= -tau[i];
            c_i = b_i + 1;
            i1 = lastc + b_i;
            for (knt = c_i; knt <= i1; knt++) {
              a[knt - 1] += work[(knt - b_i) - 1] * xnorm;
            }
          }
          b_i += 3;
        }
      }
    }
    k = (i + in) + 2;
    if (tau[i] != 0.0) {
      lastv = 2 - i;
      b_i = iv0_tmp - i;
      while ((lastv > 0) && (a[b_i] == 0.0)) {
        lastv--;
        b_i--;
      }
      lastc = 2 - i;
      exitg2 = false;
      while ((!exitg2) && (lastc > 0)) {
        b_i = k + (lastc - 1) * 3;
        ia = b_i;
        do {
          exitg1 = 0;
          if (ia <= (b_i + lastv) - 1) {
            if (a[ia - 1] != 0.0) {
              exitg1 = 1;
            } else {
              ia++;
            }
          } else {
            lastc--;
            exitg1 = 2;
          }
        } while (exitg1 == 0);
        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    } else {
      lastv = 0;
      lastc = 0;
    }
    if (lastv > 0) {
      xgemv(lastv, lastc, a, k, a, iv0_tmp, work);
      xgerc(lastv, lastc, -tau[i], iv0_tmp, work, a, k);
    }
    a[alpha1_tmp_tmp] = alpha1_tmp;
  }
}

/*
 * File trailer for xgehrd.c
 *
 * [EOF]
 */
