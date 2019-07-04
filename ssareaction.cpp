/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "rnafold.h"
void ssareaction(rna_struc *rna, int iseed, double time, double tout){
    //Variables
    float e;
    int i, j, n;
    int indx;
    //Unused Variables int n1,n2,k;
    char fld[mxnt];
    double r, tau;
    //Unused Variable double random;
    double atot, amax;
    
    //Total Transition Rate
    n = rna->nsum / 2;
    atot = rna->psum[n];
    
    //Compute Time Increment
    r = random(iseed);
    
    tau = log(1.0e0 / r);
    tau = tau / atot;
    
    time = time + tau;
    
    //Output Current Structure
    if(time > tout){
        //Commenting Functions
        //v2ct(rna->ibsp,fld,'V',rna->n);
        //estruc(rna->iseq,rna->ibsp,rna->n,e);
        cout<<tout<<" "<<e;
        cout<<rna->iseq;
        cout<<fld;
    }
    //Fire Reaction
    r = random(iseed);
    amax = r * atot;
    
    //Find Reaction to Fire
    i = n;
    while(n%2 == 0){
        n = n/2;
        j = i-n;
        
        r = rna->psum[j];
        if(r >= amax){
            i = j;
        }
        else{
            i = i + n;
            amax = amax - r;
        }
    }
    
    //Choose between i and i+1
    r = rna->ptot[i];
    
    if(r >= amax){
        indx = i;
    }
    else{
        indx = i + 1;
        amax = amax - r;
    }
    
    //Fire Reaction
    loop_fire(rna,indx,amax);
}