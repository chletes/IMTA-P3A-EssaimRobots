/*
 * @Descripttion: 
 * @version: 
 * @Author: Wentao GONG
 * @Date: 2022-03-03 15:32:13
 * @LastEditors: Wentao GONG
 * @LastEditTime: 2022-03-03 17:17:05
 */
#include<iostream>
#include "decouplante.h"
using namespace std;

int main()
{
    x_ref = 1;
    y_ref = 1;
    cout << "y_feedback " << y_feedback << endl;
    decouplante_initialize();
    decouplante_step();
    cout << "Vd = " << decouplante_Y.Vd << endl;
    cout << "Vg = " << decouplante_Y.Vg << endl;
    return 0;
}