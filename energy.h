/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   energy.h
 * Author: Nikhil
 *
 * Created on 29 June, 2019, 4:08 PM
 */

#ifndef ENERGY_H
#define ENERGY_H

void delta_hd(rna_struc *r, int ii, int jj, int kk, double dg);
void deltag_hr(rna_struc r, int ii, int jj, double dg);
void deltag_hi(rna_struc r, int i, int j, double dg);
void deltag_hm(rna_struc r, int ii, int jj, double dg);
void deltag_he(rna_struc r, int ii, int jj, double dg);
void ehair(int iseq[], int i, int j, int n, float eh);
void ebulge(int iseq[], int i, int j, int ip, int jp, int n, float eb);
void edangle(int iseq[], int i, int j, int k, int n, float ed);
void estack(int iseq[], int i, int j, int ip, int jp, int n, float es);
void estruc(int iseq[], int ibsp[], int n, float e);
void eloop(int iseq[], int ibsp[], int i, int j, int n, float el);
void tint11(int list[], int eb);
void tdangle3(int list[], float es);
void tdangle5(int list[], float es);
void tint12(int list[], float eb);
void tint22(int list[], float eb);
void tloop(int list[],int el);
void tstack(int list[], float es);
void tstackh(int list[], float es);
void tstacki(int list[], float es);

#endif /* ENERGY_H */

