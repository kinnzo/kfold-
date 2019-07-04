/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "rnavar.h"

int iwc[4][4];
float eaup[4][4];

double beta =  0.16225023135094183147e1;
const double gcons = 1.987206e-3;
const double temp = 310.15e0;

const double rateh = 1.0e2; //Helix Extension
const double ratem = 5.0e0; //Helix Morphing
const double rated = 5.0e0; //Helix Diffusion

//const int mxnt = 10000;

const float em = 10.10e0;
const float eh = -0.30e0;
const float es = -0.30e0;
const float eau = +0.50e0;

void readdata(){
    int i,j,k;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            iwc[i][j] = 0;
            eaup[i][j] = 0.0e0;
        }   
    }
    iwc[0][3] = 1;
    iwc[3][0] = 1;
    iwc[1][2] = 1;
    iwc[2][1] = 1;
    iwc[2][3] = 1;
    iwc[3][2] = 1;
    
    eaup[0][3] = eau;
    eaup[3][0] = eau;
    eaup[2][3] = eau;
    eaup[3][2] = eau;
}