/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "rnavar.h"
#include "energy.h"
void ehair(int iseq[], int i, int j, int n, float eh){
    
    
    // =  =  = VARIABLES =  =  = //
    
    int list[6];
    int k, ic, n1;
    
    float x, c;
    float elh[] = {0.00e0, 0.00e0, 5.70e0, 5.60e0, 5.60e0, 5.40e0, 5.90e0, 5.60e0, 6.40e0, 6.50e0, 6.60e0, 6.70e0, 6.80e0, 6.90e0, 6.90e0, 7.00e0, 7.10e0, 7.10e0, 7.20e0, 7.20e0, 7.30e0, 7.30e0, 7.40e0, 7.40e0, 7.50e0, 7.50e0, 7.50e0, 7.60e0, 7.60e0, 7.70e0 };
       
    eh = 0.0e0;
    n1 = j - i - 1;
    
    c = 1.750e0/float(beta);
    
    
    // =  =  = TERM 1 - -> Entropic Term =  =  = //
    
    if (n1 > 30){
        x = float(n1)/30.0e0;
        x = c*log(x);
        
        eh = elh[29] + x;
        
    } 
    else{        
        eh = elh[n1];
    }    
    // =  =  = TERM 2 - -> Stacking Energy =  =  = //
    
    if (n1 > 3){
        
        // 5" (i) A X (i+1) LOOPundefinedundefined
        // 3" (j) U Y (j-1) LOOPundefinedundefined
        
        list[0] = iseq[i];
        list[1] = iseq[j];
        list[2] = iseq[i + 1];
        list[4] = iseq[j - 1];
        
        tstackh(list, eh);
        
    }
    
    
    // =  =  = TERM 3 - -> Bonuses =  =  = //
    
    // =  =  = Tetra - loop Bonus =  =  = //
    
    if (n1 == 4){
        
        list[0] = iseq[i];
        list[1] = iseq[i + 1];
        list[2] = iseq[i + 2];
        list[3] = iseq[i + 3];
        list[4] = iseq[i + 4];
        list[5] = iseq[i + 5];
        
        tloop(list, eh);    
    }
    
    // =  =  = GGG Hairpin Bonus =  =  = //
    
    if (iseq[i] == 3 && iseq[j] == 4){
        ic = 0;
        k = (1>i-2)? 1:i-2;
        for(;k<i;k++){
            if(iseq[k] == 3) 
                ic = ic + 1;
        }
        if (ic == 3) eh = eh - 2.20e0;
    }
    
    // =  =  = TERM 4 - -> Penalties =  =  = //
    // =  =  = Poly C Penalty =  =  = //
    ic = 0;
    for(k=i+1;k<j-1;k++){
        if (iseq[k] == 2) 
            ic = ic + 1;
    }
    if (ic == n1){
        if (n1 == 3){
            eh = eh + 1.40e0;
        } 
        else{
            eh = eh + 1.60e0;
            eh = eh + 0.30e0*float(ic);
        }
    }
    
    // =  =  = A - U/G - U closing a Tri - loop =  =  = //
    if (n1 == 3){
        if (iseq[i] == 4) eh = eh + eau;
        if (iseq[j] == 4) eh = eh + eau;
    }

}


/*
#include "rnavar.h"
void ehair(int iseq[], int i, int j, int n, float eh){
    
    //USE RNAvar, ONLY : eau, beta;
    
    // implicit NONE
    
    // =  =  = ARGUMENTS =  =  = //
    
    // =  =  = VARIABLES =  =  = //
    
    int list[6];
    int k, ic, n1;
    
    float x, c;
    float elh[30] = {0.00e0, 0.00e0, 5.70e0, 5.60e0, 5.60e0, 5.40e0, 5.90e0, 5.60e0, 6.40e0, 6.50e0, 6.60e0, 6.70e0, 6.80e0, 6.90e0, 6.90e0, 7.00e0, 7.10e0, 7.10e0, 7.20e0, 7.20e0, 7.30e0, 7.30e0, 7.40e0, 7.40e0, 7.50e0, 7.50e0, 7.50e0, 7.60e0, 7.60e0, 7.70e0};
    
    
    eh = 0.0e0;
    
    n1 = j - i - 1;
    
    c = 1.750e0/float(beta);
    
    
    // =  =  = TERM 1 - -> Entropic Term =  =  = //
    
    if (n1 > 29){
        
        x = float(n1)/30.0e0;
        x = c*log(x);
        
        eh = elh[29] + x;
        
    } 
    else{
        eh = elh[n1];
    }
    
    
    // =  =  = TERM 2 - -> Stacking Energy =  =  = //
    
    if (n1 > 3) 
    {
        
        // 5" (i) A X (i+1) LOOPundefinedundefined
        // 3" (j) U Y (j-1) LOOPundefinedundefined
        
        list[0] = iseq[i];
        list[1] = iseq[j];
        list[2] = iseq[i + 1];
        list[3] = iseq[j - 1];
        
        tstackh(list, eh);
        
    }
    
    
    // =  =  = TERM 3 - -> Bonuses =  =  = //
    
    // =  =  = Tetra - loop Bonus =  =  = //
    
    if (n1 == 4){
        
        list[0] = iseq[i];
        list[1] = iseq[i + 1];
        list[2] = iseq[i + 2];
        list[3] = iseq[i + 3];
        list[4] = iseq[i + 4];
        list[5] = iseq[i + 5];
        
        tloop(list, eh);
        
    }
    
    // =  =  = GGG Hairpin Bonus =  =  = //
    
    if (iseq[i] == 3 && iseq[j] == 4){
        
        ic = 0;
        k = (1>i-2)? 1:i-2;
        for(;k<i;k++){
            if(iseq[k] == 3) ic = ic + 1;
        }
        if (ic == 3) eh = eh - 2.20e0;
    }
    // =  =  = TERM 4 - -> Penalties =  =  = //
    // =  =  = Poly C Penalty =  =  = //
    
    ic = 0;
    for(k=i+1;k<j-1;k++){
        if(iseq[k] == 2) ic++;
    }
    if (ic == n1){
        if (n1 == 3){
            eh = eh + 1.40e0;
        }
        else{
            eh = eh + 1.60e0;
            eh = eh + 0.30e0*float(ic);
        }
    }
    // =  =  = A - U/G - U closing a Tri - loop =  =  = //
    if (n1 == 3){
        if (iseq[i] == 4) eh = eh + eau;
        if (iseq[j] == 4) eh = eh + eau;
    }
}
*/


