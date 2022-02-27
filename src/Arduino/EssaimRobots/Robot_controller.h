/*
 * @Descripttion: 
 * @version: 
 * @Author: Wentao GONG
 * @Date: 2022-02-10 21:13:45
 * @LastEditors: Wentao GONG
 * @LastEditTime: 2022-02-27 23:06:51
 */
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Robot_controller.h
 *
 * Code generated for Simulink model 'decouplante'.
 *
 * Model version                  : 1.12
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Wed Feb 16 20:57:46 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Robot_controller_h_
#define RTW_HEADER_Robot_controller_h_
#include <math.h>                               /* decouplante_COMMON_INCLUDES_ */

#define D_t  42.0                     
                                        /* Variable: D_t
                                        * Referenced by:
                                        *   '<S27>/Derivative Gain'
                                        *   '<S71>/Derivative Gain'
                                        */
#define I_t  0.0                      
                                        /* Variable: I_t
                                        * Referenced by:
                                        *   '<S30>/Integral Gain'
                                        *   '<S74>/Integral Gain'
                                        */
#define L  0.085                      
                                        /* Variable: L
                                        * Referenced by: '<S1>/L//2'
                                        */
#define N_t  20.0                     
                                        /* Variable: N_t
                                        * Referenced by:
                                        *   '<S36>/Filter Coefficient'
                                        *   '<S80>/Filter Coefficient'
                                        */
#define P_t  82.0                     
                                        /* Variable: P_t
                                        * Referenced by:
                                        *   '<S38>/Proportional Gain'
                                        *   '<S82>/Proportional Gain'
                                        */
#define Vm  5.0                         // Variable: Vm 

typedef float real32_T;

/* Block states (default storage) for system '<Root>/Robot_controller' */
typedef struct {
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  real32_T Integrator_DSTATE;            /* '<S33>/Integrator' */
  real32_T Filter_DSTATE;                /* '<S28>/Filter' */
  real32_T Integrator_DSTATE_g;          /* '<S77>/Integrator' */
  real32_T Filter_DSTATE_c;              /* '<S72>/Filter' */
} DW_Robot_controller_decouplan_T;



extern void decouplan_Robot_controller_Init(DW_Robot_controller_decouplan_T
  *localDW);

extern void decouplante_Robot_controller(real32_T rtu_x_ref, real32_T rtu_y_ref,
  real32_T rtu_x_feedback, real32_T rtu_y_feedback, real32_T rtu_theta, real32_T
  rtu_v_center, real32_T Ts, real32_T *rty_Vd, real32_T *rty_Vg, DW_Robot_controller_decouplan_T *
  localDW);

#endif                                 /* RTW_HEADER_Robot_controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
