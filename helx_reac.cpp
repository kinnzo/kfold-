/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "rnafold.h"
void helx_reac(rna_struc *r, int i){
    int ke, ip, jp, indx;
    double x, dg, atot;
    
    jp = i;
    
    ip = r->ibsp[jp];
    jp = (ip<jp)? ip:jp;
    
    while(r->link[jp] == 0){
        jp = jp + 1;
    }
    indx = r->link[jp];
    
    //Open BP Inside Helix
    ke = r->ibsp[jp];
    ip = r->ibsp[jp];
    atot = r->wrk1[jp];
    
    if(r->link[ke] == 0){
        ip = ip + 1;
        jp = jp - 1;
        
        while(r->link[ip] == 0){
            //Commenting Function
            //deltag_hi(r,ip,jp,dg)
            
            dg = dg/2.0e0;
            
            x = beta * dg;
            x = exp(-x) * rateh;
            
            r->wrk1[ip] = x;
            r->wrk1[jp] = 0.0e0;
            
            r->wrk2[ip] = 0.0e0;
            r->wrk2[jp] = 0.0e0;
            
            atot = atot + x;
            
            ip = ip + 1;
            jp = jp + 1;
        }
    }
    r->ptot[indx] = atot;
    loop_resum(r,indx);
}