/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: magcal_moje_initialize.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Apr-2024 02:15:45
 */

/* Include Files */
#include "magcal_moje_initialize.h"
#include "magcal_moje_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void magcal_moje_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_magcal_moje = true;
}

/*
 * File trailer for magcal_moje_initialize.c
 *
 * [EOF]
 */
