/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Model_robot.h
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

#ifndef RTW_HEADER_Model_robot_h_
#define RTW_HEADER_Model_robot_h_
#ifndef Model_robot_COMMON_INCLUDES_
# define Model_robot_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Model_robot_COMMON_INCLUDES_ */

#include "Model_robot_types.h"

/* Child system includes */
#include "robot.h"
#include "decouplante.h"

/* Macros for accessing real-time model data structure */

/* Block states (default storage) for system '<Root>' */
typedef struct {
  DW_robot_Model_robot_T robot;        /* '<Root>/robot' */
} DW_Model_robot_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T x1;                           /* '<Root>/x1' */
  real_T y1;                           /* '<Root>/ y1' */
  real_T theta;                        /* '<Root>/ theta' */
} ExtY_Model_robot_T;

/* Real-time Model Data Structure */
struct tag_RTM_Model_robot_T {
  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block states (default storage) */
extern DW_Model_robot_T Model_robot_DW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Model_robot_T Model_robot_Y;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T Vd;                      /* '<Root>/Vd' */
extern real_T Vg;                      /* '<Root>/Vg' */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
// extern real_T L;                       /* Variable: L
//                                         * Referenced by: '<S1>/Gain1'
//                                         */

/* Model entry point functions */
extern void Model_robot_initialize(void);
extern void Model_robot_step(void);
extern void Model_robot_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Model_robot_T *const Model_robot_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Model_robot'
 * '<S1>'   : 'Model_robot/robot'
 */
#endif                                 /* RTW_HEADER_Model_robot_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
