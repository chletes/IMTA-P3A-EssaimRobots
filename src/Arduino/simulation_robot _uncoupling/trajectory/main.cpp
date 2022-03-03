/*
 * @Descripttion: 
 * @version: 
 * @Author: Wentao GONG
 * @Date: 2022-03-03 01:41:30
 * @LastEditors: Wentao GONG
 * @LastEditTime: 2022-03-03 22:20:21
 */
#include<iostream>
#include <fstream>
#include "trajectory.h"

#define amax    1.0
#define vmax    3.0 
#define Tc      0.01
#define step      0.1
using namespace std;

int main()
{
    float start_x = 0.0;
    float end_x = 5;
    float delta_x = end_x - start_x;
    
    float start_y = 0.0;
    float end_y = 5;
    float delta_y = end_y - start_y;

    float T,tau;
    mpar(delta_x,amax,vmax,Tc,&T,&tau);


    ofstream outfile;
    outfile.open("position.dat");
    float t = 0;
    while(t <= T+tau)
    {
        float al = sfun(t,T,tau);  // Interpolation
        float x = al*end_x + (1-al)*start_x;
        float y = al*end_y + (1-al)*start_y;
        outfile << "(" << x << "," << y << ") "<< endl;
        t+=step;
    }
    outfile.close();
    cout << "hello" << endl;
    return 0;
    
}