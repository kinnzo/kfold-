/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "energy.h"
#include "rnafold.h"

// --------------------------------------------
void deltag_hm(rna_struc r, int ii, int jj, double dg){
    

    // !=   == VARIABLES ==  = //
    
    int i, j, k, n, ip, jp, kp, lp;
    int is, js, nh, ns, mh, ms;
    int iloop, indx;
    
    float e1, e2, e3, e4, e5, ed;
    float x, c, ei, ef;
    
    
    indx = r->link[jj];
    
    i = r->loop[indx];
    j = r->ibsp[i];
    n = r->n;
    
    nh = r->nhlx[indx];
    ns = r->nsgl[indx];
    
    c = 1.750e0/float(beta);
    
    // !=   == Internal Loop iloop = 1 ==  = //
    // !=   == External Loop iloop = 0 ==  = //
    
    iloop = 1;
    
    if (i > j) 
    {
        iloop = 0;
        i = 1;
        j = n;
    }
    
    // !=   == Final Loop Size ==  = //
    
    mh = nh;
    ms = ns;
    
    ip = r->ibsp[ii - 1];
    jp = r->ibsp[jj + 1];
    
    if (ip !=  0 && jp !=  0) ms = ms + 2;
    
    
    e4 = 0.0e0;
    
    // !=   == INITIAL ENERGY ==  = //
    
    ei = 0.0e0;
    e1 = 0.0e0;
    e2 = 0.0e0;
    e3 = 0.0e0;
    e5 = 0.0e0;
    
    is = r->iseq[ii];
    js = r->iseq[jj];
    
    if (iloop == 1) 
    {
        
        if (ns <= 6) 
        {
            ei = em + es*float(ns) + eh*float(nh);
        } else
        {
            x = float(ns)/6.0e0;
            ei = em + es*6.0e0 + eh*float(nh);
            ei = ei + c*log(x);
        }
        
    }
    
    ei = ei + eaup[is][js];
    
    
    // !=   == 5" Side ===!undefinedundefined
    
    if (r->ibsp[ii - 1] !=  0) 
    {
        
        jp = ii - 1;
        ip = r->ibsp[jp];
        
        is = r->iseq[ip];
        js = r->iseq[jp];
        
        estack(r->iseq, ip, jp, ip + 1, jp - 1, n, e1);
        
        if (ip > 1) 
        {
            if (r->ibsp[ip - 1] == 0) 
            {
                
                edangle(r->iseq, ip, jp, ip - 1, n, e5);
                
                if (ip > 2) 
                {
                    
                    kp = ip - 2;
                    lp = r->ibsp[kp];
                    
                    if (lp !=  0) 
                    {
                        edangle(r->iseq, kp, lp, ip - 1, n, ed);
                        if (lp !=  jj + 1) e4 = e4 + ed;
                        e5 = std::min(e5, ed);
                    }
                    
                }
                
            }
        }
        
        e1 = e1 + e5 + eaup[is][js];
        
        is = r->iseq[ip + 1];
        js = r->iseq[jp - 1];
        
        edangle(r->iseq, ip + 1, jp - 1, ip, n, e5);
        
        if (ip > 1) 
        {
            if (r->ibsp[ip - 1] !=  0) 
            {
                
                kp = ip - 1;
                lp = r->ibsp[kp];
                
                if (lp !=  jj + 1) 
                {
                    edangle(r->iseq, kp, lp, ip, n, ed);
                    e5 = std::min(e5, ed);
                }
                
            }
        }
        
        e4 = e4 + e5 + eaup[is][js];
        
    } else
    {
        
        edangle(r->iseq, ii, jj, ii - 1, n, e5);
        
        if (ii > 2) 
        {
            
            ip = ii - 2;
            jp = r->ibsp[ip];
            
            if (jp !=  0) 
            {
                
                edangle(r->iseq, ip, jp, ii - 1, n, ed);
                e5 = std::min(e5, ed);
                
            } else if (ii > 3){
                
                kp = ii - 3;
                lp = r->ibsp[kp];
                
                if (lp !=  0) 
                {
                    edangle(r->iseq, kp, lp, ii - 2, n, ed);
                    e5 = e5 + ed;
                }
                
            }
            
        }
        
        e1 = e5;
        
    }
    
    
    // !=   == 3" Side ===!undefinedundefined
    
    if (r->ibsp[jj + 1] !=  0) 
    {
        
        ip = jj + 1;
        jp = r->ibsp[ip];
        
        is = r->iseq[ip];
        js = r->iseq[jp];
        
        estack(r->iseq, ip, jp, ip + 1, jp - 1, n, e2);
        
        if (jp < n) 
        {
            if (r->ibsp[jp + 1] == 0) 
            {
                
                edangle(r->iseq, ip, jp, jp + 1, n, e3);
                
                if (jp < n - 1) 
                {
                    
                    kp = jp + 2;
                    lp = r->ibsp[kp];
                    
                    if (lp !=  0) 
                    {
                        
                        edangle(r->iseq, kp, lp, jp + 1, n, ed);
                        
                        if (lp !=  ii - 1) 
                        {
                            e4 = e4 + ed;
                            e3 = std::min(e3, ed);
                        } else
                        {
                            e3 = 0.0e0;
                        }
                        
                    }
                    
                }
                
            }
        }
        
        e2 = e2 + e3 + eaup[is][js];
        
        is = r->iseq(ip + 1);
        js = r->iseq(jp - 1);
        
        edangle(r->iseq, ip + 1, jp - 1, jp, n, e3);
        
        if (jp < n) 
        {
            if (r->ibsp[jp + 1] !=  0) 
            {
                
                kp = jp + 1;
                lp = r->ibsp[kp];
                
                if (lp !=  ii - 1) 
                {
                    edangle(r->iseq, kp, lp, jp, n, ed);
                    e3 = std::min(e3, ed);
                }
                
            }
        }
        
        e4 = e4 + e3 + eaup[is][js];
        
    } else
    {
        
        edangle(r->iseq, ii, jj, jj + 1, n, e3);
        
        if (jj < n - 1) 
        {
            
            ip = jj + 2;
            jp = r->ibsp[ip];
            
            if (jp !=  0) 
            {
                
                edangle(r->iseq, ip, jp, jj + 1, n, ed);
                e3 = std::min(e3, ed);
                
            } else if (jj < n - 2){
                
                kp = jj + 3;
                lp = r->ibsp[kp];
                
                if (lp !=  0) 
                {
                    edangle(r->iseq, kp, lp, jj + 2, n, ed);
                    e3 = e3 + ed;
                }
                
            }
            
        }
        
        e2 = e3;
        
    }
    
    ei = ei + e1 + e2;
    
    
    // !=   == FINAL ENERGY ==  = //
    
    ef = 0.0e0;
    e5 = 0.0e0;
    e3 = 0.0e0;
    
    ip = ii - 1;
    jp = jj + 1;
    
    is = r->iseq[ip];
    js = r->iseq[jp];
    
    if (iloop == 1) 
    {
        
        if (ms <= 6) 
        {
            ef = em + es*float(ms) + eh*float(mh);
        } else
        {
            x = float(ms)/6.0e0;
            ef = em + es*6.0e0 + eh*float(mh);
            ef = ef + c*log(x);
        }
        
    }
    
    estack(r->iseq, ip, jp, ii, jj, n, ed);
    
    ef = ef + ed + eaup[is][js];
    
    if (ip > 1) 
    {
        if (r->ibsp[ip - 1] == 0) 
        {
            
            edangle(r->iseq, ip, jp, ip - 1, n, e5);
            
            if (ip > 2) 
            {
                
                kp = ip - 2;
                lp = r->ibsp[kp];
                
                if (lp !=  0) 
                {
                    edangle(r->iseq, kp, lp, ip - 1, n, ed);
                    e5 = std::min(e5, ed);
                }
                
            }
            
        }
    }
    
    if (jp < n) 
    {
        if (r->ibsp[jp + 1] == 0) 
        {
            
            edangle(r->iseq, ip, jp, jp + 1, n, e3);
            
            if (jp < n - 1) 
            {
                
                kp = jp + 2;
                lp = r->ibsp[kp];
                
                if (lp !=  0) 
                {
                    edangle(r->iseq, kp, lp, jp + 1, n, ed);
                    e3 = std::min(e3, ed);
                }
                
            }
            
        }
    }
    
    ef = ef + e5 + e3 + e4;
    
    dg = double(ef) - double(ei);
    
    
}


