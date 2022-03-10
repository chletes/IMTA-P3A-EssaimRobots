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
 * File: Controllers.h
 *
 * Code generated for Simulink model 'uncoupling'.
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

#ifndef Controllers_h
#define Controllers_h
#include "Arduino.h"
#include <Zumo32U4.h> 
#include <Zumo32U4Encoders.h>
#include <Wire.h>
#include <PIDController.h>
#include <math.h>                               /* uncoupling_COMMON_INCLUDES_ */

extern  byte measure_flag;
// extern  float x_ref;                          /* '<Root>/x' == hh_target_X  */
// extern  float y_ref;                          /* '<Root>/y' == hh_target_Y  */
// extern  float x_feedback;                     /* '<Root>/x1' == hh_actual_X */
// extern  float y_feedback;                     /* '<Root>/y1' == hh_actual_Y */
extern  float theta;                          /* '<Root>/theta ' */
extern  float v_center;                       /* '<Root>/v' */
extern  float Vd_t;                           /* '<Root>/capteur Vd' */
extern  float Vg_t;                           /* '<Root>/capteur Vg' */
extern  float Vd;                             /* '<Root>/Consigne Vd' */
extern  float Vg;                             /* '<Root>/Consigne Vg' */
extern  float Ti;
extern  float Tf;

extern  PIDController  pidg;
extern  PIDController  pidd;
extern  Zumo32U4Encoders  Encoder;
extern  Zumo32U4Motors  motors;

#define Kp 100  //Propotional constant260
#define Ki 0 //Integral constant
#define Kd 0 //Derivative constant
#define R 0.03 // ray of wheel
#define Pi 3.141592653589

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
#define L  0.06                     
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
#define Vm  400.0                         // Variable: Vm 

typedef float real32_T;

/* Block states (default storage) for system '<Root>/Robot_controller' */
typedef struct {
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  real32_T Integrator_DSTATE;            /* '<S33>/Integrator' */
  real32_T Filter_DSTATE;                /* '<S28>/Filter' */
  real32_T Integrator_DSTATE_g;          /* '<S77>/Integrator' */
  real32_T Filter_DSTATE_c;              /* '<S72>/Filter' */
} DW_uncouping_controller_T;

extern void setup_Velocity_PID();
extern void update_theta_v(float Vd_t, float Vg_t, float dt);
extern void velocity_PID();
extern void uncoupling_controller_init(DW_uncouping_controller_T
  *localDW);

extern void uncoupling_controller(real32_T *rtu_x_ref, real32_T *rtu_y_ref,
  real32_T *rtu_x_feedback, real32_T *rtu_y_feedback, real32_T rtu_theta, real32_T
  *rtu_v_center, real32_T Ts, real32_T *rty_Vd, real32_T *rty_Vg, DW_uncouping_controller_T *
  localDW);

#endif                                 /* RTW_HEADER_Controllers_h_ */
