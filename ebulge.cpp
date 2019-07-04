/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


// --------------------------------------------
#include "rnavar.h"
#include "energy.h"
void ebulge(int iseq[], int i, int j, int ip, int jp, int n, float eb){
    // implicit NONE    
    // =  =  = VARIABLES =  =  = //
    
    int k, ibul, imin, imax;
    int n1, n2, nt, na, list[8];
    
    float x, c, f[4];
    
    float f[] = {0.50e0, 0.50e0, 0.50e0, 0.50e0};
    
    float elb[] = {3.80e0, 2.80e0, 3.20e0, 3.60e0, 4.00e0, 4.40e0, 4.60e0, 4.70e0, 4.80e0, 4.90e0, 5.00e0, 5.10e0, 5.20e0, 5.30e0, 5.40e0, 5.40e0, 5.50e0, 5.50e0, 5.60e0, 5.70e0, 5.70e0, 5.80e0, 5.80e0, 5.80e0, 5.90e0, 5.90e0, 6.00e0, 6.00e0, 6.00e0, 6.10e0};
    
    float eli[] = {0.00e0, 0.00e0, 0.00e0, 1.70e0, 1.80e0, 2.00e0, 2.20e0, 2.30e0, 2.40e0, 2.50e0, 2.60e0, 2.70e0, 2.80e0, 2.90e0, 3.00e0, 3.00e0, 3.10e0, 3.10e0, 3.20e0, 3.30e0, 3.30e0, 3.40e0, 3.40e0, 3.40e0, 3.50e0, 3.50e0, 3.60e0, 3.60e0, 3.60e0, 3.70e0};
    
    eb = 0.0e0;
    
    n1 = ip - i - 1;
    n2 = j - jp - 1;
    
    nt = n1 + n2;
    na = abs(n1 - n2);
    
    imin = (n1 < n2)? n1:n2;
    imax = (n1 > n2)? n1:n2;
    
    c = 1.750e0/float(beta);
    
    
    // =  =  = Get Buldge Type =  =  = //
    
    ibul = 6;
    if (n1 == 0 && n2 == 1) ibul = 0;
    if (n1 == 1 && n2 == 0) ibul = 0;
    if (n1 == 0 && n2 >= 2) ibul = 1;
    if (n1 >= 2 && n2 == 0) ibul = 1;
    if (n1 == 1 && n2 == 1) ibul = 2;
    if (n1 == 1 && n2 == 2) ibul = 3;
    if (n1 == 2 && n2 == 1) ibul = 4;
    if (n1 == 2 && n2 == 2) ibul = 5;
    
    
    // =  =  = TERM 1 - -> Entropic Term =  =  = //
    
    if (nt > 30){
        
        x = float(nt)/30.0e0;
        x = c*log(x);
        
        if (ibul <= 1) eb = elb[29] + x;
        if (ibul == 6) eb = eli[30] + x;
        
    } 
    else{
        
        if (ibul <= 1) eb = elb[nt];
        if (ibul == 6) eb = eli[nt];        
    }
    
    
    // =  =  = TERM 2 & 3 - -> Stacking Energy =  =  = //
    switch(ibul){
        case 0: 
            // 5" (i) A . X (ip) 3"
            // 3" (j) U   Y (jp) 5"
            list[0] = iseq[i];
            list[1] = iseq[j];
            list[2] = iseq[ip];
            list[3] = iseq[jp];
            tstack(list, eh);
            break;
            
        case 1: 
            // 5" (i) A .. X (ip) 3"
            // 3" (j) U    Y (jp) 5"
            // =  =  = Closing A - U/G - U Penalty =  =  = //
            if (iseq[i] == 4) eb = eb + eau;
            if (iseq[j] == 4) eb = eb + eau;
            if (iseq[ip] == 4) eb = eb + eau;
            if (iseq[jp] == 4) eb = eb + eau;
            break;
        case 2:
            // 5" (i) A . X (ip) 3"
            // 3" (j) U . Y (jp) 5"
            list[0] = iseq[i];
            list[1] = iseq[j];
            list[2] = iseq[i+1];
            list[3] = iseq[j-1];
            list[4] = iseq[ip];
            list[5] = iseq[jp];
            tint11(list,eb);
            break;
        case 3:
             // 5" (i) A .   X (ip) 3"
            // 3" (j) U . . Y (jp) 5"
            list[0] = iseq[i];
            list[1] = iseq[j];
            list[2] = iseq[i+1];
            list[3] = iseq[j-1];
            list[4] = iseq[j-2];
            list[5] = iseq[ip];
            list[6] = iseq[jp];
            tint12(list,eb);
            break;
        case 4:
             // 5" (i) A . . X (ip) 3"
            // 3" (j) U   . Y (jp) 5"
            list[0] = iseq[jp];
            list[1] = iseq[ip];
            list[2] = iseq[jp+1];
            list[3] = iseq[ip-1];
            list[4] = iseq[ip-2];
            list[5] = iseq[j];
            list[6] = iseq[i];
            tint12(list,eb);
            break;
        case 5:
            // 5" (i) A . . X (ip) 3"
            // 3" (j) U . . Y (jp) 5"
            list[0] = iseq[i];
            list[1] = iseq[j];
            list[2] = iseq[i+1];
            list[3] = iseq[j-1];
            list[4] = iseq[ip-1];
            list[5] = iseq[jp+1];
            list[6] = iseq[ip];
            list[7] = iseq[jp];
            tint22(list,eb);
            break;
        case 6:
            // 5" (i) A X .. G (ip) 3"
            // 3" (j) U Y .. C (jp) 5"
            list[0] = iseq[i];
            list[1] = iseq[j];
            list[2] = iseq[i+1];
            list[3] = iseq[j-1];
            //GAIL Rule
            if(imin == 1 && imax > 2){
                list[2] = 1;
                list[3] = 1;
            }
            tstacki(list,eb);
            
            // 5" (i) A .. X G (ip) 3"
            // 3" (j) U .. Y C (jp) 5"
            list[0] = iseq[jp];
            list[1] = iseq[ip];
            list[2] = iseq[jp+1];
            list[3] = iseq[ip-1];
            //GAIL Rule
            if(imin == 1 && imax > 2){
                list[2] = 1;
                list[3] = 1;
            }
            tstacki(list,eb);
            break;
        default:
            std::cout<<"[ERROR]: ibul out of range [0-6]";
    }
    
    // =  =  = PART 4 - - - > Asymmetry Penalty =  =  = //
    if (ibul == 6){
        k = std::min(4, n1, n2);
        x = float(na)*f[k];
        x = std::min(x, 3.0e0);
        eb = eb + x;
    }
}