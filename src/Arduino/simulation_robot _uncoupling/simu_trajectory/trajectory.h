/*
 * @Descripttion: 
 * @version: 
 * @Author: Wentao GONG
 * @Date: 2022-03-03 01:15:10
 * @LastEditors: Wentao GONG
 * @LastEditTime: 2022-03-03 01:37:34
 */
#ifndef _TRAJECTORY_H
#define _TRAJECTORY_H
#define DELTA_T 0.1

/**
 * @author: Wentao GONG
 * @brief: Computing timing law parameters T, tau
 * @param {float} dq: abs. displacement
 * @param {float} qtmax: max. velocity 
 * @param {float} qttmax: max. acceleration
 * @param {float} Tc: controller cycle time
 * @param {float} *T 
 * @param {float} *tau: 
 * @return {*}
 */
void mpar(float dq, float qtmax, float qttmax, float Tc, float *T, float *tau );

/**
 * @author: Wentao GONG
 * @brief: generate trajectory according to time
 * @param {float} t
 * @param {float} T
 * @param {float} tau
 * @return {*}
 */
float sfun(float t, float T, float tau);
#endif