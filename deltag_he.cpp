/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "energy.h"
#include "rnafold.h"


// --------------------------------------------
void deltag_he(rna_struc r, int ii, int jj, double dg)
{
    
    int i, j, k, n, ip, jp, is, js;
    int nh, ns, mh, ms, iloop, indx;
    
    float e1, e3, e5, ei, ef;
    float x, c, ed;
    
    
    indx = r->link[jj];
    
    i = r->loop[indx];
    j = r->ibsp[i];
    n = r->n;
    
    nh = r->nhlx[indx];
    ns = r->nsgl[indx];
    
    c = 1.750e0/float(beta);
    
    // !==  = Internal Loop iloop = 1 ==  = //
    // !==  = External Loop iloop = 0 ==  = //
    
    iloop = 1;
    
    if (i > j) 
    {
        iloop = 0;
        i = 1;
        j = n;
    }
    
    // !==  = Final Loop Size ==  = //
    
    mh = nh;
    ms = ns - 2;
    
    
    // !==  = INITIAL ENERGY ==  = //
    
    if (nh == 1 && iloop == 1) 
    {
        
        ehair(r->iseq, i, j, n, ei);
        
    } 
    else if (nh == 2 && iloop == 1){
        
        ip = i + 1;
        while(r->ibsp[ip] == 0)
        ip = ip + 1;
    
    
    
    jp = r->ibsp[ip];
    
    ebulge(r->iseq, i, j, ip, jp, n, ei);
    
} else
{
    
    ei = 0.0e0;
    e5 = 0.0e0;
    e3 = 0.0e0;
    
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
    
    if (ii > 1) 
    {
        if (r->ibsp[ii - 1] == 0) 
        {
            
            edangle(r->iseq, ii, jj, ii - 1, n, e5);
            
            if (ii > 2) 
            {
                
                ip = ii - 2;
                jp = r->ibsp[ip];
                
                if (jp != 0) 
                {
                    edangle(r->iseq, ip, jp, ii - 1, n, ed);
                    e5 = std::min(e5, ed);
                }
                
            }
            
            if (ii > 3) 
            {
                if (r->ibsp[ii - 2] == 0) 
                {
                    
                    ip = ii - 3;
                    jp = r->ibsp[ip];
                    
                    if (jp != 0) 
                    {
                        edangle(r->iseq, ip, jp, ii - 2, n, ed);
                        ei = ei + ed;
                    }
                    
                }
            }
            
        }
    }
    
    if (jj < n) 
    {
        if (r->ibsp[jj + 1] == 0) 
        {
            
            edangle(r->iseq, ii, jj, jj + 1, n, e3);
            
            if (jj < n - 1) 
            {
                
                ip = jj + 2;
                jp = r->ibsp[ip];
                
                if (jp != 0) 
                {
                    edangle(r->iseq, ip, jp, jj + 1, n, ed);
                    e3 = std::min(e3, ed);
                }
                
            }
            
            if (jj < n - 2) 
            {
                if (r->ibsp[jj + 2] == 0) 
                {
                    
                    ip = jj + 3;
                    jp = r->ibsp[ip];
                    
                    if (jp != 0) 
                    {
                        edangle(r->iseq, ip, jp, jj + 2, n, ed);
                        ei = ei + ed;
                    }
                    
                }
            }
            
        }
    }
    
    ei = ei + e3 + e5 + eaup[is][js];
    
}


// !==  = FINAL ENERGY ==  = //

estack(r->iseq, ii - 1, jj + 1, ii, jj, n, ef);

if (mh == 1 && iloop == 1) 
{
    
    ehair(r->iseq, i + 1, j - 1, n, e1);
    
} 
else if (mh == 2 && iloop == 1){
    
    if (ms == 0) 
    {
        
        estack(r->iseq, ii - 2, jj + 2, ii - 1, jj + 1, n, e1);
        
    } else
    {
        
        ip = i + 1;
        while(r->ibsp[ip] == 0)
        ip = ip + 1;
    
    
    
    jp = r->ibsp[ip];
    
    if (j == ii) 
    {
        ebulge(r->iseq, i + 1, j - 1, ip, jp, n, e1);
    } else
    {
        ebulge(r->iseq, i, j, ip - 1, jp + 1, n, e1);
    }
    
}

} else
{

e1 = 0.0e0;
e5 = 0.0e0;
e3 = 0.0e0;

is = r->iseq[ii - 1];
js = r->iseq[jj + 1];

if (iloop == 1) 
{
    
    if (ms <= 6) 
    {
        e1 = em + es*float(ms) + eh*float(mh);
    } else
    {
        x = float(ms)/6.0e0;
        e1 = em + es*6.0e0 + eh*float(mh);
        e1 = e1 + c*log(x);
    }
    
}

if (ii > 2) 
{
    if (r->ibsp[ii - 2] == 0) 
    {
        
        edangle(r->iseq, ii - 1, jj + 1, ii - 2, n, e5);
        
        if (ii > 3) 
        {
            
            ip = ii - 3;
            jp = r->ibsp[ip];
            
            if (jp != 0) 
            {
                edangle(r->iseq, ip, jp, ii - 2, n, ed);
                e5 = std::min(e5, ed);
            }
            
        }
        
    }
}

if (jj < n - 1) 
{
    if (r->ibsp[jj + 2] == 0) 
    {
        
        edangle(r->iseq, ii - 1, jj + 1, jj + 2, n, e3);
        
        if (jj < n - 2) 
        {
            
            ip = jj + 3;
            jp = r->ibsp[ip];
            
            if (jp != 0) 
            {
                edangle(r->iseq, ip, jp, jj + 2, n, ed);
                e3 = std::min(e3, ed);
            }
            
        }
        
    }
}

e1 = e1 + e3 + e5 + eaup[is][js];

}

ef = ef + e1;

dg = double(ef) - double(ei);

}