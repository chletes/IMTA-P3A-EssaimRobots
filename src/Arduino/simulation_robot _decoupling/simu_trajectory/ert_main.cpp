/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
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

#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "Model_robot.h"               /* Model's header file */
#include "rtwtypes.h"
#include <time.h>
#include <iostream>
using namespace std;          
#include <unistd.h>


#include<iostream>
#include <fstream>
#include "trajectory.h"

#define amax    1.0
#define vmax    3.0 
#define Tc      0.01
#define step    0.1
/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model for base rate */
  Model_robot_step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
#if  0

int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Initialize model */
  decoupling_initialize();
  Model_robot_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.001 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep();
   */
  int i = 3000;
  while (i) {
    /*  Perform other application tasks here */
    x_ref = 1;
    y_ref = 1;
    x_feedback = Model_robot_Y.x1;                    
    y_feedback = Model_robot_Y.y1;                    
    theta = Model_robot_Y.theta;  
    decoupling_step();
    Vd = decoupling_Y.Vd;                         
    Vg = decoupling_Y.Vg;
    Model_robot_step();

    usleep(1000);
    cout << "(" << Model_robot_Y.x1 << "," << Model_robot_Y.y1 << ") "<< endl;
    i--;
  }
  /* The option 'Remove error status field in real-time model data structure'
   * is selected, therefore the following code does not need to execute.
   */

  return 0;
}
#endif
/*
 * File trailer for generated code.
 *
 * [EOF]
 */

//Test with trajectory
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Initialize model */
  decoupling_initialize();
  Model_robot_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.001 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep();
   */

  //trajectory generation
  float start_x = 0.0;
  float end_x = 5.0;
  float delta_x = end_x - start_x;
  
  float start_y = 0.0;
  float end_y = 5.0;
  float delta_y = end_y - start_y;

  float T,tau;
  mpar(delta_x,amax,vmax,Tc,&T,&tau);
  float t = 0;

  ofstream taj_in, taj_out;
  taj_in.open("traj_input.dat", ios::trunc);
  taj_out.open("traj_output.dat", ios::trunc);

  while(t < T+tau)
  {
    float al = sfun(t,T,tau);  // Interpolation
    float x = al*end_x + (1-al)*start_x;
    float y = al*end_y + (1-al)*start_y;
    t+=step;
    
    x_ref = x;
    y_ref = y;

    int i = 3000;
    while (i) 
    {
      /*  Perform other application tasks here */
      x_feedback = Model_robot_Y.x1;                    
      y_feedback = Model_robot_Y.y1;                    
      theta = Model_robot_Y.theta;  
      decoupling_step();
      Vd = decoupling_Y.Vd;                         
      Vg = decoupling_Y.Vg;
      Model_robot_step();

      usleep(1000);
      i--;
    }
    cout << "position_ref (" << x_ref << "," << y_ref << ") " ;
    cout << " position_real (" << Model_robot_Y.x1 << "," << Model_robot_Y.y1 << ") "<< endl;
    
    taj_in << " (" << x_ref << ", " << y_ref << ") " << endl;
    taj_out << " (" << Model_robot_Y.x1 << ", " << Model_robot_Y.y1 << ") "<< endl;
  }
  taj_in.close();
  taj_out.close();
  return 0;
}