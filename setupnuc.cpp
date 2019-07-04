/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "rnavar.h"
using namespace std;
vector <double> pnuc;
void setupnuc(int n){
    double x, xi, e;
    const double c = 0.1785714290e0;
    //const double c2= 3.9274668195d8;  !rate in (1/s)
    const double c2= 3.9274668195e2;  //rate in (1/uS)
    const double xp= 4.0000000000e0;

    pnuc.resize(n);
    for(int i=0;i<n;i++)
        pnuc[i] = 0.0e0;
    for(int i=4;i<n;i++){
        x = c * double(i-1);
        xi = 1.0e0 / x;
        
        if(x <= xp){
            e = -7.0270e0 * xi + 0.4920e0 * x;
            x = 84.90e0 * pow(xi,5.50e0);
            x = c2 * x / beta;
            
            pnuc[i] = x * exp(e);
        }
        else{
            x = xi * xi;
            e = 1.0e0 - 0.6250e0 * xi - 0.12343750e0 * x;
            x = c2 * x / beta;

            pnuc[i] = x * e;
        }
    }
}