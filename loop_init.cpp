/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "rnafold.h"

void loop_init(rna_struc *r){
    int i,j,n,n1,ns,nh;
    int ip,jp,kp,ks,ke;
    int nsum;
    
    //Initialize RNA Data
    n = r->n;
    for(i=0;i<mxnt;i++){
        r->link[i] = 0;
        r->loop[i] = 0;
        r->nhlx[i] = 0;
        r->nsgl[i] = 0;
        
        r->wrk1[i] = 0.0e0;
        r->wrk2[i] = 0.0e0;
        
        r->psum[i] = 0.0e0;
        r->ptot[i] = 0.0e0;
    }
    
    n1 = 0;
    r->loop[0] = n;
    
    //Finding Loops
    for(i=0;i<n;i++){
        j = r->ibsp[i];
        if(j > i){
            ip = i + 1;
            jp = j - 1;
            if(r->ibsp[ip] != jp){
                n1 = n1 + 1;
                r->loop[n1] = i;
            }
        }
    }
    r->n1 = n1;
    
    //Making Links
    for(i=0;i<n1;i++){
        ip = r->loop[i];
        jp = r->ibsp[ip];
        if(ip == n)
            jp = 1;
        r->link[ip] = i;
        if(ip < jp){
            ks = ip + 1;
            ke = jp;
            nh = 1;
            ns = 0;
        }
        else{
            ks = jp;
            ke = ip;
            nh = 0;
            ns = 0;
        }
        kp = ks;
        while(kp <= ke){
            if(r->ibsp[kp] > kp)
                nh = nh + 1;
            if(r->ibsp[kp] == 0)
                ns = ns + 1;
            if(r->ibsp[kp] > kp){
                kp = r->ibsp[kp];
                r->link[kp] = i;
            }
            else
                kp = kp + 1;
        }
        r->nhlx[i] = nh;
        r->nsgl[i] = ns;
    }
    
    //Compute Size of Partial Sum Table
    nsum = 2;
    while(nsum < n1){
        nsum = 2 * nsum;
    }
    r->nsum = nsum;
    
    //Compute Reactions for Loops
    for(i=0;i<n1;i++)
        loop_reac(r,i);
}