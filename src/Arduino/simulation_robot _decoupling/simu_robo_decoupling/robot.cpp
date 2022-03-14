/*
 * @Descripttion: 
 * @version: 
 * @Author: Wentao GONG
 * @Date: 2022-03-03 22:24:06
 * @LastEditors: Wentao GONG
 * @LastEditTime: 2022-03-10 18:41:39
 */
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: robot.c
 *
 * Code generated for Simulink model 'Model_robot'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Thu Mar  3 15:19:49 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "robot.h"

/* Include model header file for global data */
#include "Model_robot.h"
#include "Model_robot_private.h"


/* Output and update for atomic system: '<Root>/robot' */
void Model_robot_robot(real_T rtu_Vd, real_T rtu_Vg, real_T *rty_x1, real_T
  *rty_y1, real_T *rty_theta, DW_robot_Model_robot_T *localDW)
{
  real_T rtb_linearisation_calcul_u1;
  real_T rtb_linearisation_calcul_u2;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  *rty_theta = localDW->DiscreteTimeIntegrator_DSTATE;

  /* Gain: '<S1>/Gain' incorporates:
   *  Sum: '<S1>/Sum'
   */
  *rty_x1 = (rtu_Vd + rtu_Vg) * 0.5;

  /* Fcn: '<S1>/linearisation_calcul_u1' */
  rtb_linearisation_calcul_u1 = *rty_x1 * cos(*rty_theta);

  /* Fcn: '<S1>/linearisation_calcul_u2' */
  rtb_linearisation_calcul_u2 = *rty_x1 * sin(*rty_theta);

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  *rty_x1 = localDW->DiscreteTimeIntegrator1_DSTATE;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator2' */
  *rty_y1 = localDW->DiscreteTimeIntegrator2_DSTATE;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Sum: '<S1>/Sum1'
   */
  localDW->DiscreteTimeIntegrator_DSTATE += 1.0 / L * (rtu_Vd - rtu_Vg) * Ts;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE += Ts * rtb_linearisation_calcul_u1;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_DSTATE += Ts * rtb_linearisation_calcul_u2;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
