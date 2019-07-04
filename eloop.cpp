/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "energy.h"
#include "rnavar.h"
void eloop(int iseq[], int ibsp[], int i, int j, int n, float el)
{

    int  k, ip, jp, kp, ks, ke;
    int nh, ns, iloop, ilast;
    
    float x, c, ed, e3, e5;
    
    
    el = 0.0e0;
    
    nh = 0;
    ns = 0;
    
    c = 1.750e0/float(beta);
    
    // != =  = Internal Loop iloop = 1 ==  = //
    // != =  = External Loop iloop = 0 ==  = //
    
    if (i < j) iloop = 1;
    if (i > j) iloop = 0;
    
    ks = std::min(i, j);
    ke = std::max(i, j);
    
    
    // != =  = Count number of Helices in Loop ==  = //
    
    k = ks;
    
    while(k <= ke){
    
    if (ibsp[k] == 0) ns = ns + 1;
    if (ibsp[k] > k) nh = nh + 1;
    
    if (ibsp[k] > k) 
    {
        if (iloop == 0 || k !=  ks) 
        {
            k = ibsp[k];
        }
    }
    
    k = k + 1;
    
}




// != =  = Compute Loop Energy ==  = //

if (nh == 1 && iloop == 1) 
{
    
    ehair(iseq, i, j, n, el);
    
} else if (nh == 2 && iloop == 1){
    
    ip = i + 1;
    while(ibsp[ip] == 0)
    ip = ip + 1;



jp = ibsp[ip];

ebulge(iseq, i, j, ip, jp, n, el);

} else
{

e3 = 0.0e0;

if (iloop == 0) 
{
    
    k = ks;
    ilast = 0;
    
} else if (iloop == 1){
    
    ip = i;
    jp = ibsp[i];
    
    k = ip + 1;
    ilast = k;
    
    if (k >= 1 && k <= n) 
    {
        if (ibsp[k] == 0) 
        {
            edangle(iseq, ip, jp, k, n, e3);
        }
    }
    
    if (ns <= 6) 
    {
        el = em + es*float(ns) + eh*float(nh);
    } else
    {
        x = float(ns)/6.0e0;
        el = em + es*6.0e0 + eh*float(nh);
        el = el + c*log(x);
    }
    
}

while(k <= ke){

if (ibsp[k] !=  0) 
{
    
    ip = k;
    jp = ibsp[k];
    
    kp = ip - 1;
    
    e5 = 0.0e0;
    
    if (kp >= 1 && kp <= n) 
    {
        if (ibsp[kp] == 0) 
        {
            edangle(iseq, ip, jp, kp, n, e5);
        }
    }
    
    if (ilast == kp) 
    {
        ed = std::min(e3, e5);
    } else
    {
        ed = e3 + e5;
    }
    
    el = el + ed + eaup(iseq[ip], iseq(jp));
    
    kp = jp + 1;
    ilast = kp;
    
    e3 = 0.0e0;
    
    if (kp >= 1 && kp <= n) 
    {
        if (ibsp[kp] == 0) 
        {
            edangle(iseq, ip, jp, kp, n, e3);
        }
    }
    
    if (k !=  ke) 
    {
        k = ibsp[k];
    }
    
}
k = k + 1;
}
if (iloop == 0) 
{
el = el + e3;
}
}
}