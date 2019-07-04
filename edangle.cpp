/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "energy.h"
#include "rnavar.h"

void edangle(int iseq[], int i, int j, int k, int n, float ed){
    // =  =  = VARIABLES =  =  = //
    
    int list[3];
    
    
    ed = 0.0e0;
    
    if (k < 0) return;
    if (k > n-1) return;
    
    
    if (k == i + 1){
        
        //5" (i) A X (k) 3"
        //3" (j) U       5"
        
        list[0] = iseq[i];
        list[1] = iseq[j];
        list[2] = iseq[k];
        
        tdangle3(list, ed);
        
    }
    
    if (k == j - 1){
        
        //5" (i) A       3"
        //3" (j) U X (k) 5"
        
        list[0] = iseq[i];
        list[1] = iseq[j];
        list[2] = iseq[k];
        
        tdangle5(list, ed);
        
    }
    
    if (k == j + 1){
        
        //5"       A (i) 3"
        //3" (k) X U (j) 5"
        
        list[0] = iseq[j];
        list[1] = iseq[i];
        list[2] = iseq[k];
        
        tdangle3(list, ed);
        
    }
    
    if (k == i - 1){
        
        //5" (k) X A (i) 3"
        //3"       U (j) 5"
        
        list[0] = iseq[j];
        list[1] = iseq[i];
        list[2] = iseq[k];
        
        tdangle5(list, ed);
        
    }    
}




