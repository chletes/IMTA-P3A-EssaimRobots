/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: decoupling.c
 *
 * Code generated for Simulink model 'decoupling'.
 *
 * Model version                  : 1.19
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Mon Mar  7 11:30:05 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "decoupling.h"
#include "decoupling_private.h"

/* Exported block signals */
real_T x_ref;                          /* '<Root>/x' */
real_T y_ref;                          /* '<Root>/y' */
real_T x_feedback;                     /* '<Root>/x1' */
real_T y_feedback;                     /* '<Root>/y1' */
real_T theta;                          /* '<Root>/theta ' */

/* Exported block parameters */
real_T D_t = 42.0;                     /* Variable: D_t
                                        * Referenced by:
                                        *   '<S27>/Derivative Gain'
                                        *   '<S71>/Derivative Gain'
                                        */
real_T I_t = 0.0;                      /* Variable: I_t
                                        * Referenced by:
                                        *   '<S30>/Integral Gain'
                                        *   '<S74>/Integral Gain'
                                        */
real_T L = 0.085;                      /* Variable: L
                                        * Referenced by: '<S1>/L//2'
                                        */
real_T N_t = 20.0;                     /* Variable: N_t
                                        * Referenced by:
                                        *   '<S36>/Filter Coefficient'
                                        *   '<S80>/Filter Coefficient'
                                        */
real_T P_t = 82.0;                     /* Variable: P_t
                                        * Referenced by:
                                        *   '<S38>/Proportional Gain'
                                        *   '<S82>/Proportional Gain'
                                        */
real_T Vm = 5.0;                       /* Variable: Vm
                                        * Referenced by: '<S1>/Saturation1'
                                        */

/* Block signals (default storage) */
B_decoupling_T decoupling_B;

/* Block states (default storage) */
DW_decoupling_T decoupling_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_decoupling_T decoupling_Y;

/* Real-time model */
RT_MODEL_decoupling_T decoupling_M_;
RT_MODEL_decoupling_T *const decoupling_M = &decoupling_M_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (decoupling_M->Timing.TaskCounters.TID[1])++;
  if ((decoupling_M->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.01s, 0.0s] */
    decoupling_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void decoupling_step(void)
{
  if (decoupling_M->Timing.TaskCounters.TID[1] == 0) {
    /* Outputs for Atomic SubSystem: '<Root>/Robot_controller' */
    /* Outport: '<Root>/Vg' incorporates:
     *  Inport: '<Root>/theta '
     *  Inport: '<Root>/x'
     *  Inport: '<Root>/x1'
     *  Inport: '<Root>/y'
     *  Inport: '<Root>/y1'
     *  Outport: '<Root>/Vd'
     */
    decoupling_Robot_controller(x_ref, y_ref, x_feedback, y_feedback, theta,
      &decoupling_Y.Vd, &decoupling_Y.Vg, &decoupling_B.Robot_controller,
      &decoupling_DW.Robot_controller);

    /* End of Outputs for SubSystem: '<Root>/Robot_controller' */
  }

  rate_scheduler();
}

/* Model initialize function */
void decoupling_initialize(void)
{
  /* Registration code */

  /* external inputs */
  y_feedback = 0.085;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Robot_controller' */
  decouplin_Robot_controller_Init(&decoupling_DW.Robot_controller);

  /* End of SystemInitialize for SubSystem: '<Root>/Robot_controller' */
}

/* Model terminate function */
void decoupling_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
