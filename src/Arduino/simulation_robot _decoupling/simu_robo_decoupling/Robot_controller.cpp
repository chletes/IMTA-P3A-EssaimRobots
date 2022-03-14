/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Robot_controller.c
 *
 * Code generated for Simulink model 'decoupling'.
 *
 * Model version                  : 1.20
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Thu Mar 10 18:19:30 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Robot_controller.h"

/* Include model header file for global data */
#include "decoupling.h"
#include "decoupling_private.h"


/* System initialize for atomic system: '<Root>/Robot_controller' */
void decouplin_Robot_controller_Init(DW_Robot_controller_decouplin_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = 0.05;
}

/* Output and update for atomic system: '<Root>/Robot_controller' */
void decoupling_Robot_controller(real_T rtu_x_ref, real_T rtu_y_ref, real_T
  rtu_x_feedback, real_T rtu_y_feedback, real_T rtu_theta, real_T *rty_Vd,
  real_T *rty_Vg, DW_Robot_controller_decouplin_T *localDW)
{
  real_T rtb_Sum;
  real_T rtb_FilterCoefficient;
  real_T rtb_Sum1;
  real_T rtb_FilterCoefficient_l;
  real_T rtb_Sum_o;
  real_T rtb_Sum_l;
  real_T tmp;
  real_T tmp_0;

  /* Sum: '<S1>/Sum' */
  rtb_Sum = rtu_x_ref - rtu_x_feedback;

  /* Gain: '<S36>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S28>/Filter'
   *  Gain: '<S27>/Derivative Gain'
   *  Sum: '<S28>/SumD'
   */
  rtb_FilterCoefficient = (D_t * rtb_Sum - localDW->Filter_DSTATE) * N_t;

  /* Sum: '<S42>/Sum' incorporates:
   *  DiscreteIntegrator: '<S33>/Integrator'
   *  Gain: '<S38>/Proportional Gain'
   */
  rtb_Sum_o = (P_t * rtb_Sum + localDW->Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* Sum: '<S1>/Sum1' */
  rtb_Sum1 = rtu_y_ref - rtu_y_feedback;

  /* Gain: '<S80>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S72>/Filter'
   *  Gain: '<S71>/Derivative Gain'
   *  Sum: '<S72>/SumD'
   */
  rtb_FilterCoefficient_l = (D_t * rtb_Sum1 - localDW->Filter_DSTATE_c) * N_t;

  /* Sum: '<S86>/Sum' incorporates:
   *  DiscreteIntegrator: '<S77>/Integrator'
   *  Gain: '<S82>/Proportional Gain'
   */
  rtb_Sum_l = (P_t * rtb_Sum1 + localDW->Integrator_DSTATE_g) +
    rtb_FilterCoefficient_l;

  /* Fcn: '<S1>/linearisation calcul u2' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  Fcn: '<S1>/linearisation calcul u1'
   */
  tmp = cos(rtu_theta);
  tmp_0 = sin(rtu_theta);
  *rty_Vg = -tmp_0 / localDW->DiscreteTimeIntegrator_DSTATE * rtb_Sum_o + tmp /
    localDW->DiscreteTimeIntegrator_DSTATE * rtb_Sum_l;

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/L//2'
   */
  *rty_Vg *= L / 2.0;

  /* Sum: '<S1>/Sum2' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  *rty_Vd = localDW->DiscreteTimeIntegrator_DSTATE + *rty_Vg;

  /* Saturate: '<S1>/Saturation1' */
  if (*rty_Vd > Vm) {
    *rty_Vd = Vm;
  } else {
    if (*rty_Vd < -Vm) {
      *rty_Vd = -Vm;
    }
  }

  /* End of Saturate: '<S1>/Saturation1' */

  /* Sum: '<S1>/Sum3' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  *rty_Vg = localDW->DiscreteTimeIntegrator_DSTATE - *rty_Vg;

  /* Saturate: '<S1>/Saturation2' */
  if (*rty_Vg > Vm) {
    *rty_Vg = Vm;
  } else {
    if (*rty_Vg < -Vm) {
      *rty_Vg = -Vm;
    }
  }

  /* End of Saturate: '<S1>/Saturation2' */

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  Fcn: '<S1>/linearisation calcul u1'
   */
  localDW->DiscreteTimeIntegrator_DSTATE += (tmp * rtb_Sum_o + tmp_0 * rtb_Sum_l)
    * Ts;

  /* Update for DiscreteIntegrator: '<S33>/Integrator' incorporates:
   *  Gain: '<S30>/Integral Gain'
   */
  localDW->Integrator_DSTATE += I_t * rtb_Sum * Ts;

  /* Update for DiscreteIntegrator: '<S28>/Filter' */
  localDW->Filter_DSTATE += Ts * rtb_FilterCoefficient;

  /* Update for DiscreteIntegrator: '<S77>/Integrator' incorporates:
   *  Gain: '<S74>/Integral Gain'
   */
  localDW->Integrator_DSTATE_g += I_t * rtb_Sum1 * Ts;

  /* Update for DiscreteIntegrator: '<S72>/Filter' */
  localDW->Filter_DSTATE_c += Ts * rtb_FilterCoefficient_l;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
