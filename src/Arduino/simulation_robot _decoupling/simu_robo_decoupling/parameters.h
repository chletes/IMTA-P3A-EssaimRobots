/*
 * @Descripttion: Add some constant parameters here 
 * @version: 
 * @Author: Wentao GONG
 * @Date: 2022-03-10 18:31:32
 * @LastEditors: Wentao GONG
 * @LastEditTime: 2022-03-10 19:00:46
 */
#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

/* Exported PID block parameters */
#define P_t  0.007 
#define I_t  0.0001 
#define D_t  0.186    
                            
#define N_t  1.5    //filter parameter    

#define L    8.5     //length of robot(cm)
                     
#define Vm   40      //max speed (cm/s) of robot

#define Ts   0.1     //sampling time

#endif