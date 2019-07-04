/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "random.h"
double random(int iseed){
    int hi,lo,test;
    const int a = 16807;
    const int m = 2147483647;
    const int q = 127773;
    const int r = 2836;
    hi = int(iseed/q);
    lo = iseed%q;
    test = a*lo - r*hi;
    if(test > 0)
        iseed = test;
    else
        iseed = test + m;
    double res = double(iseed)/double(m);
    return res;
}