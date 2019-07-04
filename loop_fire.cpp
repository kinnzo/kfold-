/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "rnafold.h"

void loop_fire(rna_struc *r,int indx,double amax){
 
    //Variables   
    

int i, j, k, n, n1, ip, jp, kp, is, js;
int ks, ke, l, lmx, icnt, iloop;
int nt, nh, ns, mt, mh, ms, icase;
int jndx, kndx, nsum;

double x, dg, atot;


i = r->loop[indx];
j = r->ibsp[i];

n = r->n;
n1 = r->n1;

nsum = r->nsum;

if (i == n) j = 0; //Changed Index Here

nh = r->nhlx[indx];
ns = r->nsgl[indx];

nt = ns + 2*nh;

// ==  = Internal Loop iloop = 1 ==  = //
// ==  = External Loop iloop = 0 ==  = //

if (i < j) iloop = 1;
if (i > j) iloop = 0;

if (iloop == 1) 
{
    ks = i + 1;
    ke = j;
} 
else
{
    ks = j;
    ke = i;
}


// ==  = FIND REACTION TO FIRE ==  = //

atot = 0.0e0;
jndx = 0;
kndx = 0;

k = ks;
icnt = 0;

while(k <= ke){

// ==  = Nucleation Events ==  = //

if (r->ibsp[k] == 0) 
{
    if (atot + r->wrk1[k] >= amax) 
    {
        
        l = 2;
        lmx = nt/2 + 1;
        
        if (nt%2 == 0) 
        {
            if (icnt + 1 > lmx - 1) lmx = lmx - 1;
        }
        
        if (iloop == 0) lmx = nt - icnt;
        
        kp = k + 1;
        is = r->iseq[k];
        
        while(l <= lmx){
        
        if (r->ibsp[kp] == 0) 
        {
            
            js = r->iseq[kp];
            
            if (l > 4 && iwc[is][js] == 1) 
            {
                
                atot = atot + pnuc[l];
                
                if (atot >= amax) 
                {
                    
                    n1 = n1 + 1;
                    
                    r->ibsp[k] = kp;
                    r->ibsp[kp] = k;
                    r->n1 = n1;
                    
                    if (n1 > nsum) 
                    {
                        r->nsum = 2*nsum;
                    }
                    
                    if (k < kp) 
                    {
                        r->loop[n1] = k;
                        r->link[k] = n1;
                        r->link[kp] = indx;
                    } 
                    else
                    {
                        r->loop[n1] = kp;
                        r->link[k] = indx;
                        r->link[kp] = n1;
                    }
                    
                    // ==  = Fix Links in New Loop ==  = //
                    
                    mh = 1;
                    ms = 0;
                    
                    ip = (k < kp)? k:kp;
                    jp = ip + 1;
                    
                    jndx = r->link[ip];
                    
                    while(jp < r->ibsp[ip]){
                    
                    if (r->link[jp] == indx) 
                    {
                        r->link[jp] = jndx;
                    }
                    
                    if (r->ibsp[jp] > jp) mh = mh + 1;
                    if (r->ibsp[jp] == 0) ms = ms + 1;
                    
                    if (r->ibsp[jp] > jp) 
                    {
                        jp = r->ibsp[jp];
                    } 
                    else
                    {
                        jp = jp + 1;
                    }
                    
                }
                
                r->nhlx[indx] = nh - mh + 2;
                r->nsgl[indx] = ns - ms - 2;
                
                r->nhlx[jndx] = mh;
                r->nsgl[jndx] = ms;
                
                loop_reac(r, indx);
                loop_reac(r, jndx);
                
                // ==  = Recalc Lower Loop? ==  = //
                
                if (iloop == 0) kndx = 0;
                if (iloop == 1) kndx = r->link[j];
                
                if (kndx != 0) loop_reac(r, kndx);
                
                return;
                
            }
        }
        
    } 
    else
    {
        
        l = l + 1;
        kp = r->ibsp[kp];
        
    }
    
    l = l + 1;
    kp = kp + 1;
    
}



}
atot = atot + r->wrk1[k];
}


// ==  = Helix Events ==  = //

if (r->ibsp[k] > 0) 
{

ip = k;
jp = r->ibsp[k];

icase = 0;

// ==  = Helix Extension ==  = //

if (ip > 1 && jp < n) 
{
if (nh > 1 || ns > 4) 
{
    if (r->ibsp[ip - 1] == 0 && r->ibsp[jp + 1] == 0) 
    {
        
        is = r->iseq[ip - 1];
        js = r->iseq[jp + 1];
        
        if (iwc[is][js] == 1) 
        {
            
            icase = 1;
            
            if (iloop == 1) 
            {
                if (nh == 2 && ns == 2) 
                {
                    icase = 2;
                    if (k == ke) icase = 0;
                } 
                else if (k == ke) {
                    icase = 3;
                }
            }
            
        }
        
    }
}
}

if (icase > 0) 
{

atot = atot + r->wrk2[ip];

if (atot >= amax) 
{
    
    if (icase == 1) 
    {
        
        jndx = r->link[ip];
        r->nsgl[indx] = ns - 2;
        
    } 
    else if (icase == 2){
        
        jndx = r->link[i + 2];
        
        if (jndx == n1) 
        {
            jndx = indx;
        }
        
        // ==  = Delete Loop indx ==  = //
        
        // ==  = Copy Loop n1 to indx ==  = //
        
        if (indx != n1) 
        {
            
            r->loop[indx] = r->loop[n1];
            r->nhlx[indx] = r->nhlx[n1];
            r->nsgl[indx] = r->nsgl[n1];
            r->ptot[indx] = r->ptot[n1];
            
            loop_resum(r, indx);
            
            kp = r->loop[n1];
            
            r->link[kp] = indx;
            
            l = kp + 1;
            
            while(l < r->ibsp[kp]){
            
            if (r->link[l] == n1) 
            {
                r->link[l] = indx;
            }
            
            if (r->ibsp[l] > l) 
            {
                l = r->ibsp[l];
            } 
            else
            {
                l = l + 1;
            }
            
        }
        
        
        
    }
    
    r->link[i] = 0;
    r->link[j - 2] = 0;
    
    r->loop[n1] = 0;
    r->nhlx[n1] = 0;
    r->nsgl[n1] = 0;
    r->ptot[n1] = 0.0e0;
    
    loop_resum(r, n1);
    
    r->n1 = n1 - 1;
    
    if (nsum > 2) 
    {
        if (r->n1 <= nsum/2) 
        {
            nsum = nsum/2;
            r->nsum = nsum;
            r->psum[nsum] = 0.0e0;
        }
    }
    
} else if (icase == 3){
    
    r->loop[indx] = jp + 1;
    r->nsgl[indx] = ns - 2;
    
}

// ==  = Adjust Base - Pairs ==  = //

r->ibsp[ip - 1] = jp + 1;
r->ibsp[jp + 1] = ip - 1;

// ==  = Fix Links ==  = //

r->link[jp + 1] = r->link[jp];
r->link[jp] = 0;

// ==  = Recalc Main Loop? ==  = //

if (icase != 2) 
{
    loop_reac(r, indx);
}

// ==  = Recalc Upper Loop? ==  = //

if (icase != 3) 
{
    if (jndx == 0) helx_reac(r, ip);
    if (jndx != 0) loop_reac(r, jndx);
}

// ==  = Recalc Lower Loop? ==  = //

if (iloop == 0) kndx = 0;
if (iloop == 1) kndx = r->link[j];

if (kndx != 0) loop_reac(r, kndx);

return;

}

}

// ==  = Helix Retraction ==  = //

icase = 0;

if(ip != n && jp != 1){

if (r->ibsp[ip + 1] == jp - 1) 
{

icase = 1;

if (iloop == 1) 
{
    if (k == ke) icase = 2;
}

} 
else if (iloop == 0 || k != ke){

l = r->link[ip];
mh = r->nhlx[l];
ms = r->nsgl[l];

icase = 3;

}

}

if(icase > 0){

if (icase == 2) 
{
atot = atot + r->wrk1[ip];
} 
else
{
atot = atot + r->wrk1[jp];
}

if (atot >= amax) {

r->ibsp[ip] = 0;
r->ibsp[jp] = 0;

if (icase == 1) 
{
    
    r->nsgl[indx] = ns + 2;
    
    r->link[jp - 1] = r->link[jp];
    if (jp != n) r->link[jp] = 0;
    
    // ==  = Recalc Main Loop ==  = //
    
    loop_reac(r, indx);
    
    // ==  = Recalc Upper/Lower Loops? ==  = //
    
    jndx = r->link[ip + 1];
    
    if (iloop == 0) kndx = 0;
    if (iloop == 1) kndx = r->link[j];
    
    if (jndx == 0) helx_reac(r, ip + 1);
    if (jndx != 0) loop_reac(r, jndx);
    if (kndx != 0) loop_reac(r, kndx);
    
} 
else if (icase == 2){
    
    r->nsgl[indx] = ns + 2;
    r->loop[indx] = jp - 1;
    
    r->link[jp - 1] = r->link[jp];
    if (jp != n) r->link[jp] = 0;
    
    // ==  = Recalc Main Loop ==  = //
    
    loop_reac(r, indx);
    
    // ==  = Recalc Lower Loop? ==  = //
    
    kndx = r->link[ip + 1];
    
    if (kndx != 0) loop_reac(r, kndx);
    
} 
else if (icase == 3){
    
    r->nhlx[indx] = nh + mh - 2;
    r->nsgl[indx] = ns + ms + 2;
    
    jndx = r->link[ip];
    
    // ==  = Fix Links in Loop Being Deleted ==  = //
    
    l = ip + 1;
    
    while(l < jp){
    
    if (r->link[l] == jndx) 
    {
        r->link[l] = indx;
    }
    
    if (r->ibsp[l] > l) 
    {
        l = r->ibsp[l];
    } 
    else
    {
        l = l + 1;
    }
    
}



// !==  = Copy Loop n1 to jndx ==  = //

if (jndx != n1) 
{
    
    r->loop[jndx] = r->loop[n1];
    r->nhlx[jndx] = r->nhlx[n1];
    r->nsgl[jndx] = r->nsgl[n1];
    r->ptot[jndx] = r->ptot[n1];
    
    loop_resum(r, jndx);
    
    kp = r->loop[n1];
    
    r->link[kp] = jndx;
    
    l = kp + 1;
    
    while(l < r->ibsp[kp]){
    
    if (r->link[l] == n1) 
    {
        r->link[l] = jndx;
    }
    
    if (r->ibsp[l] > l) 
    {
        l = r->ibsp[l];
    } else
    {
        l = l + 1;
    }
    
}



}

if (indx != n1) jndx = indx;

r->link[ip] = 0;
if (jp != n) r->link[jp] = 0;

r->loop[n1] = 0;
r->nhlx[n1] = 0;
r->nsgl[n1] = 0;
r->ptot[n1] = 0.0e0;

loop_resum(r, n1);

r->n1 = n1 - 1;

if (nsum > 2) 
{
if (r->n1 <= nsum/2) 
{
    nsum = nsum/2;
    r->nsum = nsum;
    r->psum[nsum] = 0.0e0;
}
}

// ==  = Recalc Main Loop ==  = //

loop_reac(r, jndx);

// ==  = Recalc Lower Loop? ==  = //

if (iloop == 0) kndx = 0;
if (iloop == 1) kndx = r->link[j];

if (kndx != 0) loop_reac(r, kndx);

}

return;

}

}

icase = 0;

// ==  = Helix Morphing ==  = //

if (iloop == 0 || nh > 2){
if (ip > 1 && jp < n){

is = r->iseq[ip - 1];
js = r->iseq[jp + 1];

if (iwc[is][js] == 1) icase = 1;

is = r->ibsp[ip - 1];
js = r->ibsp[jp + 1];

if (is != 0){
if (r->link[is] != 0) icase = 0;
}

if (js != 0){
if (r->link[jp + 1] != 0) icase = 0;
}
if (is == 0 && js == 0) icase = 0;
}
}

if (icase > 0){

//Commented Function
//deltag_hm(r, ip, jp, dg);

dg = dg/2.0e0;

x = beta*dg;
x = exp(-x)*ratem;

atot = atot + x;

if(atot >= amax){

is = r->ibsp[ip - 1];
js = r->ibsp[jp + 1];

if(is != 0){

r->ibsp[is] = 0;
r->link[ip - 1] = 0;
r->link[ip - 2] = indx;

if(iloop == 1 && is == ke) 
{
r->loop[indx] = ip - 2;
}

}

if(js != 0){

r->ibsp[js] = 0;
r->link[js] = 0;
r->link[js - 1] = indx;

if(iloop == 1 && js == i){
r->loop[indx] = js - 1;
}
}

if(is != 0 && js != 0){
ns = ns + 2;
r->nsgl[indx] = ns;
}

// ==  = Adjust Base - Pairs ==  = //

r->ibsp[ip - 1] = jp + 1;
r->ibsp[jp + 1] = ip - 1;

// ==  = Fix Links ==  = //

r->link[jp + 1] = r->link[jp];
r->link[jp] = 0;

if(iloop == 1 && k == ke){
    r->loop[indx] = jp + 1;
}

// ==  = Recalc Main Loop ==  = //

loop_reac(r, indx);

jndx = r->link[ip];
if (jndx == 0) helx_reac(r, ip);
if (jndx != 0) loop_reac(r, jndx);

// ==  = Recalc 5" 3" Loops? ==  = //

if (is != 0) 
{
jndx = r->link[is + 1];
if (jndx == 0) helx_reac(r, is + 1);
if (jndx != 0) loop_reac(r, jndx);
}

if (js != 0) 
{
jndx = r->link[jp + 2];
if (jndx == 0) helx_reac(r, jp + 2);
if (jndx != 0) loop_reac(r, jndx);
}

// ==  = Recalc Lower Loop? ==  = //

if (iloop == 0) kndx = 0;
if (iloop == 1) kndx = r->link[j];

if (kndx != 0) loop_reac(r, kndx);

return;

}

}

// ==  = Defect Diffusion ==  = //

// ==  = PUSH ==  = //

icase = 0;

if (r->link[ip] == 0) 
{

icase = 2;

if (iloop == 1) 
{
if (nh == 2 && ns == 1) icase = 3;
if (nh == 1 && ns == 3) icase = 0;
}

} 
else if (iloop == 0 || k != ke){

icase = 1;

if (iloop == 1) 
{
if (nh == 2 && ns == 1) icase = 4;
}

}

if (icase > 0) 
{

// ==  = Push 5" End ===!undefinedundefined

kp = ip - 1;

if (kp >= 1){
if (r->ibsp[kp] == 0){

is = r->iseq[kp];
js = r->iseq[jp];

if (iwc[is][js] == 1){

//Commented Function
//deltag_hd(r, ip, jp, kp, dg);

dg = dg/2.0e0;

x = beta*dg;
x = exp(-x)*rated;

atot = atot + x;

if (atot >= amax) goto g1;
}

}
}

// ==  = Push 3" End ===!undefinedundefined

kp = jp + 1;

if (kp <= n){
if (r->ibsp[kp] == 0){

is = r->iseq[ip];
js = r->iseq[kp];

if (iwc[is][js] == 1){

//Commented Function
//deltag_hd(r, ip, jp, kp, dg);

dg = dg/2.0e0;

x = beta*dg;
x = exp(-x)*rated;

atot = atot + x;

if (atot >= amax) goto g1;

}

}
}

}

// ==  = PULL ==  = //

icase = 0;

if (r->link[ip] != 0){
if (iloop == 0 || k != ke){

l = r->link[ip];
mh = r->nhlx[l];
ms = r->nsgl[l];

icase = 1;

if (mh == 1 && ms == 3) icase = 0;
if (mh == 2 && ms == 1) icase = 4;

}
}

if (icase > 0) 
{

// ==  = Pull 5" End ===!undefinedundefined

kp = ip + 1;

if (r->ibsp[kp] == 0) 
{

is = r->iseq[kp];
js = r->iseq[jp];

if (iwc[is][js] == 1) 
{
    
//Commented Function
//deltag_hd(r, ip, jp, kp, dg);

dg = dg/2.0e0;

x = beta*dg;
x = exp(-x)*rated;

atot = atot + x;

if (atot >= amax) goto g1;

}

}

// ==  = Pull 3" End ===!undefinedundefined

kp = jp - 1;

if (r->ibsp[kp] == 0) 
{

is = r->iseq[ip];
js = r->iseq[kp];

if (iwc[is][js] == 1){

//Commented Function
//deltag_hd(r, ip, jp, kp, dg);

dg = dg/2.0e0;

x = beta*dg;
x = exp(-x)*rated;

atot = atot + x;

if (atot >= amax) goto g1;

}

}

}

g1:
if (atot >= amax){

// ==  = Adjust Base - Pairs ==  = //

if (kp == ip + 1 || kp == ip - 1){
r->ibsp[ip] = 0;
r->ibsp[jp] = kp;
r->ibsp[kp] = jp;
} 
else {
r->ibsp[ip] = kp;
r->ibsp[jp] = 0;
r->ibsp[kp] = ip;
}

if (icase == 1) {

jndx = r->link[ip];

if (kp == ip + 1 || kp == ip - 1) 
{
r->loop[jndx] = kp;
r->link[kp] = r->link[ip];
r->link[ip] = 0;
} 
else{
r->link[kp] = r->link[jp];
r->link[jp] = 0;
}

if (kp == ip + 1 || kp == jp - 1) {
r->nsgl[indx] = r->nsgl[indx] + 1;
r->nsgl[jndx] = r->nsgl[jndx] - 1;
} 
else{
r->nsgl[indx] = r->nsgl[indx] - 1;
r->nsgl[jndx] = r->nsgl[jndx] + 1;
}

loop_reac(r, indx);
loop_reac(r, jndx);

// ==  = Recalc Lower Loop? == //

if (iloop == 0) kndx = 0;
if (iloop == 1) kndx = r->link[j];

if (kndx != 0) loop_reac(r, kndx);

} 
else if (icase == 2){

// ==  = Add Loop ==  = //

n1 = n1 + 1;

r->n1 = n1;

r->link[jp - 1] = n1;

if (n1 > nsum) 
{
r->nsum = 2*nsum;
}

if (kp == jp + 1) 
{
r->link[ip] = n1;
r->link[jp + 1] = r->link[jp];
r->link[jp] = 0;
} else
{
r->link[kp] = n1;
}

if (iloop == 1 && k == ke) 
{
r->loop[n1] = i - 1;
if (kp == jp + 1) 
{
r->loop[indx] = i + 1;
}
} 
else if (kp == ip - 1){
r->loop[n1] = kp;
} 
else{
r->loop[n1] = ip;
}

r->nsgl[indx] = ns - 1;
r->nhlx[n1] = 2;
r->nsgl[n1] = 1;

loop_reac(r, indx);
loop_reac(r, n1);

// ==  = Recalc Upper Loop? ==  = //

jndx = r->link[ip + 1];
if (jndx != 0) loop_reac(r, jndx);

if (iloop == 0 || k != ke) 
{
if (jndx == 0) helx_reac(r, ip + 1);
}

// ==  = Recalc Lower Loop? ==  = //

if (iloop == 0) kndx = 0;
if (iloop == 1) kndx = r->link[j];

if (kndx != 0) loop_reac(r, kndx);

} 
else if (icase == 3){

// ==  = Move Loop ==  = //

r->link[jp - 1] = r->link[jp];
r->link[jp] = 0;

if (kp == jp + 1){
r->link[ip] = r->link[ip - 1];
r->link[ip - 1] = 0;
} 
else{
r->link[ip - 1] = r->link[ip - 2];
r->link[ip - 2] = 0;
}

if (k == ke) {

r->loop[indx] = i - 1;

kndx = r->link[ip + 1];

if (kp == ip - 1) jndx = r->link[i + 1];
if (kp == jp + 1) jndx = r->link[i + 2];

if (jndx == 0) helx_reac(r, j - 1);
} 
else{
r->loop[indx] = i + 1;

jndx = r->link[ip + 1];
kndx = r->link[j];

if (jndx == 0) helx_reac(r, ip + 1);

}

loop_reac(r, indx);

if (jndx != 0) loop_reac(r, jndx);
if (kndx != 0) loop_reac(r, kndx);

} 
else if (icase == 4){

// ==  = Delete Loop ==  = //

if (kp == ip + 1) 
{

jndx = r->link[ip];

r->nsgl[indx] = r->nsgl[indx] + 1;

r->link[ip] = 0;
r->link[jp - 1] = 0;

loop_reac(r, indx);

// ==  = Recalc Upper Loop? ==  = //

kndx = r->link[ip + 2];

if (kndx != 0) loop_reac(r, kndx);
if (kndx == 0) helx_reac(r, ip + 2);

// ==  = Recalc Lower Loop? ==  = //

if (iloop == 0) kndx = 0;
if (iloop == 1) kndx = r->link[j];

if (kndx != 0) loop_reac(r, kndx);

} 
else if (kp == jp - 1){

jndx = r->link[ip];

r->nsgl[indx] = r->nsgl[indx] + 1;

r->link[jp - 1] = r->link[jp];
r->link[ip] = 0;
r->link[jp] = 0;
r->link[jp - 2] = 0;

loop_reac(r, indx);

// ==  = Recalc Upper Loop? ==  = //

kndx = r->link[ip + 1];

if (kndx != 0) loop_reac(r, kndx);
if (kndx == 0) helx_reac(r, ip + 1);

// ==  = Recalc Lower Loop? ==  = //

if (iloop == 0) kndx = 0;
if (iloop == 1) kndx = r->link[j];

if (kndx != 0) loop_reac(r, kndx);

} 
else{

jndx = r->link[ip];
kndx = r->link[j];

r->nsgl[jndx] = r->nsgl[jndx] + 1;

r->link[i] = 0;
r->link[jp] = 0;

if (kp == ip - 1) {
r->loop[jndx] = ip - 1;
r->link[ip - 1] = r->link[ip];
r->link[ip] = 0;
}

// ==  = Recalc Loops ==  = //

loop_reac(r, jndx);

if (kndx != 0) loop_reac(r, kndx);

jndx = indx;

}

// ==  = Delete Loop jndx ==  = //

// ==  = Copy Loop n1 to jndx ==  = //

if (jndx != n1) {

r->loop[jndx] = r->loop[n1];
r->nhlx[jndx] = r->nhlx[n1];
r->nsgl[jndx] = r->nsgl[n1];
r->ptot[jndx] = r->ptot[n1];

loop_resum(r, jndx);

is = r->loop[n1];

r->link[is] = jndx;

l = is + 1;

while(l < r->ibsp[is]){

if (r->link[l] == n1){
r->link[l] = jndx;
}

if (r->ibsp[l] > l) {
l = r->ibsp[l];
} 
else{
l = l + 1;
}

}



}

r->loop[n1] = 0;
r->nhlx[n1] = 0;
r->nsgl[n1] = 0;
r->ptot[n1] = 0.0e0;

loop_resum(r, n1);

r->n1 = n1 - 1;

if (nsum > 2) 
{
if (r->n1 <= nsum/2) 
{
nsum = nsum/2;
r->nsum = nsum;
r->psum[nsum] = 0.0e0;
}
}

}

return;

}

// ==  = fopen BP Inside Helix ==  = //

if (r->link[ip] == 0){
if (iloop == 1 && k == ke){

is = ip + 1;
js = jp - 1;

while(r->link[is] == 0){

atot = atot + r->wrk1[is];

is = is + 1;
js = js - 1;

if (atot >= amax) {

n1 = n1 + 1;

r->ibsp[is - 1] = 0;
r->ibsp[js + 1] = 0;
r->n1 = n1;

r->loop[n1] = js;
r->link[js] = n1;
r->link[is - 2] = n1;

r->nhlx[n1] = 2;
r->nsgl[n1] = 2;

if (n1 > nsum){
r->nsum = 2*nsum;
}

// ==  = Recalc Upper Loop? ==  = //

jndx = r->link[js + 2];

if (jndx == 0) helx_reac(r, js + 2);
if (jndx != 0) loop_reac(r, jndx);

// ==  = Calculate New Loop ==  = //

jndx = r->link[js];

loop_reac(r, jndx);

// ==  = Recalc Lower Loop? ==  = //

kndx = r->link[is];

if (kndx != 0) loop_reac(r, kndx);

return;

}

}
}
}


if (k != ke) 
{
k = r->ibsp[k];
icnt = icnt + 1;
}

}

k = k + 1;
icnt = icnt + 1;

}
}


