/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Model_robot.c
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

#include "Model_robot.h"
#include "Model_robot_private.h"

/* Exported block signals */
real_T Vd;                             /* '<Root>/Vd' */
real_T Vg;                             /* '<Root>/Vg' */

/* Exported block parameters */
real_T L = 0.085;                      /* Variable: L
                                        * Referenced by: '<S1>/Gain1'
                                        */

/* Block states (default storage) */
DW_Model_robot_T Model_robot_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Model_robot_T Model_robot_Y;

/* Real-time model */
RT_MODEL_Model_robot_T Model_robot_M_;
RT_MODEL_Model_robot_T *const Model_robot_M = &Model_robot_M_;
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
  (Model_robot_M->Timing.TaskCounters.TID[1])++;
  if ((Model_robot_M->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.01s, 0.0s] */
    Model_robot_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void Model_robot_step(void)
{
  if (Model_robot_M->Timing.TaskCounters.TID[1] == 0) {
    /* Outputs for Atomic SubSystem: '<Root>/robot' */
    /* Outport: '<Root>/ theta' incorporates:
     *  Inport: '<Root>/Vd'
     *  Inport: '<Root>/Vg'
     *  Outport: '<Root>/ y1'
     *  Outport: '<Root>/x1'
     */
    Model_robot_robot(Vd, Vg, &Model_robot_Y.x1, &Model_robot_Y.y1,
                      &Model_robot_Y.theta, &Model_robot_DW.robot);

    /* End of Outputs for SubSystem: '<Root>/robot' */
  }

  rate_scheduler();
}

/* Model initialize function */
void Model_robot_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void Model_robot_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
