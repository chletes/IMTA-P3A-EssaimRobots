/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: decoupling.h
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

#ifndef RTW_HEADER_decoupling_h_
#define RTW_HEADER_decoupling_h_
#ifndef decoupling_COMMON_INCLUDES_
# define decoupling_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* decoupling_COMMON_INCLUDES_ */

#include "decoupling_types.h"

/* Child system includes */
#include "Robot_controller.h"

/* Macros for accessing real-time model data structure */

/* Block signals (default storage) */
typedef struct {
  B_Robot_controller_decoupling_T Robot_controller;/* '<Root>/Robot_controller' */
} B_decoupling_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  DW_Robot_controller_decouplin_T Robot_controller;/* '<Root>/Robot_controller' */
} DW_decoupling_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Vd;                           /* '<Root>/Vd' */
  real_T Vg;                           /* '<Root>/Vg' */
} ExtY_decoupling_T;

/* Real-time Model Data Structure */
struct tag_RTM_decoupling_T {
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

/* Block signals (default storage) */
extern B_decoupling_T decoupling_B;

/* Block states (default storage) */
extern DW_decoupling_T decoupling_DW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_decoupling_T decoupling_Y;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T x_ref;                   /* '<Root>/x' */
extern real_T y_ref;                   /* '<Root>/y' */
extern real_T x_feedback;              /* '<Root>/x1' */
extern real_T y_feedback;              /* '<Root>/y1' */
extern real_T theta;                   /* '<Root>/theta ' */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T D_t;                     /* Variable: D_t
                                        * Referenced by:
                                        *   '<S27>/Derivative Gain'
                                        *   '<S71>/Derivative Gain'
                                        */
extern real_T I_t;                     /* Variable: I_t
                                        * Referenced by:
                                        *   '<S30>/Integral Gain'
                                        *   '<S74>/Integral Gain'
                                        */
extern real_T L;                       /* Variable: L
                                        * Referenced by: '<S1>/L//2'
                                        */
extern real_T N_t;                     /* Variable: N_t
                                        * Referenced by:
                                        *   '<S36>/Filter Coefficient'
                                        *   '<S80>/Filter Coefficient'
                                        */
extern real_T P_t;                     /* Variable: P_t
                                        * Referenced by:
                                        *   '<S38>/Proportional Gain'
                                        *   '<S82>/Proportional Gain'
                                        */
extern real_T Vm;                      /* Variable: Vm
                                        * Referenced by: '<S1>/Saturation1'
                                        */

/* Model entry point functions */
extern void decoupling_initialize(void);
extern void decoupling_step(void);
extern void decoupling_terminate(void);

/* Real-time Model object */
extern RT_MODEL_decoupling_T *const decoupling_M;

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
 * '<Root>' : 'decoupling'
 * '<S1>'   : 'decoupling/Robot_controller'
 * '<S2>'   : 'decoupling/Robot_controller/PID Controller'
 * '<S3>'   : 'decoupling/Robot_controller/PID Controller1'
 * '<S4>'   : 'decoupling/Robot_controller/PID Controller/Anti-windup'
 * '<S5>'   : 'decoupling/Robot_controller/PID Controller/D Gain'
 * '<S6>'   : 'decoupling/Robot_controller/PID Controller/Filter'
 * '<S7>'   : 'decoupling/Robot_controller/PID Controller/Filter ICs'
 * '<S8>'   : 'decoupling/Robot_controller/PID Controller/I Gain'
 * '<S9>'   : 'decoupling/Robot_controller/PID Controller/Ideal P Gain'
 * '<S10>'  : 'decoupling/Robot_controller/PID Controller/Ideal P Gain Fdbk'
 * '<S11>'  : 'decoupling/Robot_controller/PID Controller/Integrator'
 * '<S12>'  : 'decoupling/Robot_controller/PID Controller/Integrator ICs'
 * '<S13>'  : 'decoupling/Robot_controller/PID Controller/N Copy'
 * '<S14>'  : 'decoupling/Robot_controller/PID Controller/N Gain'
 * '<S15>'  : 'decoupling/Robot_controller/PID Controller/P Copy'
 * '<S16>'  : 'decoupling/Robot_controller/PID Controller/Parallel P Gain'
 * '<S17>'  : 'decoupling/Robot_controller/PID Controller/Reset Signal'
 * '<S18>'  : 'decoupling/Robot_controller/PID Controller/Saturation'
 * '<S19>'  : 'decoupling/Robot_controller/PID Controller/Saturation Fdbk'
 * '<S20>'  : 'decoupling/Robot_controller/PID Controller/Sum'
 * '<S21>'  : 'decoupling/Robot_controller/PID Controller/Sum Fdbk'
 * '<S22>'  : 'decoupling/Robot_controller/PID Controller/Tracking Mode'
 * '<S23>'  : 'decoupling/Robot_controller/PID Controller/Tracking Mode Sum'
 * '<S24>'  : 'decoupling/Robot_controller/PID Controller/postSat Signal'
 * '<S25>'  : 'decoupling/Robot_controller/PID Controller/preSat Signal'
 * '<S26>'  : 'decoupling/Robot_controller/PID Controller/Anti-windup/Passthrough'
 * '<S27>'  : 'decoupling/Robot_controller/PID Controller/D Gain/Internal Parameters'
 * '<S28>'  : 'decoupling/Robot_controller/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S29>'  : 'decoupling/Robot_controller/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S30>'  : 'decoupling/Robot_controller/PID Controller/I Gain/Internal Parameters'
 * '<S31>'  : 'decoupling/Robot_controller/PID Controller/Ideal P Gain/Passthrough'
 * '<S32>'  : 'decoupling/Robot_controller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S33>'  : 'decoupling/Robot_controller/PID Controller/Integrator/Discrete'
 * '<S34>'  : 'decoupling/Robot_controller/PID Controller/Integrator ICs/Internal IC'
 * '<S35>'  : 'decoupling/Robot_controller/PID Controller/N Copy/Disabled'
 * '<S36>'  : 'decoupling/Robot_controller/PID Controller/N Gain/Internal Parameters'
 * '<S37>'  : 'decoupling/Robot_controller/PID Controller/P Copy/Disabled'
 * '<S38>'  : 'decoupling/Robot_controller/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S39>'  : 'decoupling/Robot_controller/PID Controller/Reset Signal/Disabled'
 * '<S40>'  : 'decoupling/Robot_controller/PID Controller/Saturation/Passthrough'
 * '<S41>'  : 'decoupling/Robot_controller/PID Controller/Saturation Fdbk/Disabled'
 * '<S42>'  : 'decoupling/Robot_controller/PID Controller/Sum/Sum_PID'
 * '<S43>'  : 'decoupling/Robot_controller/PID Controller/Sum Fdbk/Disabled'
 * '<S44>'  : 'decoupling/Robot_controller/PID Controller/Tracking Mode/Disabled'
 * '<S45>'  : 'decoupling/Robot_controller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S46>'  : 'decoupling/Robot_controller/PID Controller/postSat Signal/Forward_Path'
 * '<S47>'  : 'decoupling/Robot_controller/PID Controller/preSat Signal/Forward_Path'
 * '<S48>'  : 'decoupling/Robot_controller/PID Controller1/Anti-windup'
 * '<S49>'  : 'decoupling/Robot_controller/PID Controller1/D Gain'
 * '<S50>'  : 'decoupling/Robot_controller/PID Controller1/Filter'
 * '<S51>'  : 'decoupling/Robot_controller/PID Controller1/Filter ICs'
 * '<S52>'  : 'decoupling/Robot_controller/PID Controller1/I Gain'
 * '<S53>'  : 'decoupling/Robot_controller/PID Controller1/Ideal P Gain'
 * '<S54>'  : 'decoupling/Robot_controller/PID Controller1/Ideal P Gain Fdbk'
 * '<S55>'  : 'decoupling/Robot_controller/PID Controller1/Integrator'
 * '<S56>'  : 'decoupling/Robot_controller/PID Controller1/Integrator ICs'
 * '<S57>'  : 'decoupling/Robot_controller/PID Controller1/N Copy'
 * '<S58>'  : 'decoupling/Robot_controller/PID Controller1/N Gain'
 * '<S59>'  : 'decoupling/Robot_controller/PID Controller1/P Copy'
 * '<S60>'  : 'decoupling/Robot_controller/PID Controller1/Parallel P Gain'
 * '<S61>'  : 'decoupling/Robot_controller/PID Controller1/Reset Signal'
 * '<S62>'  : 'decoupling/Robot_controller/PID Controller1/Saturation'
 * '<S63>'  : 'decoupling/Robot_controller/PID Controller1/Saturation Fdbk'
 * '<S64>'  : 'decoupling/Robot_controller/PID Controller1/Sum'
 * '<S65>'  : 'decoupling/Robot_controller/PID Controller1/Sum Fdbk'
 * '<S66>'  : 'decoupling/Robot_controller/PID Controller1/Tracking Mode'
 * '<S67>'  : 'decoupling/Robot_controller/PID Controller1/Tracking Mode Sum'
 * '<S68>'  : 'decoupling/Robot_controller/PID Controller1/postSat Signal'
 * '<S69>'  : 'decoupling/Robot_controller/PID Controller1/preSat Signal'
 * '<S70>'  : 'decoupling/Robot_controller/PID Controller1/Anti-windup/Passthrough'
 * '<S71>'  : 'decoupling/Robot_controller/PID Controller1/D Gain/Internal Parameters'
 * '<S72>'  : 'decoupling/Robot_controller/PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S73>'  : 'decoupling/Robot_controller/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S74>'  : 'decoupling/Robot_controller/PID Controller1/I Gain/Internal Parameters'
 * '<S75>'  : 'decoupling/Robot_controller/PID Controller1/Ideal P Gain/Passthrough'
 * '<S76>'  : 'decoupling/Robot_controller/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S77>'  : 'decoupling/Robot_controller/PID Controller1/Integrator/Discrete'
 * '<S78>'  : 'decoupling/Robot_controller/PID Controller1/Integrator ICs/Internal IC'
 * '<S79>'  : 'decoupling/Robot_controller/PID Controller1/N Copy/Disabled'
 * '<S80>'  : 'decoupling/Robot_controller/PID Controller1/N Gain/Internal Parameters'
 * '<S81>'  : 'decoupling/Robot_controller/PID Controller1/P Copy/Disabled'
 * '<S82>'  : 'decoupling/Robot_controller/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S83>'  : 'decoupling/Robot_controller/PID Controller1/Reset Signal/Disabled'
 * '<S84>'  : 'decoupling/Robot_controller/PID Controller1/Saturation/Passthrough'
 * '<S85>'  : 'decoupling/Robot_controller/PID Controller1/Saturation Fdbk/Disabled'
 * '<S86>'  : 'decoupling/Robot_controller/PID Controller1/Sum/Sum_PID'
 * '<S87>'  : 'decoupling/Robot_controller/PID Controller1/Sum Fdbk/Disabled'
 * '<S88>'  : 'decoupling/Robot_controller/PID Controller1/Tracking Mode/Disabled'
 * '<S89>'  : 'decoupling/Robot_controller/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S90>'  : 'decoupling/Robot_controller/PID Controller1/postSat Signal/Forward_Path'
 * '<S91>'  : 'decoupling/Robot_controller/PID Controller1/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_decoupling_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
