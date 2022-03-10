/*
 * @Descripttion: 
 * @version: 
 * @Author: Wentao GONG
 * @Date: 2022-03-03 15:32:13
 * @LastEditors: Wentao GONG
 * @LastEditTime: 2022-03-09 22:37:54
 */
#include<iostream>
#include "decoupling.h"
using namespace std;

int main()
{
    x_ref = 1;
    y_ref = 1;
    cout << "y_feedback " << y_feedback << endl;
    decoupling_initialize();
    decoupling_step();
    cout << "Vd = " << decoupling_Y.Vd << endl;
    cout << "Vg = " << decoupling_Y.Vg << endl;
    return 0;
}