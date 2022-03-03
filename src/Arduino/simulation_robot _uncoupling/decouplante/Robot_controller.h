/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Robot_controller.h
 *
 * Code generated for Simulink model 'decouplante'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Thu Mar  3 15:03:20 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Robot_controller_h_
#define RTW_HEADER_Robot_controller_h_
#include <math.h>
#ifndef decouplante_COMMON_INCLUDES_
# define decouplante_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* decouplante_COMMON_INCLUDES_ */

#include "decouplante_types.h"

/* Block signals for system '<Root>/Robot_controller' */
typedef struct {
  real_T addantiwindup;                /* '<S1>/Saturation1' */
} B_Robot_controller_decouplant_T;

/* Block states (default storage) for system '<Root>/Robot_controller' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  real_T Integrator_DSTATE;            /* '<S33>/Integrator' */
  real_T Filter_DSTATE;                /* '<S28>/Filter' */
  real_T Integrator_DSTATE_g;          /* '<S77>/Integrator' */
  real_T Filter_DSTATE_c;              /* '<S72>/Filter' */
} DW_Robot_controller_decouplan_T;

extern void decouplan_Robot_controller_Init(DW_Robot_controller_decouplan_T
  *localDW);
extern void decouplante_Robot_controller(real_T rtu_x_ref, real_T rtu_y_ref,
  real_T rtu_x_feedback, real_T rtu_y_feedback, real_T rtu_theta, real_T *rty_Vd,
  real_T *rty_Vg, B_Robot_controller_decouplant_T *localB,
  DW_Robot_controller_decouplan_T *localDW);

#endif                                 /* RTW_HEADER_Robot_controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
