/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xhseqr.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

/* Include Files */
#include "xhseqr.h"
#include "magcal_moje_rtwutil.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xnrm2.h"
#include "xrot.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double h[9]
 *                double z[9]
 * Return Type  : int
 */
int xhseqr(double h[9], double z[9])
{
  double v[3];
  double bb;
  double d;
  double h12;
  double h22;
  double rt1r;
  double rt2r;
  double s;
  double tr;
  double tst;
  int b_i;
  int b_k;
  int i;
  int info;
  int its;
  int k;
  int kdefl;
  int knt;
  int m;
  int nr;
  int tst_tmp_tmp;
  boolean_T aa_tmp;
  boolean_T converged;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  info = 0;
  h[2] = 0.0;
  kdefl = 0;
  i = 2;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    k = -1;
    converged = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      k = i - 1;
      exitg3 = false;
      while ((!exitg3) && (k + 2 > 1)) {
        knt = k + 3 * k;
        h22 = fabs(h[knt + 1]);
        if (h22 <= 3.0062525400134592E-292) {
          exitg3 = true;
        } else {
          nr = 3 * (k + 1);
          tst_tmp_tmp = k + nr;
          h12 = h[tst_tmp_tmp + 1];
          tr = fabs(h12);
          bb = h[knt];
          tst = fabs(bb) + tr;
          if (tst == 0.0) {
            if (k >= 1) {
              tst = fabs(h[k]);
            }
            if (k + 3 <= 3) {
              tst += fabs(h[nr + 2]);
            }
          }
          if (h22 <= 2.2204460492503131E-16 * tst) {
            rt2r = fabs(h[tst_tmp_tmp]);
            h12 = fabs(bb - h12);
            aa_tmp = rtIsNaN(h12);
            if ((tr >= h12) || aa_tmp) {
              tst = tr;
            } else {
              tst = h12;
            }
            if ((tr <= h12) || aa_tmp) {
              bb = tr;
            } else {
              bb = h12;
            }
            s = tst + bb;
            tst = 2.2204460492503131E-16 * (bb * (tst / s));
            aa_tmp = rtIsNaN(rt2r);
            if ((h22 <= rt2r) || aa_tmp) {
              d = h22;
            } else {
              d = rt2r;
            }
            if ((h22 >= rt2r) || aa_tmp) {
              h12 = h22;
            } else {
              h12 = rt2r;
            }
            if ((tst <= 3.0062525400134592E-292) || rtIsNaN(tst)) {
              tst = 3.0062525400134592E-292;
            }
            if (d * (h12 / s) <= tst) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }
      if (k + 2 > 1) {
        h[(k + 3 * k) + 1] = 0.0;
      }
      if (k + 2 >= i) {
        converged = true;
        exitg2 = true;
      } else {
        kdefl++;
        if (kdefl - kdefl / 20 * 20 == 0) {
          s = fabs(h[i + 3 * (i - 1)]) + fabs(h[i - 1]);
          tst = 0.75 * s + h[i + 3 * i];
          h12 = -0.4375 * s;
          bb = s;
          h22 = tst;
        } else if (kdefl - kdefl / 10 * 10 == 0) {
          s = fabs(h[1]) + fabs(h[5]);
          tst = 0.75 * s + h[0];
          h12 = -0.4375 * s;
          bb = s;
          h22 = tst;
        } else {
          knt = i + 3 * (i - 1);
          tst = h[knt - 1];
          bb = h[knt];
          knt = i + 3 * i;
          h12 = h[knt - 1];
          h22 = h[knt];
        }
        s = ((fabs(tst) + fabs(h12)) + fabs(bb)) + fabs(h22);
        if (s == 0.0) {
          rt1r = 0.0;
          tst = 0.0;
          rt2r = 0.0;
          bb = 0.0;
        } else {
          tst /= s;
          bb /= s;
          h12 /= s;
          h22 /= s;
          tr = (tst + h22) / 2.0;
          tst = (tst - tr) * (h22 - tr) - h12 * bb;
          bb = sqrt(fabs(tst));
          if (tst >= 0.0) {
            rt1r = tr * s;
            rt2r = rt1r;
            tst = bb * s;
            bb = -tst;
          } else {
            rt1r = tr + bb;
            rt2r = tr - bb;
            if (fabs(rt1r - h22) <= fabs(rt2r - h22)) {
              rt1r *= s;
              rt2r = rt1r;
            } else {
              rt2r *= s;
              rt1r = rt2r;
            }
            tst = 0.0;
            bb = 0.0;
          }
        }
        m = i - 1;
        if (i - 1 >= 1) {
          h12 = h[0] - rt2r;
          s = (fabs(h12) + fabs(bb)) + fabs(h[1]);
          tr = h[1] / s;
          v[0] = (tr * h[3] + (h[0] - rt1r) * (h12 / s)) - tst * (bb / s);
          v[1] = tr * (((h[0] + h[4]) - rt1r) - rt2r);
          v[2] = tr * h[5];
          s = (fabs(v[0]) + fabs(v[1])) + fabs(v[2]);
          v[0] /= s;
          v[1] /= s;
          v[2] /= s;
        }
        for (b_k = m; b_k <= i; b_k++) {
          knt = (i - b_k) + 2;
          if (knt >= 3) {
            nr = 3;
          } else {
            nr = knt;
          }
          if (b_k > i - 1) {
            knt = ((b_k - 2) * 3 + b_k) - 1;
            for (tst_tmp_tmp = 0; tst_tmp_tmp < nr; tst_tmp_tmp++) {
              v[tst_tmp_tmp] = h[knt + tst_tmp_tmp];
            }
          }
          h12 = v[0];
          rt2r = 0.0;
          if (nr > 0) {
            tst = c_xnrm2(nr - 1, v);
            if (tst != 0.0) {
              bb = rt_hypotd_snf(v[0], tst);
              if (v[0] >= 0.0) {
                bb = -bb;
              }
              if (fabs(bb) < 1.0020841800044864E-292) {
                knt = 0;
                do {
                  knt++;
                  for (tst_tmp_tmp = 2; tst_tmp_tmp <= nr; tst_tmp_tmp++) {
                    v[tst_tmp_tmp - 1] *= 9.9792015476736E+291;
                  }
                  bb *= 9.9792015476736E+291;
                  h12 *= 9.9792015476736E+291;
                } while ((fabs(bb) < 1.0020841800044864E-292) && (knt < 20));
                bb = rt_hypotd_snf(h12, c_xnrm2(nr - 1, v));
                if (h12 >= 0.0) {
                  bb = -bb;
                }
                rt2r = (bb - h12) / bb;
                tst = 1.0 / (h12 - bb);
                for (tst_tmp_tmp = 2; tst_tmp_tmp <= nr; tst_tmp_tmp++) {
                  v[tst_tmp_tmp - 1] *= tst;
                }
                for (tst_tmp_tmp = 0; tst_tmp_tmp < knt; tst_tmp_tmp++) {
                  bb *= 1.0020841800044864E-292;
                }
                h12 = bb;
              } else {
                rt2r = (bb - v[0]) / bb;
                tst = 1.0 / (v[0] - bb);
                for (tst_tmp_tmp = 2; tst_tmp_tmp <= nr; tst_tmp_tmp++) {
                  v[tst_tmp_tmp - 1] *= tst;
                }
                h12 = bb;
              }
            }
          }
          if (b_k > i - 1) {
            h[b_k - 1] = h12;
            h[b_k] = 0.0;
            if (b_k < i) {
              h[2] = 0.0;
            }
          }
          s = v[1];
          h12 = rt2r * v[1];
          if (nr == 3) {
            d = v[2];
            tst = rt2r * v[2];
            for (nr = b_k; nr < 4; nr++) {
              tst_tmp_tmp = 3 * (nr - 1);
              knt = b_k + tst_tmp_tmp;
              bb = h[knt - 1];
              tr = (bb + s * h[knt]) + d * h[tst_tmp_tmp + 2];
              h[knt - 1] = bb - tr * rt2r;
              h[knt] -= tr * h12;
              h[tst_tmp_tmp + 2] -= tr * tst;
            }
            if (b_k + 3 <= i + 1) {
              b_i = b_k + 2;
            } else {
              b_i = i;
            }
            for (nr = 0; nr <= b_i; nr++) {
              tst_tmp_tmp = nr + 3 * (b_k - 1);
              bb = h[tst_tmp_tmp];
              knt = nr + 3 * b_k;
              tr = (bb + s * h[knt]) + d * h[nr + 6];
              h[tst_tmp_tmp] = bb - tr * rt2r;
              h[knt] -= tr * h12;
              h[nr + 6] -= tr * tst;
            }
            tst_tmp_tmp = 3 * (b_k - 1);
            bb = z[tst_tmp_tmp];
            tr = (bb + v[1] * z[3 * b_k]) + v[2] * z[6];
            z[tst_tmp_tmp] = bb - tr * rt2r;
            z[3 * b_k] -= tr * h12;
            z[6] -= tr * tst;
            bb = z[tst_tmp_tmp + 1];
            knt = 3 * b_k + 1;
            tr = (bb + v[1] * z[knt]) + v[2] * z[7];
            z[tst_tmp_tmp + 1] = bb - tr * rt2r;
            z[knt] -= tr * h12;
            z[7] -= tr * tst;
            bb = z[tst_tmp_tmp + 2];
            knt = 3 * b_k + 2;
            tr = (bb + v[1] * z[knt]) + v[2] * z[8];
            z[tst_tmp_tmp + 2] = bb - tr * rt2r;
            z[knt] -= tr * h12;
            z[8] -= tr * tst;
          } else if (nr == 2) {
            for (nr = b_k; nr < 4; nr++) {
              b_i = b_k + 3 * (nr - 1);
              d = h[b_i - 1];
              rt1r = h[b_i];
              tr = d + s * rt1r;
              d -= tr * rt2r;
              h[b_i - 1] = d;
              rt1r -= tr * h12;
              h[b_i] = rt1r;
            }
            for (nr = 0; nr <= i; nr++) {
              b_i = nr + 3 * (b_k - 1);
              d = h[b_i];
              tst_tmp_tmp = nr + 3 * b_k;
              rt1r = h[tst_tmp_tmp];
              tr = d + s * rt1r;
              d -= tr * rt2r;
              h[b_i] = d;
              rt1r -= tr * h12;
              h[tst_tmp_tmp] = rt1r;
            }
            b_i = 3 * (b_k - 1);
            s = z[b_i];
            d = z[3 * b_k];
            tr = s + v[1] * d;
            s -= tr * rt2r;
            z[b_i] = s;
            d -= tr * h12;
            z[3 * b_k] = d;
            s = z[b_i + 1];
            tst_tmp_tmp = 3 * b_k + 1;
            d = z[tst_tmp_tmp];
            tr = s + v[1] * d;
            s -= tr * rt2r;
            z[b_i + 1] = s;
            d -= tr * h12;
            z[tst_tmp_tmp] = d;
            s = z[b_i + 2];
            tst_tmp_tmp = 3 * b_k + 2;
            d = z[tst_tmp_tmp];
            tr = s + v[1] * d;
            s -= tr * rt2r;
            z[b_i + 2] = s;
            d -= tr * h12;
            z[tst_tmp_tmp] = d;
          }
        }
        its++;
      }
    }
    if (!converged) {
      info = i + 1;
      exitg1 = true;
    } else {
      if ((k + 2 != i + 1) && (k + 2 == i)) {
        b_i = i + 3 * i;
        s = h[b_i - 1];
        tst_tmp_tmp = 3 * (i - 1);
        knt = i + tst_tmp_tmp;
        d = h[knt];
        rt1r = h[b_i];
        xdlanv2(&h[knt - 1], &s, &d, &rt1r, &bb, &h12, &tr, &rt2r, &h22);
        h[b_i - 1] = s;
        h[knt] = d;
        h[b_i] = rt1r;
        if (i + 1 < 3) {
          knt = (i + 1) * 3 + i;
          b_i = 1 - i;
          for (b_k = 0; b_k <= b_i; b_k++) {
            nr = knt + b_k * 3;
            tst = h[nr];
            h12 = h[nr - 1];
            h[nr] = rt2r * tst - h22 * h12;
            h[nr - 1] = rt2r * h12 + h22 * tst;
          }
        }
        b_i = i * 3 + 1;
        c_xrot(i - 1, h, tst_tmp_tmp + 1, b_i, rt2r, h22);
        c_xrot(3, z, tst_tmp_tmp + 1, b_i, rt2r, h22);
      }
      kdefl = 0;
      i = k;
    }
  }
  h[2] = 0.0;
  return info;
}

/*
 * File trailer for xhseqr.c
 *
 * [EOF]
 */
