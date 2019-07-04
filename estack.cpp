/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "energy.h"
#include "rnavar.h"

void estack(int iseq[], int i, int j, int ip, int jp, int n, float es){
    int list[4];
    
    es = 0.0e0;
    
    list[0] = iseq[i];
    list[1] = iseq[j];
    list[2] = iseq[ip];
    list[3] = iseq[jp];
    
    tstack(list, es);
}