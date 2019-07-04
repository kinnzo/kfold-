/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rnafold.h
 * Author: Nikhil
 *
 * Created on 19 June, 2019, 1:20 PM
 */

#include <cmath>
#include "rnavar.h"
#ifndef RNAFOLD_H
#define RNAFOLD_H

struct rna_struc{
    char seq[mxnt];
    
    int iseq[mxnt];
    int ibsp[mxnt];
    int link[mxnt];
    
    int loop[mxnt];
    int nhlx[mxnt];
    int nsgl[mxnt];
    
    int n;
    int n1;
    int nsum;
    
    double psum[mxnt];
    double ptot[mxnt];
    
    double wrk1[mxnt];
    double wrk2[mxnt];
};

void loop_init(rna_struc *r);
void loop_resum(rna_struc *r, int indx);

void helx_reac(rna_struc *r, int i);
void loop_reac(rna_struc *r, int indx);
void loop_fire(rna_struc *r, int indx, double amax);


#endif /* RNAFOLD_H */

