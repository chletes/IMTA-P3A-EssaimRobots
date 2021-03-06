/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controllers.cpp
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
#include <Arduino.h>
#include "Controllers.h"

byte measure_flag = LOW;
// float x_ref;                          /* '<Root>/x' == hh_target_X  */
// float y_ref;                          /* '<Root>/y' == hh_target_Y  */
// float x_feedback;                     /* '<Root>/x1' == hh_actual_X */
// float y_feedback;                     /* '<Root>/y1' == hh_actual_Y */
float theta = 0;                          /* '<Root>/theta ' */
float v_center;                       /* '<Root>/v' */
float Vd_t;                           /* '<Root>/capteur Vd' */
float Vg_t;                           /* '<Root>/capteur Vg' */
float Vd;                             /* '<Root>/Consigne Vd' */
float Vg;                             /* '<Root>/Consigne Vg' */
float Ti=0;
float Tf;

PIDController pidg;
PIDController pidd;
PIDController pid1;
PIDController pid2;
#if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
extern  Zumo32U4Encoders  encoder;
extern  Zumo32U4Motors  motors;
#endif

void setup_Velocity_PID(){
  pidg.begin();          // initialize the PID instance
  pidg.tune(Kp, Ki, Kd);    // Tune the PID, arguments: kP, kI, kD
  pidg.limit(-255, 255);    // Limit the PID output between 0 and 255, this is important to get rid of integral windup!
  pidd.begin();          
  pidd.tune(Kp, Ki, Kd); 
  pidd.limit(-255, 255);

}
void update_theta_v(float Vd_t, float Vg_t, float dt){
  theta += (Vd_t - Vg_t)/L *dt;
  #if VELOCITY_PID_DEBUG && defined(__AVR_ATmega2560__) // Arduino Mega 2560
  Serial.print("Velocity Controller \t -> dt: \t");
  Serial.println(dt);
  Serial.print("Velocity Controller \t -> theta: \t");
  Serial.println(theta);
  #endif
}
void velocity_PID(){
  pidg.setpoint(Vg*400/42);    // The "goal" the PID controller tries to "reach"
  pidd.setpoint(Vd*400/42);    // The "goal" the PID controller tries to "reach"
  Tf=millis();
  float Time = (Tf-Ti)/1000;
  #if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
    Vg_t=encoder.getCountsAndResetLeft()*2*Pi*R/(100*12*Time)+0.01;
    Vd_t=encoder.getCountsAndResetRight()*2*Pi*R/(100*12*Time)+0.01;
  #elif defined(__AVR_ATmega2560__) // Arduino Mega 2560
    Vg_t = 1;
    Vd_t = 3;
  #endif
  Ti=millis();
  update_theta_v(Vd_t, Vg_t, Time);
  int output_g = pidg.compute(Vg_t);    // Let the PID compute the value, returns the optimal output
  int output_d = pidd.compute(Vd_t);    // Let the PID compute the value, returns the optimal output
  #if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
  motors.setLeftSpeed(output_g);  
  motors.setRightSpeed(output_d);
  #elif VELOCITY_PID_DEBUG && defined(__AVR_ATmega2560__) // Arduino Mega 2560
  Serial.print("Velocity Controller \t -> output_g: \t");
  Serial.print(output_g);
  Serial.print("\t output_d: ");
  Serial.println(output_d);
  #endif
  delay(500);
}
/* System initialize for atomic system: '<Root>/Robot_controller' */
void uncoupling_controller_init(DW_uncouping_controller_T *localDW){
  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = 0.083;
  pid1.begin();          // initialize the PID instance
  pid1.tune(P_t, I_t, N_t*D_t);    // Tune the PID, arguments: kP, kI, kD 
  pid1.limit(-255, 255);    // Limit the PID output between 0 and 255, this is important to get rid of integral windup!

  pid2.begin();          // initialize the PID instance
  pid2.tune(P_t, I_t,N_t*D_t);    // Tune the PID, arguments: kP, kI, kD  
  pid2.limit(-255, 255);    // Limit the PID output between 0 and 255, this is important to get rid of integral windup!
}

/* Output and update for atomic system: '<Root>/Robot_controller' */
//void uncoupling_controller(float *rtu_x_ref, float *rtu_y_ref, float
//  *rtu_x_feedback, float *rtu_y_feedback, float rtu_theta, float *rtu_v_center, float Ts,
//  float *rty_Vd, float *rty_Vg, DW_uncouping_controller_T *localDW)
//{
//  real32_T rtb_Product;
//  real32_T rtb_Sum;
//  real32_T rtb_FilterCoefficient;
//  real32_T rtb_Sum1;
//  real32_T rtb_FilterCoefficient_l;
//  real32_T rtb_Sum_o;
//  real32_T rtb_Sum_l;
//  real32_T rtb_Product_tmp;
//  real32_T rtb_Product_tmp_0;
//
//  /* Saturate: '<S1>/Saturation1' incorporates:
//   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
//   */
//  if (localDW->DiscreteTimeIntegrator_DSTATE > Vm) {
//    *rtu_v_center = Vm;
//  } else if (localDW->DiscreteTimeIntegrator_DSTATE < -Vm) {
//    *rtu_v_center = -Vm;
//  } else {
//    *rtu_v_center = localDW->DiscreteTimeIntegrator_DSTATE;
//  }
//
//  /* End of Saturate: '<S1>/Saturation1' */
//
//  /* Sum: '<S1>/Sum' */
//  rtb_Sum = *rtu_x_ref - *rtu_x_feedback;
//
//  /* Gain: '<S36>/Filter Coefficient' incorporates:
//   *  DiscreteIntegrator: '<S28>/Filter'
//   *  Gain: '<S27>/Derivative Gain'
//   *  Sum: '<S28>/SumD'
//   */
//  rtb_FilterCoefficient = (D_t * rtb_Sum - localDW->Filter_DSTATE) * N_t;
//
//  /* Sum: '<S42>/Sum' incorporates:
//   *  DiscreteIntegrator: '<S33>/Integrator'
//   *  Gain: '<S38>/Proportional Gain'
//   */
//  rtb_Sum_o = (P_t * rtb_Sum + localDW->Integrator_DSTATE) +
//    rtb_FilterCoefficient;
//
//  /* Sum: '<S1>/Sum1' */
//  rtb_Sum1 = *rtu_y_ref - *rtu_y_feedback;
//
//  /* Gain: '<S80>/Filter Coefficient' incorporates:
//   *  DiscreteIntegrator: '<S72>/Filter'
//   *  Gain: '<S71>/Derivative Gain'
//   *  Sum: '<S72>/SumD'
//   */
//  rtb_FilterCoefficient_l = (D_t * rtb_Sum1 - localDW->Filter_DSTATE_c) * N_t;
//
//  /* Sum: '<S86>/Sum' incorporates:
//   *  DiscreteIntegrator: '<S77>/Integrator'
//   *  Gain: '<S82>/Proportional Gain'
//   */
//  rtb_Sum_l = (P_t * rtb_Sum1 + localDW->Integrator_DSTATE_g) +
//    rtb_FilterCoefficient_l;
//
//  /* Fcn: '<S1>/linearisation calcul u2' incorporates:
//   *  Fcn: '<S1>/linearisation calcul u1'
//   */
//  rtb_Product_tmp = cos(rtu_theta);
//  rtb_Product_tmp_0 = sin(rtu_theta);
//
//  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
//   *  Fcn: '<S1>/linearisation calcul u1'
//   */
//  localDW->DiscreteTimeIntegrator_DSTATE += (rtb_Product_tmp * rtb_Sum_o +
//    rtb_Product_tmp_0 * rtb_Sum_l) * Ts;//Velocity
//  *rtu_v_center+=(rtb_Product_tmp * rtb_Sum_o + rtb_Product_tmp_0 * rtb_Sum_l) * Ts;
//
//  /* Product: '<S1>/Product' incorporates:
//   *  Constant: '<S1>/L//2'
//   *  Fcn: '<S1>/linearisation calcul u2'
//   */
//  rtb_Product = (-rtb_Product_tmp_0 / *rtu_v_center * rtb_Sum_o + rtb_Product_tmp
//                 / *rtu_v_center * rtb_Sum_l) * (L / 2.0);//theta_p *L/2
//
//
//  /* Sum: '<S1>/Sum2' */
//  *rty_Vd = *rtu_v_center+ rtb_Product;
//
//  /* Sum: '<S1>/Sum3' */
//  *rty_Vg = *rtu_v_center- rtb_Product;
//  /* Update for DiscreteIntegrator: '<S33>/Integrator' incorporates:
//   *  Gain: '<S30>/Integral Gain'
//   */
//  localDW->Integrator_DSTATE += I_t * rtb_Sum * Ts;
//
//  /* Update for DiscreteIntegrator: '<S28>/Filter' */
//  localDW->Filter_DSTATE += Ts * rtb_FilterCoefficient;
//
//  /* Update for DiscreteIntegrator: '<S77>/Integrator' incorporates:
//   *  Gain: '<S74>/Integral Gain'
//   */
//  localDW->Integrator_DSTATE_g += I_t * rtb_Sum1 * Ts;
//
//  /* Update for DiscreteIntegrator: '<S72>/Filter' */
//  localDW->Filter_DSTATE_c += Ts * rtb_FilterCoefficient_l;
//}




void uncoupling_controller(float *rtu_x_ref, float *rtu_y_ref, float
  *rtu_x_feedback, float *rtu_y_feedback, float rtu_theta, float *rtu_v_center, float Ts,
  float *rty_Vd, float *rty_Vg, DW_uncouping_controller_T *localDW){
  //Intern parameters:
  
  real32_T rtb_Product;
  real32_T rtb_Sum;
  real32_T error_x;
  real32_T rtb_FilterCoefficient;
  real32_T rtb_Sum1;
  real32_T rtb_FilterCoefficient_l;
  real32_T rtb_Sum_o;
  real32_T rtb_Sum_l;
  real32_T rtb_Product_tmp;
  real32_T rtb_Product_tmp_0;
  
  //Pid for x_ref and x_feedback:
  pid1.setpoint(*rtu_x_ref);    // The "goal" the PID controller tries to "reach"
  float output_1 = pid1.compute(*rtu_x_feedback);
  //Pid for y_ref and y_feedback:
  pid2.setpoint (*rtu_y_ref);// The "goal" the PID controller tries to "reach"
  float output_2 = pid2.compute(*rtu_y_feedback);

  if((*rtu_y_feedback- *rtu_y_ref)<0.01 && (*rtu_x_feedback- *rtu_x_ref)<0.01){
    *rty_Vd =0;
    *rty_Vg =0;
    }
  /* Saturate: '<S1>/Saturation1' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  if (*rty_Vd> Vm) {
    *rty_Vd = Vm;
  } else if (*rty_Vd < -Vm) {
    *rty_Vd = -Vm;
  }
  if (*rty_Vg> Vm) {
    *rty_Vg = Vm;
  } else if (*rty_Vg < -Vm) {
    *rty_Vg = -Vm;
  }

  #if DECOUPLING_CONTROLLER_DEBUG && defined(__AVR_ATmega2560__) // Arduino Mega 2560
  Serial.print("Decoupling Controller \t -> v_center: \t");
  Serial.println(*rtu_v_center);
  #endif

  /* End of Saturate: '<S1>/Saturation1' */


  /* Fcn: '<S1>/linearisation calcul u2' incorporates:
   *  Fcn: '<S1>/linearisation calcul u1'
   */
  rtb_Product_tmp = cos(rtu_theta);
  rtb_Product_tmp_0 = sin(rtu_theta);

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  Fcn: '<S1>/linearisation calcul u1'
   */
  localDW->DiscreteTimeIntegrator_DSTATE += (rtb_Product_tmp * output_1 +
    rtb_Product_tmp_0 * output_2) * Ts;//Velocity
    
  *rtu_v_center+=(rtb_Product_tmp * output_1 + rtb_Product_tmp_0 * output_2) * Ts;
  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/L//2'
   *  Fcn: '<S1>/linearisation calcul u2'
   */
  rtb_Product = (-rtb_Product_tmp_0 / *rtu_v_center * output_1 + rtb_Product_tmp
                 / *rtu_v_center * output_2) * (L / 2.0);//theta_p *L/2


  /* Sum: '<S1>/Sum2' */
  *rty_Vd = *rtu_v_center+ rtb_Product;

  /* Sum: '<S1>/Sum3' */
  *rty_Vg = *rtu_v_center- rtb_Product;

  
    }
