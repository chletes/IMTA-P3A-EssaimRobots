/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: robot.h
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

#ifndef RTW_HEADER_robot_h_
#define RTW_HEADER_robot_h_
#include <math.h>
#ifndef Model_robot_COMMON_INCLUDES_
# define Model_robot_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Model_robot_COMMON_INCLUDES_ */

#include "Model_robot_types.h"

/* Block states (default storage) for system '<Root>/robot' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<S1>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator2_DSTATE;/* '<S1>/Discrete-Time Integrator2' */
} DW_robot_Model_robot_T;

extern void Model_robot_robot(real_T rtu_Vd, real_T rtu_Vg, real_T *rty_x1,
  real_T *rty_y1, real_T *rty_theta, DW_robot_Model_robot_T *localDW);

#endif                                 /* RTW_HEADER_robot_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
