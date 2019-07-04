/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "rnafold.h"

void loop_reac(rna_struc *r, int indx){
    int i,j,k,n,ip,jp,kp,is,js;
    int ks,ke,l,lmx,icnt,iloop;
    int nt,nh,ns,mt,mh,ms,icase;
    
    double x, dg, atot, rate;
    
    i = r->loop[indx];
    j = r->ibsp[i];
    n = r->n;
    
    if(i == n)
        j = 0;
    nh = r->nhlx[indx];
    ns = r->nsgl[indx];
    
    nt = ns + 2 * nh;
    
    //Internal Loop Flag iloop (1-internal)
    if(i < j) iloop = 1;
    if(i > j) iloop = 0;
    if(i == j){
        ks = i + 1;
        ke = j;
    }
    else{
        ks = j;
        ke = i;
    }
    
    //Compute Reactions
    atot = 0.0e0;
    k = ks;
    icnt = 0;
    
    while(k <= ke){
        if(r->ibsp[k] == 0){
            r->wrk1[k] = 0.0e0;
            r->wrk2[k] = 0.0e0;
            x = 0.0e0;
            l = 2;
            lmx = nt/2 + 1;
            
            if(nt % 2 == 0){
                if(icnt + 1 > lmx - 1)
                    lmx = lmx - 1;
            }
            if(iloop == 0)
                lmx = nt - icnt;
            
            kp = k+1;
            is = r->iseq[k];
            
            while(l <= lmx){
                if(r->ibsp[kp] == 0){
                    js = r->iseq[kp];
                    if(l > 4 && iwc[is][js]==1)
                        x = x + pnuc[l];
                }
                else{
                    l = l + 1;
                    kp = r->ibsp[kp];
                }
                l = l + 1;
                kp = kp + 1;
            }
            r->wrk1[k] = x;
            atot = atot + x;
        }
        //Helix Events
        if(r->ibsp[k] > 0){
            ip = k;
            jp = r->ibsp[k];
            
            r->wrk1[jp] = 0.0e0;
            r->wrk2[ip] = 0.0e0; 
            
            if(r->link[ip] == 0){
                r->wrk1[ip] = 0.0e0;
                r->wrk2[jp] = 0.0e0;
            }
            icase = 0;
            //Helix Extension
            if(ip > 1 && jp < n){
                if(nh > 1 || ns > 4){
                    if(r->ibsp[ip-1] == 0 && r->ibsp[jp+1] ==0){
                        is = r->iseq[ip-1];
                        js = r->iseq[jp+1];
                        if(iwc[is][js] == 1){
                            icase = 1;
                            if(iloop == 1){
                                if(nh ==2 && ns == 2){
                                    icase = 2;
                                    if(k==ke)
                                        icase = 0;
                                }
                                else if(k==ke){
                                    icase = 3;
                                }
                            }
                        }
                    }
                }
            }
            
            if(icase > 0){
                //Commenting Function
                //delta_he(r,ip,jp,dg);
                dg = dg / 2.0e0;
                x = beta * dg;
                x = exp(-x) * rateh;
                
                r->wrk2[ip] = x;
                atot = atot + x;
            }
            icase = 0;
       
            //Helix Retraction
            if(ip != n-1 && jp != 0){ //Changed Index Here
                if(r->ibsp[ip+1] == jp - 1){
                    icase = 1;
                    if(iloop == 1){
                        if(k==ke)
                            icase = 2;
                    }
                    rate = rateh;
                }
                else if(iloop == 0 || k != ke){
                    icase = 3;
                    
                    l = r->link[ip];
                    mh = r->nhlx[l];
                    ms = r->nsgl[l];
                    
                    mt = ms + 2*mh;
                    
                    if(iloop == 1){
                        l = (nt < mt)? nt:mt;
                    }
                    else
                        l=mt;
                    rate = pnuc[l];
                }
            }
            if(icase > 0){
                //Commenting Function
                //delta_hr(r,ip,jp,dg);
                if(icase != 3)
                    dg = dg/ 2.0e0;
                x = beta * dg;
                x = exp(-x) * rate;
                if(icase == 2)
                    r->wrk1[ip] = x;
                else
                    r->wrk1[jp] = x;
                atot = atot + x;
            }
            icase = 0;
            
            //Helix Morphing
            if(iloop == 0 || nh > 2){
                if(ip > 1 && jp < n){
                    is = r->iseq[ip - 1];
                    js = r->iseq[jp + 1];
                    if(iwc[is][js] == 1)
                        icase = 1;
                    is = r->ibsp[ip-1];
                    js = r->ibsp[jp+1];
                    
                    if(is != 0){
                        if(r->link[is] != 0)
                            icase = 0;
                    }
                    if(js != 0){
                        if(r->link[jp+1] != 0)
                            icase = 0;
                    }
                    if(is == 0 && js == 0)
                        icase = 0;
                }
            }
            if(icase > 0){
                //Commenting Function
                //deltag_hm(r,ip,jp,dg);
                dg = dg / 2.0e0;
                x = beta * dg;
                x = exp(-x) * ratem;
                
                atot = atot + x;
            }
            
            //Defect Diffusion
            //Push
            icase = 0;
            if(r->link[ip] == 0){
                icase = 2;
                if(iloop == 1){
                    if(nh==2 && ns==1) icase = 3;
                    if(nh==1 && ns==3) icase = 0;
                }
            }
            else if(iloop == 0 || k != ke){
                icase = 1;
                if(iloop == 1){
                    if(nh==2 && ns==1) icase = 4;
                }
            }
            if(icase > 0){
                //Push 5' End
                kp = ip - 1;
                if(kp >= 1){
                    if(r->ibsp[kp] == 0){
                        is = r->iseq[kp];
                        js = r->iseq[jp];
                        if(iwc[is][js] == 1){
                            //Commenting Function
                            //deltag_hd(r,ip,jp,kp,dg);
                            dg = dg/2.0e0;
                            x = beta * dg;
                            x = exp(-x) * rated;
                            
                            atot = atot + x;
                        }
                    }
                }
                //Push 3' End
                kp = jp + 1;
                if(kp <= n){
                    if(r->ibsp[kp] == 0){
                        is = r->iseq[ip];
                        js = r->iseq[kp];
                        if(iwc[is][js] == 1){
                            //Commenting Function
                            //deltag_hd(r,ip,jp,kp,dg);
                            dg = dg/2.0e0;
                            x = beta * dg;
                            x = exp(-x) * rated;
                            
                            atot = atot + x;
                        }
                    }
                }
            }
            //Pull
            icase = 0;
            if(r->link[ip] != 0){
                if(iloop == 0 || k != ke){
                    l = r->link[ip];
                    mh = r->nhlx[l];
                    ms = r->nsgl[l];
                    
                    icase = 1;
                    if(mh == 1 && ms == 3) icase = 0;
                    if(mh == 2 && ms == 1) icase = 4;
                }
            }
            if(icase > 0){
                //Pull 5' End
                kp = ip + 1;
                if(r->ibsp[kp] == 0){
                    is = r->iseq[kp];
                    js = r->iseq[jp];
                    
                    if(iwc[is][js] == 1){
                            //Commenting Function
                            //deltag_hd(r,ip,jp,kp,dg);
                            dg = dg/2.0e0;
                            x = beta * dg;
                            x = exp(-x) * rated;
                            
                            atot = atot + x;
                        }
                }
                //Pull 3' End
                kp = jp - 1;
                if(r->ibsp[kp] == 0){
                    is = r->iseq[ip];
                    js = r->iseq[kp];
                    
                    if(iwc[is][js] == 1){
                            //Commenting Function
                            //deltag_hd(r,ip,jp,kp,dg);
                            dg = dg/2.0e0;
                            x = beta * dg;
                            x = exp(-x) * rated;
                            
                            atot = atot + x;
                        }
                }
            }
            //Save Loop Reaction Rate
            if(iloop == 1) r->wrk1[i] = atot;
            //Open Internal Helix BP
            if(r->link[ip] == 0){
                if(iloop == 1 && k == ke){
                    is = ip + 1;
                    js = jp + 1;
                    while(r->link[is] == 0){
                        //Commenting Function
                        //deltag_hi(r,is,js,dg);
                        dg = dg / 2.0e0;
                        x = beta * dg;
                        x = exp(-x) * rateh;
                        r->wrk1[is] = x;
                        r->wrk1[js] = 0.0e0;
                        r->wrk2[is] = 0.0e0;
                        r->wrk2[js] = 0.0e0;
                        
                        atot = atot + x;
                        is = is + 1;
                        js = js - 1;
                    }
                }
            }
            if(k!=ke){
                k = r->ibsp[k];
                icnt = icnt + 1;
            }
        }
        k = k + 1;
        icnt = icnt + 1;
    }
    r->ptot[indx] = atot;
    loop_resum(r,indx);
}