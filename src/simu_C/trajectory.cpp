/*
 * @Descripttion: 
 * @version: 
 * @Author: Wentao GONG
 * @Date: 2022-03-03 01:15:21
 * @LastEditors: Wentao GONG
 * @LastEditTime: 2022-03-03 20:06:15
 */
#include "trajectory.h"
#include<math.h>

/*   dq  - abs. displacement; 
*    qtmax,qttmax - max. velocity and acceleration;
*    Tc  - controller cycle time;
*/
void mpar(float dq, float qtmax, float qttmax, float Tc, float *T, float *tau )
{
    int k =4;//4 point at leat
    float T_min =  k*Tc; 
    float tau_min = k*Tc; 
    *T = dq/qtmax; 
    *tau = qtmax/qttmax;
    if(*T < *tau)
    {
        *tau = sqrt(dq/qttmax);
        *T = *tau;
    }

    *T = Tc*ceil(*T/Tc);
    *tau = Tc*ceil(*tau/Tc);

    if(*T < T_min)
    {
        *T = T_min;
    }    
    if(*tau < tau_min)
    {
        *tau = tau_min;
    }
}


float sfun(float t, float T, float tau)
{
    float s=0;
    if ((t>=0) && (t <= tau))
    {
         s = pow(t,2)/(2*T*tau);
    }
    if ((t>=tau) && (t <= T))
    {
        s = pow(tau,2)/(2*T*tau) + (t-tau)/T;
    }
    if ((t>=T) && (t <= T+tau))
    {
        s = 1-pow((t-T-tau),2)/(2*T*tau);
    }
    if (t > T+tau)
    {
        s=1;
    } 
    return s;   
}

