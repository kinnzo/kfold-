/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "rnafold.h"
void loop_resum(rna_struc *r,int indx){
    // =  =  = VARIABLES =  =  = //

    int i, j, k, nsum;
    int n, n1, n2;


    nsum = r->nsum;
    // =  =  = Re-sum Partial Sum Table =  =  = //
    n = 1;
    n1 = 2;
    n2 = 4;
    
    if (indx%2 == 1) i = indx; //Need to Change Index Here
    if (indx%2 == 0) i = indx - 1; //Need to Change Index Here
    
    r->psum[i] = r->ptot[i] + r->ptot[i + 1];
    
    while(n1 < nsum){
        i = int(i/n2)*n2 + n1;
        j = i - n;
        k = i + n;
        
        r->psum[i] = r->psum[j] + r->psum[k];
        
        n = n1;
        n1 = n2;
        n2 = 2*n2;
    }
}