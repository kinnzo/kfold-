/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "energy.h"
#include "rnafold.h"

// --------------------------------------------
void deltag_hr(rna_struc r, int ii, int jj, double dg){
    
    
    // !=   == VARIABLES ==  = //
    
    int i, j, k, n, ip, jp, is, js;
    int nh, ns, mh, ms, lh, ls;
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
    
    if (i > j){
        iloop = 0;
        i = 1;
        j = n;
    }
    
    if (r->ibsp[ii + 1] !=  jj - 1) {
        
        k = r->link[ii];
        mh = r->nhlx[k];
        ms = r->nsgl[k];
        
    } 
    else{
        mh = 2;
        ms = 0;
    }
    
    // !=   == Final Loop Size ==  = //
    
    lh = nh + mh - 2;
    ls = ns + ms + 2;
    
    
    e4 = 0.0e0;
    
    // !=   == INITIAL ENERGY ==  = //
    
    if (nh == 1 && iloop == 1){
        
        ehair(r->iseq, i, j, n, e1);
        
    } 
    else if (nh == 2 && iloop == 1){
        
        ip = i + 1;
        while(r->ibsp[ip] == 0)
            ip = ip + 1;
        jp = r->ibsp[ip];
        ebulge(r->iseq, i, j, ip, jp, n, e1);
        if (mh > 2){
            is = r->iseq[i];
            js = r->iseq[j];
            if (r->ibsp[i + 1] == 0){
                edangle(r->iseq, i, j, i + 1, n, ed);
                e4 = e4 + ed;
            }
            if (r->ibsp[j - 1] == 0) {
                edangle(r->iseq, i, j, j - 1, n, ed);
                e4 = e4 + ed;
            }
            e4 = e4 + eaup[is][js];
        }
    } 
    else{
        e1 = 0.0e0;
        e5 = 0.0e0;
        e3 = 0.0e0;
        is = r->iseq[ii];
        js = r->iseq[jj];
        if (iloop == 1) {
            if (ns <= 6) {
                e1 = em + es*float(ns) + eh*float(nh);
            }
            else{
                x = float(ns)/6.0e0;
                e1 = em + es*6.0e0 + eh*float(nh);
                e1 = e1 + c*log(x);
            }
        }
        if (ii > 1){
            if (r->ibsp[ii - 1] == 0) {
                edangle(r->iseq, ii, jj, ii - 1, n, e5);
                if (ii > 2) {
                    ip = ii - 2;
                    jp = r->ibsp[ip];
                    if (jp !=  0) {
                        edangle(r->iseq, ip, jp, ii - 1, n, ed);
                        e5 = std::min(e5, ed);
                        e4 = e4 + ed;
                    }
                }
            }
        }
        if (jj < n){
            if (r->ibsp[jj + 1] == 0){
                edangle(r->iseq, ii, jj, jj + 1, n, e3);
                if (jj < n - 1) {
                    ip = jj + 2;
                    jp = r->ibsp[ip];
                    if (jp !=  0){
                        edangle(r->iseq, ip, jp, jj + 1, n, ed);
                        e3 = std::min(e3, ed);
                        e4 = e4 + ed;
                    }
                }
            }
        }
        e1 = e1 + e3 + e5 + eaup[is][js];
    }
    if (mh == 1){
        ehair(r->iseq, ii, jj, n, e2);
    } 
    else if (mh == 2){
        if (ms == 0){
            estack(r->iseq, ii, jj, ii + 1, jj - 1, n, e2);
        }
        else{
            ip = ii + 1;
            while(r->ibsp[ip] == 0)
                ip = ip + 1;
            jp = r->ibsp[ip];    
            ebulge(r->iseq, ii, jj, ip, jp, n, e2);
    
    if (nh > 2 || iloop == 0) 
    {
        
        is = r->iseq[ip];
        js = r->iseq[jp];
        
        if (r->ibsp[ip - 1] == 0) 
        {
            edangle(r->iseq, ip, jp, ip - 1, n, ed);
            e4 = e4 + ed;
        }
        
        if (r->ibsp[jp + 1] == 0) 
        {
            edangle(r->iseq, ip, jp, jp + 1, n, ed);
            e4 = e4 + ed;
        }
        
        e4 = e4 + eaup[is][js];
        
    }
    
}

} else
{

e2 = 0.0e0;
e5 = 0.0e0;
e3 = 0.0e0;

is = r->iseq[ii];
js = r->iseq[jj];

if (ms <= 6) 
{
    e2 = em + es*float(ms) + eh*float(mh);
} else
{
    x = float(ms)/6.0e0;
    e2 = em + es*6.0e0 + eh*float(mh);
    e2 = e2 + c*log(x);
}

if (r->ibsp[jj - 1] == 0) 
{
    
    edangle(r->iseq, ii, jj, jj - 1, n, e5);
    
    ip = jj - 2;
    jp = r->ibsp[ip];
    
    if (jp !=  0) 
    {
        edangle(r->iseq, ip, jp, jj - 1, n, ed);
        e5 = std::min(e5, ed);
        e4 = e4 + ed;
    }
    
}

if (r->ibsp[ii + 1] == 0) 
{
    
    edangle(r->iseq, ii, jj, ii + 1, n, e3);
    
    ip = ii + 2;
    jp = r->ibsp[ip];
    
    if (jp !=  0) 
    {
        edangle(r->iseq, ip, jp, ii + 1, n, ed);
        e3 = std::min(e3, ed);
        e4 = e4 + ed;
    }
    
}

e2 = e2 + e3 + e5 + eaup[is][js];

}

ei = e1 + e2;


// !=   == FINAL ENERGY ==  = //

if (lh == 1 && iloop == 1) 
{

if (j == ii) 
{
    ehair(r->iseq, i - 1, j + 1, n, ef);
} else
{
    ehair(r->iseq, i, j, n, ef);
}

} else if (lh == 2 && iloop == 1){

ip = ii + 1;
if (mh == 1) ip = i + 1;
if (j == ii) ip = i + 1;

while(r->ibsp[ip] == 0)
ip = ip + 1;

jp = r->ibsp[ip];

if (nh > 2) 
{

e3 = 0.0e0;
e5 = 0.0e0;

if (ip == ii) 
{
    
    ip = jj + 1;
    while(r->ibsp[ip] == 0)
    ip = ip + 1;
jp = r->ibsp[ip];

}

is = r->iseq[i];
js = r->iseq[j];

if (i + 2 !=  ii) 
{
if (r->ibsp[i + 1] == 0) 
{
    
    edangle(r->iseq, i, j, i + 1, n, e3);
    
}
}

if (j - 2 !=  jj) 
{
if (r->ibsp[j - 1] == 0) 
{
    
    edangle(r->iseq, i, j, j - 1, n, e5);
    
}
}

e1 = e1 + eaup[is][js];

is = r->iseq[ip];
js = r->iseq[jp];

if (ip - 2 !=  jj) 
{
if (r->ibsp[ip - 1] == 0) 
{
    
    edangle(r->iseq, ip, jp, ip - 1, n, ed);
    
    if (ip - 2 == i) 
    {
        e3 = std::min(e3, ed);
    } else
    {
        e3 = e3 + ed;
    }
    
}
}

if (jp + 2 !=  ii) 
{
if (r->ibsp[jp + 1] == 0) 
{
    
    edangle(r->iseq, ip, jp, jp + 1, n, ed);
    
    if (jp + 2 == j) 
    {
        e5 = std::min(e5, ed);
    } else
    {
        e5 = e5 + ed;
    }
    
}
}

e1 = e1 + eaup[is][js];
e1 = e1 + e3 + e5;

ei = e1 + e2;

}

if (j == ii) 
{
ebulge(r->iseq, i - 1, j + 1, ip, jp, n, ef);
} else
{
ebulge(r->iseq, i, j, ip, jp, n, ef);
}

} else
{

ef = 0.0e0;
e5 = 0.0e0;
e3 = 0.0e0;

if (iloop == 1) 
{

if (ls <= 6) 
{
ef = em + es*float(ls) + eh*float(lh);
} else
{
x = float(ls)/6.0e0;
ef = em + es*6.0e0 + eh*float(lh);
ef = ef + c*log(x);
}

}

ip = ii + 1;
jp = r->ibsp[ip];

if (jp !=  0) 
{
edangle(r->iseq, ip, jp, ii, n, e5);
}

if (ii > 1) 
{

ip = ii - 1;
jp = r->ibsp[ip];

if (jp !=  0) 
{
edangle(r->iseq, ip, jp, ii, n, ed);
e5 = std::min(e5, ed);
}

}

ip = jj - 1;
jp = r->ibsp[ip];

if (jp !=  0) 
{
edangle(r->iseq, ip, jp, jj, n, e3);
}

if (jj < n) 
{

ip = jj + 1;
jp = r->ibsp[ip];

if (jp !=  0) 
{
edangle(r->iseq, ip, jp, jj, n, ed);
e3 = std::min(e3, ed);
}

}

if (mh == 2 && ms == 0) 
{

is = r->iseq[ii + 1];
js = r->iseq[jj - 1];

ef = ef + eaup[is][js];

}

ef = ef + e3 + e4 + e5;

}

    dg = double(ef) - double(ei);

} 