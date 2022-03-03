/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: decouplante.h
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

#ifndef RTW_HEADER_decouplante_h_
#define RTW_HEADER_decouplante_h_
#ifndef decouplante_COMMON_INCLUDES_
# define decouplante_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* decouplante_COMMON_INCLUDES_ */

#include "decouplante_types.h"

/* Child system includes */
#include "Robot_controller.h"

/* Macros for accessing real-time model data structure */

/* Block signals (default storage) */
typedef struct {
  B_Robot_controller_decouplant_T Robot_controller;/* '<Root>/Robot_controller' */
} B_decouplante_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  DW_Robot_controller_decouplan_T Robot_controller;/* '<Root>/Robot_controller' */
} DW_decouplante_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Vd;                           /* '<Root>/Vd' */
  real_T Vg;                           /* '<Root>/Vg' */
} ExtY_decouplante_T;

/* Real-time Model Data Structure */
struct tag_RTM_decouplante_T {
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
extern B_decouplante_T decouplante_B;

/* Block states (default storage) */
extern DW_decouplante_T decouplante_DW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_decouplante_T decouplante_Y;

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
extern void decouplante_initialize(void);
extern void decouplante_step(void);
extern void decouplante_terminate(void);

/* Real-time Model object */
extern RT_MODEL_decouplante_T *const decouplante_M;

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
 * '<Root>' : 'decouplante'
 * '<S1>'   : 'decouplante/Robot_controller'
 * '<S2>'   : 'decouplante/Robot_controller/PID Controller'
 * '<S3>'   : 'decouplante/Robot_controller/PID Controller1'
 * '<S4>'   : 'decouplante/Robot_controller/PID Controller/Anti-windup'
 * '<S5>'   : 'decouplante/Robot_controller/PID Controller/D Gain'
 * '<S6>'   : 'decouplante/Robot_controller/PID Controller/Filter'
 * '<S7>'   : 'decouplante/Robot_controller/PID Controller/Filter ICs'
 * '<S8>'   : 'decouplante/Robot_controller/PID Controller/I Gain'
 * '<S9>'   : 'decouplante/Robot_controller/PID Controller/Ideal P Gain'
 * '<S10>'  : 'decouplante/Robot_controller/PID Controller/Ideal P Gain Fdbk'
 * '<S11>'  : 'decouplante/Robot_controller/PID Controller/Integrator'
 * '<S12>'  : 'decouplante/Robot_controller/PID Controller/Integrator ICs'
 * '<S13>'  : 'decouplante/Robot_controller/PID Controller/N Copy'
 * '<S14>'  : 'decouplante/Robot_controller/PID Controller/N Gain'
 * '<S15>'  : 'decouplante/Robot_controller/PID Controller/P Copy'
 * '<S16>'  : 'decouplante/Robot_controller/PID Controller/Parallel P Gain'
 * '<S17>'  : 'decouplante/Robot_controller/PID Controller/Reset Signal'
 * '<S18>'  : 'decouplante/Robot_controller/PID Controller/Saturation'
 * '<S19>'  : 'decouplante/Robot_controller/PID Controller/Saturation Fdbk'
 * '<S20>'  : 'decouplante/Robot_controller/PID Controller/Sum'
 * '<S21>'  : 'decouplante/Robot_controller/PID Controller/Sum Fdbk'
 * '<S22>'  : 'decouplante/Robot_controller/PID Controller/Tracking Mode'
 * '<S23>'  : 'decouplante/Robot_controller/PID Controller/Tracking Mode Sum'
 * '<S24>'  : 'decouplante/Robot_controller/PID Controller/postSat Signal'
 * '<S25>'  : 'decouplante/Robot_controller/PID Controller/preSat Signal'
 * '<S26>'  : 'decouplante/Robot_controller/PID Controller/Anti-windup/Passthrough'
 * '<S27>'  : 'decouplante/Robot_controller/PID Controller/D Gain/Internal Parameters'
 * '<S28>'  : 'decouplante/Robot_controller/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S29>'  : 'decouplante/Robot_controller/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S30>'  : 'decouplante/Robot_controller/PID Controller/I Gain/Internal Parameters'
 * '<S31>'  : 'decouplante/Robot_controller/PID Controller/Ideal P Gain/Passthrough'
 * '<S32>'  : 'decouplante/Robot_controller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S33>'  : 'decouplante/Robot_controller/PID Controller/Integrator/Discrete'
 * '<S34>'  : 'decouplante/Robot_controller/PID Controller/Integrator ICs/Internal IC'
 * '<S35>'  : 'decouplante/Robot_controller/PID Controller/N Copy/Disabled'
 * '<S36>'  : 'decouplante/Robot_controller/PID Controller/N Gain/Internal Parameters'
 * '<S37>'  : 'decouplante/Robot_controller/PID Controller/P Copy/Disabled'
 * '<S38>'  : 'decouplante/Robot_controller/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S39>'  : 'decouplante/Robot_controller/PID Controller/Reset Signal/Disabled'
 * '<S40>'  : 'decouplante/Robot_controller/PID Controller/Saturation/Passthrough'
 * '<S41>'  : 'decouplante/Robot_controller/PID Controller/Saturation Fdbk/Disabled'
 * '<S42>'  : 'decouplante/Robot_controller/PID Controller/Sum/Sum_PID'
 * '<S43>'  : 'decouplante/Robot_controller/PID Controller/Sum Fdbk/Disabled'
 * '<S44>'  : 'decouplante/Robot_controller/PID Controller/Tracking Mode/Disabled'
 * '<S45>'  : 'decouplante/Robot_controller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S46>'  : 'decouplante/Robot_controller/PID Controller/postSat Signal/Forward_Path'
 * '<S47>'  : 'decouplante/Robot_controller/PID Controller/preSat Signal/Forward_Path'
 * '<S48>'  : 'decouplante/Robot_controller/PID Controller1/Anti-windup'
 * '<S49>'  : 'decouplante/Robot_controller/PID Controller1/D Gain'
 * '<S50>'  : 'decouplante/Robot_controller/PID Controller1/Filter'
 * '<S51>'  : 'decouplante/Robot_controller/PID Controller1/Filter ICs'
 * '<S52>'  : 'decouplante/Robot_controller/PID Controller1/I Gain'
 * '<S53>'  : 'decouplante/Robot_controller/PID Controller1/Ideal P Gain'
 * '<S54>'  : 'decouplante/Robot_controller/PID Controller1/Ideal P Gain Fdbk'
 * '<S55>'  : 'decouplante/Robot_controller/PID Controller1/Integrator'
 * '<S56>'  : 'decouplante/Robot_controller/PID Controller1/Integrator ICs'
 * '<S57>'  : 'decouplante/Robot_controller/PID Controller1/N Copy'
 * '<S58>'  : 'decouplante/Robot_controller/PID Controller1/N Gain'
 * '<S59>'  : 'decouplante/Robot_controller/PID Controller1/P Copy'
 * '<S60>'  : 'decouplante/Robot_controller/PID Controller1/Parallel P Gain'
 * '<S61>'  : 'decouplante/Robot_controller/PID Controller1/Reset Signal'
 * '<S62>'  : 'decouplante/Robot_controller/PID Controller1/Saturation'
 * '<S63>'  : 'decouplante/Robot_controller/PID Controller1/Saturation Fdbk'
 * '<S64>'  : 'decouplante/Robot_controller/PID Controller1/Sum'
 * '<S65>'  : 'decouplante/Robot_controller/PID Controller1/Sum Fdbk'
 * '<S66>'  : 'decouplante/Robot_controller/PID Controller1/Tracking Mode'
 * '<S67>'  : 'decouplante/Robot_controller/PID Controller1/Tracking Mode Sum'
 * '<S68>'  : 'decouplante/Robot_controller/PID Controller1/postSat Signal'
 * '<S69>'  : 'decouplante/Robot_controller/PID Controller1/preSat Signal'
 * '<S70>'  : 'decouplante/Robot_controller/PID Controller1/Anti-windup/Passthrough'
 * '<S71>'  : 'decouplante/Robot_controller/PID Controller1/D Gain/Internal Parameters'
 * '<S72>'  : 'decouplante/Robot_controller/PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S73>'  : 'decouplante/Robot_controller/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S74>'  : 'decouplante/Robot_controller/PID Controller1/I Gain/Internal Parameters'
 * '<S75>'  : 'decouplante/Robot_controller/PID Controller1/Ideal P Gain/Passthrough'
 * '<S76>'  : 'decouplante/Robot_controller/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S77>'  : 'decouplante/Robot_controller/PID Controller1/Integrator/Discrete'
 * '<S78>'  : 'decouplante/Robot_controller/PID Controller1/Integrator ICs/Internal IC'
 * '<S79>'  : 'decouplante/Robot_controller/PID Controller1/N Copy/Disabled'
 * '<S80>'  : 'decouplante/Robot_controller/PID Controller1/N Gain/Internal Parameters'
 * '<S81>'  : 'decouplante/Robot_controller/PID Controller1/P Copy/Disabled'
 * '<S82>'  : 'decouplante/Robot_controller/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S83>'  : 'decouplante/Robot_controller/PID Controller1/Reset Signal/Disabled'
 * '<S84>'  : 'decouplante/Robot_controller/PID Controller1/Saturation/Passthrough'
 * '<S85>'  : 'decouplante/Robot_controller/PID Controller1/Saturation Fdbk/Disabled'
 * '<S86>'  : 'decouplante/Robot_controller/PID Controller1/Sum/Sum_PID'
 * '<S87>'  : 'decouplante/Robot_controller/PID Controller1/Sum Fdbk/Disabled'
 * '<S88>'  : 'decouplante/Robot_controller/PID Controller1/Tracking Mode/Disabled'
 * '<S89>'  : 'decouplante/Robot_controller/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S90>'  : 'decouplante/Robot_controller/PID Controller1/postSat Signal/Forward_Path'
 * '<S91>'  : 'decouplante/Robot_controller/PID Controller1/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_decouplante_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
