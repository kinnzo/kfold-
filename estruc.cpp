/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "energy.h"
void estruc(int iseq[], int ibsp[], int n, float e)
{
    

    
    int i, j, ip, jp;
    int il, nl, loop[n];
    
    float el, es;
    
    
    e = 0.0e0;
    el = 0.0e0;
    es = 0.0e0;
    
    // !=   == Find Loops ==  = //
    
    nl = 1;
    loop[0] = n;
    
   for(i=0;i<n;i++){ 
    j = ibsp[i];
    
    if (j > i) 
    {
        
        ip = i + 1;
        jp = j - 1;
        
        if (ibsp[ip] !=  jp) 
        {
            nl = nl + 1;
            loop[nl] = i;
        }
        
    }
    
}



// !=   == Compute Energy ==  = //


for(il=0;il<nl;il++){
i = loop[il];
j = ibsp[i];

if (i == n) j = 1;

// !=   == Loop Energy ==  = //

eloop(iseq, ibsp, i, j, n, el);

e = e + el;

// !=   == Stacking Energy ==  = //

ip = i - 1;
jp = j + 1;

if (ip < 0) continue;
if (jp > n-1) continue;
if (i > j) continue;

while(ibsp[ip] == jp){

estack(iseq, ip, jp, i, j, n, es);

e = e + es;

i = ip;
j = jp;

ip = ip - 1;
jp = jp + 1;

if (ip < 0) return;
if (jp > n-1) return;

}



}
} 