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

  int i = 10000;
  while (i) {
    /*  Perform other application tasks here */
    x_ref = 10;
    y_ref = 10;
    x_feedback = Model_robot_Y.x1;                    
    y_feedback = Model_robot_Y.y1;                    
    theta = Model_robot_Y.theta;  
    //cout << "In: "<<  x_ref   << ", " << y_ref  << ", "<< x_feedback  << ", "<< y_feedback << ", " << theta  << ", "<< Vd << ", " << Vg << endl;
    //cout << decouplante_B.Robot_controller.addantiwindup << endl;
    //cout << 
    decoupling_step();
    Vd = decoupling_Y.Vd;                         
    Vg = decoupling_Y.Vg;
    //cout <<  "vitess: " << Vd << "," << Vg << endl;
    Model_robot_step();

    usleep(1000*10);
    cout << "(" << Model_robot_Y.x1 << "," << Model_robot_Y.y1 << ") "<< endl;
    i--;
  }

  /* The option 'Remove error status field in real-time model data structure'
   * is selected, therefore the following code does not need to execute.
   */
#if 0

  /* Disable rt_OneStep() here */

  /* Terminate model */
  Model_robot_terminate();

#endif

  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
