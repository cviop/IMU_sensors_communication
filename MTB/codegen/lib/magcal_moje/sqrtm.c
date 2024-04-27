/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sqrtm.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

/* Include Files */
#include "sqrtm.h"
#include "magcal_moje_rtwutil.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xdlanv2.h"
#include "xgehrd.h"
#include "xgemv.h"
#include "xgerc.h"
#include "xhseqr.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double A[9]
 *                creal_T X[9]
 * Return Type  : void
 */
void sqrtm(const double A[9], creal_T X[9])
{
  creal_T R[9];
  creal_T T[9];
  creal_T U[9];
  double Vr[9];
  double b_A[9];
  double work[3];
  double tau[2];
  double U_re_tmp;
  double c;
  double cs;
  double d;
  double d_tmp;
  double mu1_im;
  double mu1_re;
  double r;
  double re;
  double rt1i;
  double s;
  double sn;
  double t1_im;
  int b_i;
  int exitg1;
  int exitg2;
  int i;
  int ia;
  int iaii;
  int j;
  int lastc;
  int lastv;
  boolean_T exitg3;
  boolean_T p;
  p = true;
  for (ia = 0; ia < 9; ia++) {
    if (p) {
      U_re_tmp = A[ia];
      if (rtIsInf(U_re_tmp) || rtIsNaN(U_re_tmp)) {
        p = false;
      }
    } else {
      p = false;
    }
  }
  if (!p) {
    for (i = 0; i < 9; i++) {
      U[i].re = rtNaN;
      U[i].im = 0.0;
    }
    U[2].re = 0.0;
    U[2].im = 0.0;
    for (i = 0; i < 9; i++) {
      T[i].re = rtNaN;
      T[i].im = 0.0;
    }
  } else {
    memcpy(&b_A[0], &A[0], 9U * sizeof(double));
    xgehrd(b_A, tau);
    memcpy(&Vr[0], &b_A[0], 9U * sizeof(double));
    for (j = 1; j >= 0; j--) {
      ia = (j + 1) * 3;
      for (b_i = 0; b_i <= j; b_i++) {
        Vr[ia + b_i] = 0.0;
      }
      i = j + 3;
      for (b_i = i; b_i < 4; b_i++) {
        Vr[ia + 2] = Vr[ia - 1];
      }
    }
    Vr[1] = 0.0;
    Vr[2] = 0.0;
    Vr[0] = 1.0;
    work[0] = 0.0;
    work[1] = 0.0;
    work[2] = 0.0;
    for (b_i = 1; b_i >= 0; b_i--) {
      iaii = (b_i + b_i * 3) + 5;
      if (b_i + 1 < 2) {
        Vr[iaii - 1] = 1.0;
        if (tau[b_i] != 0.0) {
          lastv = 2;
          lastc = iaii;
          while ((lastv > 0) && (Vr[lastc] == 0.0)) {
            lastv--;
            lastc--;
          }
          lastc = 1;
          ia = iaii + 3;
          do {
            exitg1 = 0;
            if (ia <= (iaii + lastv) + 2) {
              if (Vr[ia - 1] != 0.0) {
                exitg1 = 1;
              } else {
                ia++;
              }
            } else {
              lastc = 0;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        } else {
          lastv = 0;
          lastc = 0;
        }
        if (lastv > 0) {
          xgemv(lastv, lastc, Vr, iaii + 3, Vr, iaii, work);
          xgerc(lastv, lastc, -tau[b_i], iaii, work, Vr, iaii + 3);
        }
        lastv = iaii + 1;
        for (ia = lastv; ia <= lastv; ia++) {
          Vr[ia - 1] *= -tau[b_i];
        }
      }
      Vr[iaii - 1] = 1.0 - tau[b_i];
      if (b_i - 1 >= 0) {
        Vr[iaii - 2] = 0.0;
      }
    }
    xhseqr(b_A, Vr);
    for (i = 0; i < 9; i++) {
      T[i].re = b_A[i];
      T[i].im = 0.0;
      U[i].re = Vr[i];
      U[i].im = 0.0;
    }
    for (iaii = 1; iaii >= 0; iaii--) {
      lastv = iaii + 1;
      i = iaii + 3 * iaii;
      U_re_tmp = b_A[i + 1];
      if (U_re_tmp != 0.0) {
        r = b_A[i];
        ia = 3 * (iaii + 1);
        lastc = iaii + ia;
        t1_im = b_A[lastc];
        c = U_re_tmp;
        d_tmp = b_A[lastc + 1];
        d = d_tmp;
        mu1_re = xdlanv2(&r, &t1_im, &c, &d, &rt1i, &mu1_im, &s, &cs, &sn);
        mu1_re -= d_tmp;
        r = rt_hypotd_snf(rt_hypotd_snf(mu1_re, rt1i), U_re_tmp);
        if (rt1i == 0.0) {
          re = mu1_re / r;
          sn = 0.0;
        } else if (mu1_re == 0.0) {
          re = 0.0;
          sn = rt1i / r;
        } else {
          re = mu1_re / r;
          sn = rt1i / r;
        }
        s = U_re_tmp / r;
        for (j = lastv; j < 4; j++) {
          lastc = iaii + 3 * (j - 1);
          r = T[lastc].re;
          t1_im = T[lastc].im;
          c = T[lastc + 1].re;
          d_tmp = T[lastc + 1].im;
          T[lastc].re = (re * r + sn * t1_im) + s * c;
          T[lastc].im = (re * t1_im - sn * r) + s * d_tmp;
          mu1_re = re * c - sn * d_tmp;
          mu1_im = re * d_tmp + sn * c;
          T[lastc + 1].re = mu1_re - s * r;
          T[lastc + 1].im = mu1_im - s * t1_im;
        }
        for (b_i = 0; b_i <= iaii + 1; b_i++) {
          lastc = b_i + 3 * iaii;
          r = T[lastc].re;
          t1_im = T[lastc].im;
          lastv = b_i + ia;
          c = T[lastv].re;
          d_tmp = T[lastv].im;
          mu1_re = re * r - sn * t1_im;
          mu1_im = re * t1_im + sn * r;
          T[lastc].re = mu1_re + s * c;
          T[lastc].im = mu1_im + s * d_tmp;
          T[lastv].re = (re * c + sn * d_tmp) - s * r;
          T[lastv].im = (re * d_tmp - sn * c) - s * t1_im;
        }
        r = U[3 * iaii].re;
        t1_im = U[3 * iaii].im;
        c = U[ia].re;
        d_tmp = U[ia].im;
        mu1_re = re * r - sn * t1_im;
        mu1_im = re * t1_im + sn * r;
        U[3 * iaii].re = mu1_re + s * c;
        U[3 * iaii].im = mu1_im + s * d_tmp;
        U[ia].re = (re * c + sn * d_tmp) - s * r;
        U[ia].im = (re * d_tmp - sn * c) - s * t1_im;
        lastc = 3 * iaii + 1;
        r = U[lastc].re;
        t1_im = U[lastc].im;
        c = U[ia + 1].re;
        d_tmp = U[ia + 1].im;
        mu1_re = re * r - sn * t1_im;
        mu1_im = re * t1_im + sn * r;
        U[lastc].re = mu1_re + s * c;
        U[lastc].im = mu1_im + s * d_tmp;
        U[ia + 1].re = (re * c + sn * d_tmp) - s * r;
        U[ia + 1].im = (re * d_tmp - sn * c) - s * t1_im;
        lastc = 3 * iaii + 2;
        r = U[lastc].re;
        t1_im = U[lastc].im;
        c = U[ia + 2].re;
        d_tmp = U[ia + 2].im;
        mu1_re = re * r - sn * t1_im;
        mu1_im = re * t1_im + sn * r;
        U[lastc].re = mu1_re + s * c;
        U[lastc].im = mu1_im + s * d_tmp;
        U[ia + 2].re = (re * c + sn * d_tmp) - s * r;
        U[ia + 2].im = (re * d_tmp - sn * c) - s * t1_im;
        T[(iaii + 3 * iaii) + 1].re = 0.0;
        T[(iaii + 3 * iaii) + 1].im = 0.0;
      }
    }
  }
  j = -1;
  do {
    exitg2 = 0;
    if (j + 1 < 3) {
      b_i = 0;
      do {
        exitg1 = 0;
        if (b_i <= j) {
          lastc = b_i + 3 * (j + 1);
          if ((T[lastc].re != 0.0) || (T[lastc].im != 0.0)) {
            memset(&R[0], 0, 9U * sizeof(creal_T));
            for (j = 0; j < 3; j++) {
              iaii = j + 3 * j;
              R[iaii] = T[iaii];
              b_sqrt(&R[iaii]);
              for (b_i = j; b_i >= 1; b_i--) {
                mu1_re = 0.0;
                mu1_im = 0.0;
                i = b_i + 1;
                for (ia = i; ia <= j; ia++) {
                  t1_im = R[b_i + 2].re;
                  lastc = 3 * j + 1;
                  r = R[lastc].im;
                  c = R[b_i + 2].im;
                  d_tmp = R[lastc].re;
                  mu1_re += t1_im * d_tmp - c * r;
                  mu1_im += t1_im * r + c * d_tmp;
                }
                lastv = (b_i + 3 * j) - 1;
                mu1_re = T[lastv].re - mu1_re;
                cs = T[lastv].im - mu1_im;
                lastc = (b_i + 3 * (b_i - 1)) - 1;
                t1_im = R[lastc].re + R[iaii].re;
                c = R[lastc].im + R[iaii].im;
                if (c == 0.0) {
                  if (cs == 0.0) {
                    re = mu1_re / t1_im;
                    sn = 0.0;
                  } else if (mu1_re == 0.0) {
                    re = 0.0;
                    sn = cs / t1_im;
                  } else {
                    re = mu1_re / t1_im;
                    sn = cs / t1_im;
                  }
                } else if (t1_im == 0.0) {
                  if (mu1_re == 0.0) {
                    re = cs / c;
                    sn = 0.0;
                  } else if (cs == 0.0) {
                    re = 0.0;
                    sn = -(mu1_re / c);
                  } else {
                    re = cs / c;
                    sn = -(mu1_re / c);
                  }
                } else {
                  d_tmp = fabs(t1_im);
                  r = fabs(c);
                  if (d_tmp > r) {
                    s = c / t1_im;
                    d = t1_im + s * c;
                    re = (mu1_re + s * cs) / d;
                    sn = (cs - s * mu1_re) / d;
                  } else if (r == d_tmp) {
                    if (t1_im > 0.0) {
                      t1_im = 0.5;
                    } else {
                      t1_im = -0.5;
                    }
                    if (c > 0.0) {
                      r = 0.5;
                    } else {
                      r = -0.5;
                    }
                    re = (mu1_re * t1_im + cs * r) / d_tmp;
                    sn = (cs * t1_im - mu1_re * r) / d_tmp;
                  } else {
                    s = t1_im / c;
                    d = c + s * t1_im;
                    re = (s * mu1_re + cs) / d;
                    sn = (s * cs - mu1_re) / d;
                  }
                }
                R[lastv].re = re;
                R[lastv].im = sn;
              }
            }
            exitg1 = 1;
          } else {
            b_i++;
          }
        } else {
          j++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);
      if (exitg1 == 1) {
        exitg2 = 1;
      }
    } else {
      memset(&R[0], 0, 9U * sizeof(creal_T));
      R[0] = T[0];
      b_sqrt(&R[0]);
      R[4] = T[4];
      b_sqrt(&R[4]);
      R[8] = T[8];
      b_sqrt(&R[8]);
      exitg2 = 1;
    }
  } while (exitg2 == 0);
  for (i = 0; i < 3; i++) {
    r = U[i].re;
    t1_im = U[i].im;
    c = U[i + 3].re;
    d_tmp = U[i + 3].im;
    mu1_re = U[i + 6].re;
    mu1_im = U[i + 6].im;
    for (lastv = 0; lastv < 3; lastv++) {
      s = R[3 * lastv].im;
      cs = R[3 * lastv].re;
      lastc = 3 * lastv + 1;
      sn = R[lastc].im;
      rt1i = R[lastc].re;
      lastc = 3 * lastv + 2;
      U_re_tmp = R[lastc].im;
      d = R[lastc].re;
      lastc = i + 3 * lastv;
      T[lastc].re = ((r * cs - t1_im * s) + (c * rt1i - d_tmp * sn)) +
                    (mu1_re * d - mu1_im * U_re_tmp);
      T[lastc].im = ((r * s + t1_im * cs) + (c * sn + d_tmp * rt1i)) +
                    (mu1_re * U_re_tmp + mu1_im * d);
    }
    c = T[i].re;
    d_tmp = T[i].im;
    cs = T[i + 3].re;
    mu1_re = T[i + 3].im;
    mu1_im = T[i + 6].re;
    s = T[i + 6].im;
    for (lastv = 0; lastv < 3; lastv++) {
      r = U[lastv].re;
      t1_im = -U[lastv].im;
      re = c * r - d_tmp * t1_im;
      sn = c * t1_im + d_tmp * r;
      r = U[lastv + 3].re;
      t1_im = -U[lastv + 3].im;
      re += cs * r - mu1_re * t1_im;
      sn += cs * t1_im + mu1_re * r;
      r = U[lastv + 6].re;
      t1_im = -U[lastv + 6].im;
      re += mu1_im * r - s * t1_im;
      sn += mu1_im * t1_im + s * r;
      lastc = i + 3 * lastv;
      X[lastc].re = re;
      X[lastc].im = sn;
    }
  }
  for (i = 0; i < 9; i++) {
    b_A[i] = X[i].im;
  }
  r = 0.0;
  j = 0;
  exitg3 = false;
  while ((!exitg3) && (j < 3)) {
    s = (fabs(b_A[3 * j]) + fabs(b_A[3 * j + 1])) + fabs(b_A[3 * j + 2]);
    if (rtIsNaN(s)) {
      r = rtNaN;
      exitg3 = true;
    } else {
      if (s > r) {
        r = s;
      }
      j++;
    }
  }
  t1_im = 0.0;
  j = 0;
  exitg3 = false;
  while ((!exitg3) && (j < 3)) {
    lastc = 3 * j + 1;
    lastv = 3 * j + 2;
    s = (rt_hypotd_snf(X[3 * j].re, X[3 * j].im) +
         rt_hypotd_snf(X[lastc].re, X[lastc].im)) +
        rt_hypotd_snf(X[lastv].re, X[lastv].im);
    if (rtIsNaN(s)) {
      t1_im = rtNaN;
      exitg3 = true;
    } else {
      if (s > t1_im) {
        t1_im = s;
      }
      j++;
    }
  }
  if (r <= 6.6613381477509392E-15 * t1_im) {
    for (j = 0; j < 3; j++) {
      X[3 * j].im = 0.0;
      X[3 * j + 1].im = 0.0;
      X[3 * j + 2].im = 0.0;
    }
  }
}

/*
 * File trailer for sqrtm.c
 *
 * [EOF]
 */
