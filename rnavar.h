/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rnavar.h
 * Author: Nikhil
 *
 * Created on 18 June, 2019, 10:51 AM
 */

#include <vector>
#include <iostream>
#include <cmath>
#include "random.h"
#ifndef RNAVAR_H
#define RNAVAR_H

using namespace std;

extern vector <double> pnuc;
//Variables
extern double beta;
extern int iwc[4][4];
extern float eaup[4][4];

//Parameters
extern const double gcons;
extern const double temp;

extern const double rateh; //Helix Extension
extern const double ratem; //Helix Morphing
extern const double rated; //Helix Diffusion

const int mxnt = 10000;

extern const float em;
extern const float eh;
extern const float es;
extern const float eau;
void readdata();
void setupnuc(int n);
#endif /* RNAVAR_H */

