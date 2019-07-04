/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "energy.h"
#include "rnafold.h"

// --------------------------------------------
void deltag_hi(rna_struc r, int i, int j, double dg){
    
    // =  =  = VARIABLES =  =  = //
    
    int n;
    
    float ei, ef, es;
    
    
    n = r->n;
    
    // =  =  = INITIAL ENERGY =  =  = //
    
    estack(r->iseq, i - 1, j + 1, i, j, n, ei);
    estack(r->iseq, i, j, i + 1, j - 1, n, es);
    
    ei = ei + es;
    
    
    // =  =  = FINAL ENERGY =  =  = //
    
    ebulge(r->iseq, i - 1, j + 1, i + 1, j - 1, n, ef);
    
    dg = double(ef) - double(ei);
    
    
}

