/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "rnafold.h"
#include "energy.h"
void delta_hd(rna_struc *r, int ii, int jj, int kk, double dg){
    int i,j,k,l,n,ip,jp;
    int nh,ns,mh,ms,is,js;
    int indx,iloop,kloop;
    
    float e1,e2,e3,e4,e5,ed;
    float x,c,ei,ef;
    
    indx = r->link[jj];
    i = r->loop[indx];
    j = r->ibsp[i];
    n = r->n;
    
    nh = r->nhlx[indx];
    ns = r->nsgl[indx];
    
    c = 1.750e0 / float(beta);
    
    //Internal Loop iloop = 1
    //External Loop iloop = 0
    iloop = 1;
    kloop = 1;
    
    //Changing Index here
    if(i>j){
        iloop = 0;
        i = 0;
        j = n-1;
    }
    if(r->link[ii] != 0){
        k = r->link[ii];
        mh = r->nhlx[k];
        ms = r->nsgl[k];
        k = r->loop[k];
        l = r->ibsp[k];
        
        //Need Index change here
        if(k > 1){
            kloop = 0;
            k = 1;
            l = n;
        }
    }
    else{
        mh = 2;
        ms = 0;
        k = ii;
        l = jj;
    }
    e4 = 0.0e0;
    
    //Initial Energy
    if(nh == 1 && iloop == 1)
        ehair(r->iseq,i,j,n,e1);
    else if(nh == 2 && iloop == 1){
        ip = i + 1;
        while(r->ibsp[ip] == 0)
            ip = ip + 1;
        jp = r->ibsp[ip];
        ebulge(r->iseq,i,j,ip,jp,n,e1);
    }
    else{
        e1 = 0.0e0;
        e5 = 0.0e0;
        e3 = 0.0e0;

        is = r->iseq[ii];
        js = r->iseq[jj];
        
        if(iloop == 1){
            if(ns <= 6){
                e1 = em + es * float(ns) + eh*float(nh);
            }
            else{
                x = float(ns)/6.0e0;
                e1 = em + es * 6.0e0 + eh * float(nh);
                e1 = e1 + c * log(x);
            }
        }
        if(ii > 1){
            if(r->ibsp[ii-1] == 0){
                edangle(r->iseq,ii,jj,ii-1,n,e5);
                if(ii > 2){
                    ip = ii - 2;
                    jp = r->ibsp[ip];
                    if(jp != 0){
                        edangle(r->iseq,ip,jp,ii-1,n,ed);
                        if(kk == ii+1) 
                            e4 = e4 + ed;
                        e5 = (e5 < ed)? e5:ed;
                    }
                }
                if(ii > 3 && kk == ii-1){
                    if(r->ibsp[ii-2] == 0){
                        ip = ii - 3;
                        jp = r->ibsp[ip];
                        if(jp != 0){
                            edangle(r->iseq,ip,jp,ii-2,n,ed);
                            e1= e1 + ed;
                        }
                    }
                }
            }
        }
        if(jj < n){
            if(r->ibsp[jj+1] == 0){
                edangle(r->iseq,ii,jj,jj+1,n,e3);
                if(jj < n-1){
                    ip = jj + 2;
                    jp = r->ibsp[ip];
                    if(jp != 0){
                        edangle(r->iseq,ip,jp,jj+1,n,ed);
                        if(kk == jj-1) e4 = e4 + ed;
                        e3 = (e3 < ed)? e3:ed;
                    }
                }
                if(jj < n-2 && kk == jj+1){
                    if(r->ibsp[jj+2] == 0){
                        ip = jj+ 3;
                        jp = r->ibsp[ip];
                        if(jp!=0){
                            edangle(r->iseq,ip,jp,jj+2,n,ed);
                            e1 = e1 + ed;
                        }
                    }
                }
            }
        }
        e1 = e1 + e3 + e5 + eaup[is][js];
    }
    
    if(mh == 1 && kloop == 1)
        ehair(r->iseq, ii, jj, n, e2);
    else if(mh == 2 && kloop == 1){
        if(ms == 0)
            estack(r->iseq,ii,jj,ii+1,jj-1,n,e2);
        else{
            ip = ii + 1;
            while(r->ibsp[ip] == 0)
                ip = ip + 1;
            jp = r->ibsp[ip];
            ebulge(r->iseq,ii,jj,ip,jp,n,e2);
        }
    }
    else{
        e2 = 0.0e0;
        e5 = 0.0e0;
        e3 = 0.0e0;
        
        is = r->iseq[ii];
        js = r->iseq[jj];
        if(kloop == 1){
            if(ms <= 6)
                e2 = em + es * float(ms) + eh * float(mh);
            else{
                x = float(ms) / 6.0e0;
                e2 = em + es * 6.0e0 + eh * float(mh);
                e2 = e2 + c * log(x);
            }
        }
        if(jj > 1){
            if(r->ibsp[jj-1] == 0){
                edangle(r->iseq,ii,jj,jj-1,n,e5);
                if(jj > 2){
                    ip = jj - 2;
                    jp = r->ibsp[ip];
                    if(jp != 0){
                        edangle(r->iseq,ip,jp,jj-1,n,ed);
                        if(kk == jj + 1) e4 = e4 + ed;
                        e5 = (e5 < ed)? e5:ed;
                    }
                }
                if(jj > 3 && kk == jj-1){
                    if(r->ibsp[jj-2] == 0){
                        ip = jj - 3;
                        jp = r->ibsp[ip];
                        if(jp!=0){
                            edangle(r->iseq,ip,jp,jj-2,n,ed);
                            e2 = e2 + ed;
                        }
                    }
                }
            }
        }
        if(ii < n){
            if(r->ibsp[ii+1] == 0){
                edangle(r->iseq,ii,jj,ii+1,n,e3);
                if(ii < n-1){
                    ip = ii + 2;
                    jp = r->ibsp[ip];
                    if(jp != 0){
                        edangle(r->iseq,ip,jp,ii+1,n,ed);
                        if(kk == ii-1) e4 = e4 + ed;
                        e3 = (e3 < ed)? e3:ed;
                    }
                }
                if(ii < n-2 && kk == ii+1){
                    if(r->ibsp[ii+2] == 0){
                        ip = ii + 3;
                        jp = r->ibsp[ip];
                        if(jp != 0){
                            edangle(r->iseq,ip,jp,ii+2,n,ed);
                            e2 = e2 + ed;
                        }
                    }
                }
            }
        }
        e2 = e2 + e3 + e5 + eaup[is][js];
    }
    ei = e1 + e2;
    
    //Final Energy
    if(kk == ii - 1 || kk == jj + 1){
        ns = ns - 1;
        ms = ms + 1;
    } 
    else{
        ns = ns + 1;
        ms = ms - 1;
    }
    if (nh == 1 && iloop == 1){
        if (kk == i - 1 || kk == i + 1){
            ehair(r->iseq, kk, j, n, e1);
        }
        if (kk == j - 1 || kk == j + 1){
            ehair(r->iseq, i, kk, n, e1);
        }
    } 
    else if (nh == 2 && iloop == 1){
        if (ns == 0){
            if (kk == ii - 1){
                estack(r->iseq, kk - 1, jj + 1, kk, jj, n, e1);
            } 
            else{
                estack(r->iseq, ii - 1, kk + 1, ii, kk, n, e1);
            }
        } 
        else{
            ip = i + 1;
            while(r->ibsp(ip) == 0)
                ip = ip + 1;
            jp = r->ibsp(ip);
            if (ii == j){
                if (kk == ii + 1 || kk == ii - 1){
                    ebulge(r->iseq, jj, kk, ip, jp, n, e1);
                }
                else{
                    ebulge(r->iseq, kk, ii, ip, jp, n, e1);
                }
            }
            else {
                if (kk == ii + 1 || kk == ii - 1){
                    ebulge(r->iseq, i, j, kk, jj, n, e1);
                } 
                else{
                    ebulge(r%iseq, i, j, ii, kk, n, e1);
                }
            }
        }
    } 
    else{
        e1 = 0.0e0;
        e5 = 0.0e0;
        e3 = 0.0e0;
        if (iloop == 1){
            if (ns <= 6){
                e1 = em + es*float(ns) + eh*float(nh);
            } 
            else{
                x = float(ns)/6.0e0;
                e1 = em + es*6.0e0 + eh*float(nh);
                e1 = e1 + c*log(x);
            }
        }
        if (kk == jj + 1 || kk == jj - 1){
            is = r->iseq[ii];
            js = r->iseq[kk];
            if (ii > 1){
                if (r->ibsp[ii - 1] == 0){
                    edangle(r->iseq, ii, kk, ii - 1, n, e5);
                    if (ii > 2){
                        ip = ii - 2;
                        jp = r->ibsp[ip];
                        if (jp != 0){
                            edangle(r->iseq, ip, jp, ii - 1, n, ed);
                            e5 = (e5 < ed)? e5:ed;
                        }
                    }
                }
            }
            if (kk < n){
                if (r->ibsp(kk + 1) == 0 || kk == jj - 1){
                    edangle(r->iseq, ii, kk, kk + 1, n, e3);
                    if (kk < n - 1) {
                        ip = kk + 2;
                        jp = r->ibsp[ip];
                        if (jp != 0){
                            edangle(r->iseq, ip, jp, kk + 1, n, ed);
                            e3 = (e3<ed)? e3:ed;
                        }
                    }
                }
            }
        }
        if (kk == ii - 1 || kk == ii + 1){
            is = r->iseq[kk];
            js = r->iseq[jj];
            if (kk > 1){
                if (r->ibsp[kk - 1] == 0 || kk == ii + 1){
                    edangle(r->iseq, kk, jj, kk - 1, n, e5);
                    if (kk > 2) {
                        ip = kk - 2;
                        jp = r->ibsp[ip];
                        if (jp != 0){
                            edangle(r->iseq, ip, jp, kk - 1, n, ed);
                            e5 = (e5 < ed)? e5:ed;
                        }
                    }
                }
            }
            if (jj < n){
                if (r->ibsp[jj + 1] == 0){
                    edangle(r->iseq, kk, jj, jj + 1, n, e3);
                    if (jj < n - 1){
                        ip = jj + 2;
                        jp = r->ibsp[ip];
                        if (jp != 0){
                            edangle(r->iseq, ip, jp, jj + 1, n, ed);
                            e3 = (e3 < ed)? e3:ed;
                        }
                    }
                }
            }
        }
        e1 = e1 + e3 + e5 + eaup[is][js];
    }
    if (mh == 1 && kloop == 1){
        if (kk == ii - 1 || kk == ii + 1){
            ehair(r->iseq, kk, jj, n, e2);
        }
        if (kk == jj - 1 || kk == jj + 1){
            ehair(r->iseq, ii, kk, n, e2);
        }
    } 
    else if (mh == 2 && kloop == 1){
        if (ms == 0){
            if (kk == ii + 1){
                estack(r->iseq, kk, jj, kk + 1, jj - 1, n, e2);
            } 
            else{
                estack(r->iseq, ii, kk, ii + 1, kk - 1, n, e2);
            }
        }
        else{
            ip = ii + 1;
            while(r->ibsp[ip] == 0)
                ip = ip + 1;
            jp = r->ibsp[ip];
            if (kk == ii + 1 || kk == ii - 1){
                ebulge(r->iseq, kk, jj, ip, jp, n, e2);
            }
            else{
                ebulge(r->iseq, ii, kk, ip, jp, n, e2);
            }
        }
    } 
    else{
        e2 = 0.0e0;
        e5 = 0.0e0;
        e3 = 0.0e0;
        if (kloop == 1){
            if (ms <= 6){
                e2 = em + es*float(ms) + eh*float(mh);
            } 
            else{
                x = float(ms)/6.0e0;
                e2 = em + es*6.0e0 + eh*float(mh);
                e2 = e2 + c*log(x);
            }
        }
        if (kk == jj + 1 || kk == jj - 1){
            is = r->iseq[ii];
            js = r->iseq[kk];
            if (kk > 1){
                if (r->ibsp[kk - 1] == 0 || kk == jj + 1){
                    edangle(r->iseq, ii, kk, kk - 1, n, e5);
                    if (kk > 2) {
                        ip = kk - 2;
                        jp = r->ibsp[ip];
                        if (jp != 0){
                            edangle(r->iseq, ip, jp, kk - 1, n, ed);
                            e5 = (e5<ed)? e5:ed;
                        }
                    }
                }
            }
            if (ii < n) {
                if (r->ibsp[ii + 1] == 0) {
                    edangle(r->iseq, ii, kk, ii + 1, n, e3);
                    if (ii < n - 1) {
                        ip = ii + 2;
                        jp = r->ibsp[ip];
                        if (jp != 0){
                            edangle(r->iseq, ip, jp, ii + 1, n, ed);
                            e3 = (e3<ed)? e3:ed;
                        }
                    }
                }
            }
        }
        if (kk == ii - 1 || kk == ii + 1){
            is = r->iseq[kk];
            js = r->iseq[jj];
            if (jj > 1){
                if (r->ibsp[jj - 1] == 0){
                    edangle(r->iseq, kk, jj, jj - 1, n, e5);
                    if (jj > 2){
                        ip = jj - 2;
                        jp = r->ibsp[ip];
                        if (jp != 0) {
                            edangle(r->iseq, ip, jp, jj - 1, n, ed);
                            e5 = (e5<ed)? e5:ed;
                        }
                    }
                }
            }
            if (kk < n) {
                if (r->ibsp[kk + 1] == 0 || kk == ii - 1){
                    edangle(r->iseq, kk, jj, kk + 1, n, e3);
                    if (kk < n - 1){
                        ip = kk + 2;
                        jp = r->ibsp[ip];
                        if (jp != 0) {
                            edangle(r->iseq, ip, jp, kk + 1, n, ed);
                            e3 = (e3<ed)? e3:ed;
                        }
                    }
                }
            }
        }
        e2 = e2 + e3 + e5 + eaup[is][js];
    }
    ef = e1 + e2 + e4;
    dg = double(ef) - double(ei);
}